# drinkhub-university-project
Consegna numero 3 : Gestione Vendita bevande

# DrinkHub
client critto in java (Android Studio) e server in C (Visual Studio Code) ci hanno permesso di creare un bar virtuale per la vendita di bevande. L'obiettivo è di consentire a qualsiasi utente (cliente) di registrarsi, navigare tra i prodotti disponibili (alcolici,analcolici,frullati), effettuare acquisti simulati e gestirne il pagamento. I clienti possono selezionare le bevande in due modalità: 1) Utlizzando la barra di ricerca con la possibilità di aggiungere i filtri. 2) Sfruttando le liste personalizzate "raccomandati" (Elenco dei 10 drink consigliati da DrinkHub) o "preferiti" (Elenco di 10 drink scelti sulla base dello storico vendite).
Le informazioni relative ai prodotti e agli utenti sono conservate in un database SQL (PostgreSQL).
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

# Installazione
1. Clona il repository:
    ```bash
    git clone https://github.com/AntonioNavarra/drinkhub-university-project.git
    ```
2. Apri il progetto in Android Studio:
    - Avvia Android Studio.
    - Seleziona "Open an existing Android Studio project".
    - Naviga nella cartella in cui hai clonato il repository e seleziona il file `build.gradle` nella cartella `app`.
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
- Antonio Navarra email: navarra.antonio99@gmail.com / cell: (+39) 3883562926
- Vincenzo giordano email: vincenzo.giordano14@studenti.unina.it / cell: (+39) 3312687597;


# Contributi e Feedback
Se vuoi contribuire o fornire feedback, sentiti libero di aprire una nuova issue o inviare una richiesta di pull. Siamo aperti a miglioramenti e collaborazioni!
