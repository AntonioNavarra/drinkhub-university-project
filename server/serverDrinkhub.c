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

// Costanti
#define PORT_NUMBER 8080
#define BUFFER_SIZE 2000

// Strutture dati per gli utenti e i prodotti
struct User {
    char username[50];
    char password[50];
    int logged;
    char favoriteCategory[50];
};

struct Product {
    char name[50];
    double price;
    char image_url[255];
};

// Funzioni
PGconn *establishDBConnection(void);
PGresult *executeQuery(PGconn *conn, const char *query);
bool registerUser(const struct User *user, PGconn *conn);
bool loginUser(struct User *user, PGconn *conn);
bool addToCart(const char *productName, PGconn *conn, const char *username);
PGresult *getCart(PGconn *conn, const char *username);
PGresult *getTopRecommendedProducts(PGconn *conn);
PGresult *getFavoriteCategoryProducts(PGconn *conn, const struct User *user);
PGresult *searchProducts(PGconn *conn, const char *searchWords, bool alcoholicFilter, bool nonAlcoholicFilter, bool smoothieFilter);
void *handleConnection(void *socketDesc);
void closeDBConnection(PGconn *conn);
void sendMessageToClient(const char *message, int sock);

// Funzione principale
int main(void) {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddressLength = sizeof(struct sockaddr_in);

    // Creazione del socket del server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configurazione dell'indirizzo del server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT_NUMBER);

    // Associazione del socket all'indirizzo del server
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Ascolto delle connessioni in arrivo
    listen(serverSocket, 3);

    printf("\n*** Welcome to the DrinkHub server ***\n\n");
    printf("Server listening on port %d...\n\n", PORT_NUMBER);

    // Accettazione delle connessioni e gestione dei thread
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

        // Distacco del thread per rilasciare immediatamente le risorse
        pthread_detach(thread);
    }

    if (clientSocket < 0) {
        perror("Connection with client failed\n\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// Connessione al database
PGconn *establishDBConnection(void) {
    const char *connectionInfo = "host=localhost port=5432 dbname=DrinkHub user=postgres password=admin";
    PGconn *dbConnection = PQconnectdb(connectionInfo);

    if (PQstatus(dbConnection) != CONNECTION_OK) {
        fprintf(stderr, "Database connection failed: %s\n", PQerrorMessage(dbConnection));
        PQfinish(dbConnection);
        exit(EXIT_FAILURE);
    }

    return dbConnection;
}

// Esecuzione di una query e gestione degli errori
PGresult *executeQuery(PGconn *conn, const char *query) {
    PGresult *result = PQexec(conn, query);

    if (PQresultStatus(result) != PGRES_COMMAND_OK && PQresultStatus(result) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error executing query: %s\n", PQerrorMessage(conn));
        PQclear(result);
        exit(EXIT_FAILURE);
    }

    return result;
}

// Registrazione di un nuovo utente
bool registerUser(const struct User *user, PGconn *conn) {
    char query[1000];
    snprintf(query, sizeof(query), "INSERT INTO utente(username, password) VALUES ('%s', '%s')",
             user.username, user.password);

    PGresult *result = executeQuery(conn, query);
    PQclear(result);

    return true;
}

// Login utente
bool loginUser(struct User *user, PGconn *conn) {
    char query[1000];
    if (user.logged > 0) {
        return true;
    }
    snprintf(query, sizeof(query), "SELECT * FROM utente WHERE username='%s' AND password='%s'",
             user.username, user.password);
    PGresult *result = executeQuery(conn, query);
    int rows = PQntuples(result);
    PQclear(result);
    return rows > 0;
}

// Aggiunta di un prodotto al carrello
bool addToCart(const char *productName, PGconn *conn, const char *username) {
    char query[1000];
    snprintf(query, sizeof(query), "INSERT INTO carrello(username2, nomeProdotto2) VALUES ('%s', '%s')",
             username, productName);

    PGresult *result = executeQuery(conn, query);

    if (PQresultStatus(result) == PGRES_COMMAND_OK) {
        PQclear(result);
        return true;
    } else {
        fprintf(stderr, "Error adding product to the cart: %s\n", PQerrorMessage(conn));
        PQclear(result);
        return false;
    }
}

// Ottenimento del carrello per un utente
PGresult *getCart(PGconn *conn, const char *username) {
    char query[1000];
    snprintf(query, sizeof(query), "SELECT p->nomeProdotto, p->prezzo"
                                    "FROM carrello c JOIN prodotto p ON c->nomeProdotto2 = p->nomeProdotto "
                                    "WHERE c->username='%s'", username);
    return executeQuery(conn, query);
}

// Ottenimento dei prodotti consigliati
PGresult *getTopRecommendedProducts(PGconn *conn) {
    char query[1000];
    snprintf(query, sizeof(query), "SELECT * FROM prodotto ORDER BY costo LIMIT 10");
    return executeQuery(conn, query);
}

// Ottenimento dei prodotti della categoria preferita per un utente
PGresult *getFavoriteCategoryProducts(PGconn *conn, const struct User *user) {
    char query[1000];
    snprintf(query, sizeof(query), "SELECT * FROM prodotto WHERE categoria = '%s' AND idprodotto IN "
                                    "(SELECT idprodotto FROM carrello WHERE username='%s') LIMIT 10", user.favoriteCategory , user.username);
    return executeQuery(conn, query);
}

// Ricerca dei prodotti attraverso la barra di ricerca e le checkbox
PGresult *searchProducts(PGconn *conn, const char *searchWords, bool alcoholicFilter, bool nonAlcoholicFilter, bool smoothieFilter) {
    char query[1000];

    if (alcoholicFilter) {
        snprintf(query, sizeof(query), "SELECT * FROM prodotto WHERE nomeprodotto ILIKE '%%%s%%' AND categoria = 'alcolico'", searchWords);
    } else if (nonAlcoholicFilter) {
        snprintf(query, sizeof(query), "SELECT * FROM prodotto WHERE nomeprodotto ILIKE '%%%s%%' AND categoria = 'analcolico'", searchWords);
    } else if (smoothieFilter) {
        snprintf(query, sizeof(query), "SELECT * FROM prodotto WHERE nomeprodotto ILIKE '%%%s%%' AND categoria = 'frullato'", searchWords);
    } else {
        snprintf(query, sizeof(query), "SELECT * FROM prodotto WHERE nomeprodotto ILIKE '%%%s%%'", searchWords);
    }
    return executeQuery(conn, query);
}

// Gestione della connessione del client in un thread separato
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

                // Estrazione dei dati di registrazione dal messaggio del client
                token = strtok(NULL, ";");
                strncpy(user.username, token, sizeof(user.username) - 1);
                user.username[sizeof(user.username) - 1] = '\0';

                token = strtok(NULL, ";");
                strncpy(user.password, token, sizeof(user.password) - 1);
                user.password[sizeof(user.password) - 1] = '\0';

                token = strtok(NULL, ";");
                strncpy(user.favoriteCategory, token, sizeof(user.favoriteCategory) - 1);
                user.favoriteCategory[sizeof(user.favoriteCategory) - 1] = '\0';

                // Registrazione dell'utente nel database
                if (registerUser(&user, dbConnection)) {
                    printf("Registration successful\n\n");
                    strcpy(message, "OK");
                } else {
                    printf("Error during registration\n\n");
                    strcpy(message, "Error");
                }
            } else if (strcmp(token, "Login") == 0 || strcmp(token, "LoginFinger") == 0) {
                printf("Logging in...\n\n");

                // Estrazione dei dati di login dal messaggio del client
                token = strtok(NULL, ";");
                strncpy(user.username, token, sizeof(user.username) - 1);
                user.username[sizeof(user.username) - 1] = '\0';

                token = strtok(NULL, ";");
                strncpy(user.password, token, sizeof(user.password) - 1);
                user.password[sizeof(user.password) - 1] = '\0';

                user.logged = (strcmp(token, "LoginFinger") == 0) ? 1 : 0;

                // Login dell'utente
                if (loginUser(&user, dbConnection)) {
                    printf("Login successful\n\n");
                    strcpy(message, "OK");
                } else {
                    printf("Error during login\n\n");
                    strcpy(message, "Error");
                }
            } else if (strcmp(token, "GetCart") == 0) {
                printf("Viewing the cart...\n\n");
                // Ottenimento del carrello dell'utente
                PGresult *cartResult = getCart(dbConnection, user.username);
                PQclear(cartResult);
            } else if (strcmp(token, "AddToCart") == 0) {
                printf("Adding the product to the cart...\n\n");
                struct Product product;

                // Estrazione dei dati del prodotto dal messaggio del client
                token = strtok(NULL, ";");
                strncpy(product.name, token, sizeof(product.name) - 1);
                product.name[sizeof(product.name) - 1] = '\0';

                token = strtok(NULL, ";");
                product.price = atof(token);

                token = strtok(NULL, ";");
                strncpy(product.image_url, token, sizeof(product.image_url) - 1);
                product.image_url[sizeof(product.image_url) - 1] = '\0';

                // Aggiunta del prodotto al carrello
                if (addToCart(&product, dbConnection, user.username)) {
                    printf("Product added to the cart successfully\n\n");
                    strcpy(message, "OK");
                } else {
                    printf("Error adding the product to the cart\n\n");
                    strcpy(message, "Error");
                }
            } else if (strcmp(token, "GetTopRecommendedProducts") == 0) {
                printf("Viewing top recommended products...\n\n");
                // Ottenimento dei prodotti consigliati
                PGresult *recommendedResult = getTopRecommendedProducts(dbConnection);
                PQclear(recommendedResult);
            } else if (strcmp(token, "GetFavoriteCategoryProducts") == 0) {
                printf("Viewing favorite category products...\n\n");
                // Ottenimento dei prodotti della categoria preferita
                PGresult *favoriteCategoryResult = getFavoriteCategoryProducts(dbConnection, &user);
                PQclear(favoriteCategoryResult);
            } else if (strcmp(token, "Search") == 0) {
                printf("Searching for products...\n\n");
                // Estrazione dei dati di ricerca dal messaggio del client
                token = strtok(NULL, ";");
                char searchWords[255];
                strncpy(searchWords, token, sizeof(searchWords) - 1);
                searchWords[sizeof(searchWords) - 1] = '\0';
                token = strtok(NULL, ";");
                bool alcoholicFilter = (strcmp(token, "true") == 0);
                token = strtok(NULL, ";");
                bool nonAlcoholicFilter = (strcmp(token, "true") == 0);
                token = strtok(NULL, ";");
                bool smoothieFilter = (strcmp(token, "true") == 0);
                // Ricerca dei prodotti
                PGresult *searchResult = searchProducts(dbConnection, searchWords, alcoholicFilter, nonAlcoholicFilter, smoothieFilter);
                PQclear(searchResult);
            }

            // Invio messaggio al client
            sendMessageToClient(message, clientSocket);
        }
    }

    // Gestione della disconnessione del client
    ssize_t recv_result = recv(clientSocket, clientMessage, sizeof(clientMessage), 0);
    if (recv_result == 0) {
        puts("Client disconnected\n\n");
        fflush(stdout);
    } else if (recv_result == (ssize_t)-1) {
        perror("recv failed");
    }

    // Chiusura del socket e liberazione delle risorse
    close(clientSocket);
    closeDBConnection(dbConnection);
    free(socketDesc);
    return NULL;
}


// Chiusura della connessione al database
void closeDBConnection(PGconn *conn) {
    PQfinish(conn);
}

// Invio messaggio al client
void sendMessageToClient(const char *message, int sock) {
    send(sock, message, strlen(message), 0);
}