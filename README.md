# drinkhub-university-project
Consegna numero 3 : Gestione Vendita bevande
# Nome del Progetto: DrinkHub
Il progetto è un sistema di gestione per un bar virtuale con l'obiettivo è di consentire a qualsiasi utente (cliente) di registrarsi, navigare tra le bevande disponibili (alcolici,analcolici,frullati), effettuare acquisti simulati e gestirne il pagamento. Le informazioni relative ai prodotti e agli utenti sono conservate in un database SQL (PostgreSQL). Gli utenti possono selezionare le bevande in due modalità: 1) Utlizzando la barra di ricerca con la possibilità di aggiungere i filtri. 2) Sfruttando le liste personalizzate : "raccomandati" (Elenco dei 10 drink consigliati da DrinkHub) o "preferiti" (Elenco di 10 drink scelti sulla base dello storico vendite).
Il sistema può essere accessibile tramite applicazione per cellulare o tablet, rendendo l'esperienza utente più comoda e portatile.

# Tabella dei Contenuti
- Come Iniziare
- Struttura del Progetto
- Licenza
- Contatti

# Come Iniziare
Segui questi passaggi per configurare e avviare l'applicazione "DrinkHub" sul tuo ambiente di sviluppo.

# Prerequisiti
Prima di iniziare, assicurati di avere installato quanto segue:
- [Android Studio](https://developer.android.com/studio) (versione consigliata XYZ)
- [Git](https://git-scm.com/)

# Installazione
1. Clona il repository:
    ```bash
    git clone https://github.com/tuonome/drinkhub.git
    ```
2. Apri il progetto in Android Studio:
    - Avvia Android Studio.
    - Seleziona "Open an existing Android Studio project".
    - Naviga nella cartella in cui hai clonato il repository e seleziona il file `build.gradle` nella cartella `app`.
3. Configura il dispositivo virtuale o connetti un dispositivo fisico.

# Configurazione delle Variabili d'Ambiente
1. Copia il file di configurazione di esempio:
    ```bash
    cp app/src/main/res/raw/config.example.xml app/src/main/res/raw/config.xml
        ```
2. Apri il file `config.xml` e inserisci le tue chiavi API o altre configurazioni necessarie.

# Esecuzione dell'Applicazione
1. Avvia l'applicazione da Android Studio.
2. Seleziona il dispositivo virtuale o fisico su cui vuoi eseguire l'applicazione.
3. Clicca su "Run" in Android Studio.

# Esempio di comandi
git clone https://github.com/tuonome/progetto.git
cd progetto
npm install
npm start

# Struttura del Progetto
- `app`: Contiene il codice specifico dell'app Android.
  - `src`: Codice sorgente dell'app.
    - `main`: Codice principale dell'app.
      - `java`: Sorgente Java dell'app.
        - `com.example.drinkhub`: Package principale dell'app.
          - `gui`: Attività principali e componenti dell'interfaccia utente.
            - `MainActivity.java`: Attività principale dell'app.
          - `adapters`: Adattatori per RecyclerView o altri elementi dell'interfaccia utente.
          - `classes`: Classi del progetto (cart,product,result).
      - `res`: Risorse dell'app (layout, drawable, values, ecc.).
  - `test`: Test unitari e di strumentazione.
- `gradle`: Configurazioni e script Gradle.
- `build`: Contiene i file e le cartelle generati durante la compilazione.
- `docs`: Documentazione del progetto.
- `config`: Configurazioni specifiche dell'app.
- `README.md`: Documentazione principale del progetto.

# Diritti d'Autore
© 2024 Antonio Navarra e Vincenzo Giordano

# Contatti
navarra.antonio99@gmail.com (Antonio Navarra)
... metti il tuo vinsss

# Contributi e Feedback
Se vuoi contribuire o fornire feedback, sentiti libero di aprire una nuova issue o inviare una richiesta di pull. Siamo aperti a miglioramenti e collaborazioni!
