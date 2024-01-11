# drinkhub-university-project
Consegna numero 3 : Gestione Vendita bevande

# DrinkHub
In questo progetto verrà gestita tramite un Client in Java, utilizzando come IDE Android Studio, e un Server in C, un'applicazione che ci permetterà la gestione di vendita di un negozio di bevande online. L'obiettivo è di consentire a qualsiasi utente di registrarsi, navigare tra i prodotti disponibili, quali alcolici, analcolici e frullati, effettuare acquisti simulati e gestirne il pagamento.
I clienti possono selezionare le bevande in due modalità:
1. Utlizzando la barra di ricerca con la possibilità di aggiungere i filtri.
2. Sfruttando le liste personalizzate:
   a. Raccomandati: un elenco dei 10 drink consigliati da DrinkHub;
   b. Preferiti: un elenco di 10 drink scelti sulla base dello storico vendite;
Le informazioni relative ai prodotti e agli utenti sono conservate in un database SQL, per la precisione PostgreSQL.
Il sistema può essere accessibile tramite applicazione per cellulare o tablet, rendendo l'esperienza utente più comoda e portatile.

# Tabella dei Contenuti
- Come Iniziare
- Prerequisiti
- Installazione
- Esecuzione dell'applicazione
- Struttura del Progetto
- Diritti d'autore 
- Contatti
- Contributi e feedback

# Come Iniziare
Segui questi passaggi per configurare e avviare l'applicazione "DrinkHub" sul tuo ambiente di sviluppo.

# Prerequisiti
Prima di iniziare, assicurati di avere installato quanto segue:
- [Android Studio](https://developer.android.com/studio) (versione consigliata Hedgehog 2023 1.1)
- [Git](https://git-scm.com/)

# Creazione del Database
1. Creazione di un database in PostgreSQL
2. Una volta creato il database eseguire il dump presente all'interno del folder `database`

# Installazione
1. Clona il repository: `git clone https://github.com/AntonioNavarra/drinkhub-university-project.git`
2. Apri il progetto in Android Studio:
    a. Avvia Android Studio.
    b. Seleziona "Open an existing Android Studio project".
    c. Naviga nella cartella in cui hai clonato il repository e seleziona il file `build.gradle` nella cartella `app`.
3. Configura il dispositivo virtuale o connetti un dispositivo fisico.

# Esecuzione dell'Applicazione
1. Avvia l'applicazione da Android Studio.
2. Seleziona il dispositivo virtuale o fisico su cui vuoi eseguire l'applicazione.
3. Clicca su "Run" in Android Studio.

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
- Antonio Navarra email: navarra.antonio99@gmail.com / cell: (+39) 388 356 29 26;
- Vincenzo Giordano email: vincenzo.giordano14@studenti.unina.it / cell: (+39) 331 26 87 597.

# Contributi e Feedback
Se vuoi contribuire o fornire feedback, sentiti libero di aprire una nuova issue o inviare una richiesta di pull. Siamo aperti a miglioramenti e collaborazioni!
