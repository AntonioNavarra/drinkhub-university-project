#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <libpq-fe.h>

#define PORT_NUMBER 8080
#define BUFFER_SIZE 2000

// Struct
struct User {
    char username[50];
    char password[50];
    int logged;
    char accessibility[50];
};

struct ItemOnCart {
    char name[50];
    double price;
    char image_url[255];
};

// Function declarations
PGconn *establishDBConnection(void);
PGresult *executeQuery(PGconn *conn, const char *query);
bool registerUser(const struct User *user, PGconn *conn);
bool loginUser(struct User *user, PGconn *conn);
void *handleConnection(void *socketDesc);
void closeDBConnection(PGconn *conn);
void sendMessageToClient(const char *message, int sock);
PGresult *getCart(PGconn *conn, const char *username);
bool addToCart(const struct ItemOnCart *product, PGconn *conn, const char *username);

// Main
int main(void) {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(struct sockaddr_in);

    // Create Socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT_NUMBER);

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    listen(serverSocket, 3);

    // Initialize database connection
    printf("\n*** Welcome to the DrinkHub server ***\n\n");
    printf("Server listening on port %d...\n\n", PORT_NUMBER);

    while ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength))) {
        printf("Connection with client established\n\n");

        pthread_t thread;
        int *newSocket = malloc(sizeof(int));
        if (!newSocket) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        *newSocket = clientSocket;

        if (pthread_create(&thread, NULL, handleConnection, (void *)newSocket) != 0) {
            perror("Error creating thread");
            free(newSocket);
            exit(EXIT_FAILURE);
        }

        // Detach the thread to release resources immediately
        pthread_detach(thread);
    }

    if (clientSocket < 0) {
        perror("Connection with client failed\n\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Establish connection to the DB
PGconn *establishDBConnection(void) {
    char *connectionInfo = "host=localhost port=5432 dbname=DrinkHub user=postgres password=admin";
    PGconn *dbConnection = PQconnectdb(connectionInfo);

    if (PQstatus(dbConnection) != CONNECTION_OK) {
        fprintf(stderr, "Database connection failed: %s\n", PQerrorMessage(dbConnection));
        PQfinish(dbConnection);
        exit(EXIT_FAILURE);
    }

    return dbConnection;
}

// Execute a query and handle errors
PGresult *executeQuery(PGconn *conn, const char *query) {
    PGresult *result = PQexec(conn, query);

    if (PQresultStatus(result) != PGRES_COMMAND_OK && PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error executing query: %s\n", PQerrorMessage(conn));
        PQclear(result);
        exit(EXIT_FAILURE);
    }

    return result;
}

// Register a new user
bool registerUser(const struct User *user, PGconn *conn) {
    char query[1000];
    snprintf(query, sizeof(query), "INSERT INTO utente(username, password) VALUES ('%s', '%s')",
             user->username, user->password);

    PGresult *result = executeQuery(conn, query);
    PQclear(result);

    return true;
}

// Login user
bool loginUser(struct User *user, PGconn *conn) {
    char query[1000];

    if (user->logged > 0) {
        snprintf(query, sizeof(query), "SELECT accessibility FROM utente WHERE username='%s'", user->username);
    } else {
        snprintf(query, sizeof(query), "SELECT accessibility FROM utente WHERE username='%s' AND password='%s'",
                 user->username, user->password);
    }

    PGresult *result = executeQuery(conn, query);

    int rows = PQntuples(result);
    if (rows > 0) {
        strncpy(user->accessibility, PQgetvalue(result, 0, 0), sizeof(user->accessibility) - 1);
        user->accessibility[sizeof(user->accessibility) - 1] = '\0'; // Ensure null-terminated
    }

    PQclear(result);
    return rows > 0;
}

// Add a product to the cart
bool addToCart(const struct ItemOnCart *product, PGconn *conn, const char *username) {
    char query[1000];
    snprintf(query, sizeof(query), "INSERT INTO carrello(username, product_name, price, image_url) VALUES ('%s', '%s', %lf, '%s')",
             username, product->name, product->price, product->image_url);
    PGresult *result = executeQuery(conn, query);
    PQclear(result);
    return true;
}

// Get the cart for a user
PGresult *getCart(PGconn *conn, const char *username) {
    char query[1000];
    snprintf(query, sizeof(query), "SELECT product_name, price, image_url FROM carrello WHERE username='%s'", username);
    return executeQuery(conn, query);
}

// Handle client connection in a separate thread
void *handleConnection(void *socketDesc) {
    int clientSocket = *(int *)socketDesc;
    struct User user;
    char message[255], clientMessage[BUFFER_SIZE];
    PGconn *dbConnection = establishDBConnection();

    while (recv(clientSocket, clientMessage, sizeof(clientMessage), 0) > 0) {
        char *token = strtok(clientMessage, ";");

        if (token != NULL) {
            if (strcmp(token, "Registrazione") == 0) {
                printf("Registering a new user...\n\n");

                token = strtok(NULL, ";");
                strncpy(user.username, token, sizeof(user.username) - 1);
                user.username[sizeof(user.username) - 1] = '\0'; // Ensure null-terminated

                token = strtok(NULL, ";");
                strncpy(user.password, token, sizeof(user.password) - 1);
                user.password[sizeof(user.password) - 1] = '\0'; // Ensure null-terminated

                if (registerUser(&user, dbConnection)) {
                    printf("Registration successful\n\n");
                    strcpy(message, "OK");
                } else {
                    printf("Error during registration\n\n");
                    strcpy(message, "Error");
                }
            } else if (strcmp(token, "Login") == 0 || strcmp(token, "LoginFinger") == 0) {
                printf("Logging in...\n\n");

                token = strtok(NULL, ";");
                strncpy(user.username, token, sizeof(user.username) - 1);
                user.username[sizeof(user.username) - 1] = '\0'; // Ensure null-terminated

                token = strtok(NULL, ";");
                strncpy(user.password, token, sizeof(user.password) - 1);
                user.password[sizeof(user.password) - 1] = '\0'; // Ensure null-terminated

                user.logged = (strcmp(token, "LoginFinger") == 0) ? 1 : 0;

                if (loginUser(&user, dbConnection)) {
                    printf("Login successful\n\n");
                    strcpy(message, user.accessibility);
                } else {
                    printf("Error during login\n\n");
                    strcpy(message, "Error");
                }
            } else if (strcmp(token, "GetCart") == 0) {
                printf("Viewing the cart...\n\n");
                PGresult *cartResult = getCart(dbConnection, user.username);
                PQclear(cartResult);
            } else if (strcmp(token, "AddToCart") == 0) {
                printf("Adding the product to the cart...\n\n");
                struct ItemOnCart product;

                token = strtok(NULL, ";");
                strncpy(product.name, token, sizeof(product.name) - 1);
                product.name[sizeof(product.name) - 1] = '\0'; // Ensure null-terminated

                token = strtok(NULL, ";");
                product.price = atof(token);

                token = strtok(NULL, ";");
                strncpy(product.image_url, token, sizeof(product.image_url) - 1);
                product.image_url[sizeof(product.image_url) - 1] = '\0'; // Ensure null-terminated

                if (addToCart(&product, dbConnection, user.username)) {
                    printf("Product added to the cart successfully\n\n");
                    strcpy(message, "OK");
                } else {
                    printf("Error adding the product to the cart\n\n");
                    strcpy(message, "Error");
                }
            }

            sendMessageToClient(message, clientSocket);
        }
    }
    ssize_t recv_result = recv(clientSocket, clientMessage, sizeof(clientMessage), 0);
    if (recv_result == 0) {
        puts("Client disconnesso\n\n");
        fflush(stdout);
    } else if (recv_result == (ssize_t)-1) {
        perror("recv fallito");
    }

    free(socketDesc);
    closeDBConnection(dbConnection);

    return NULL;
}

// Send a message to the client
void sendMessageToClient(const char *message, int sock) {
    if (write(sock, message, strlen(message)) < 0) {
        perror("Error writing\n\n");
        exit(EXIT_FAILURE);
    }
}

// Close the DB connection
void closeDBConnection(PGconn *conn) {
    PQfinish(conn);
}
