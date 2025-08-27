# Lesson 1

## Main Topics
*   **Stile del corso e pubblico di riferimento**: Il corso è presentato in modo istintivo e operativo, senza grande preparazione a monte dei contenuti, ma con un approccio pratico per imparare a programmare programmando. È rivolto a chi sa già programmare (ad esempio in JavaScript, Ruby, Python, Go) e ha una minima conoscenza di come funzionano i computer a basso livello. La chiarezza espositiva è prioritaria, anche a costo di piccole imprecisioni che verranno colmate in seguito.
*   **Panoramica del linguaggio C**: Il C è un linguaggio molto datato, ma ha subito un'evoluzione significativa nei compilatori, pur mantenendo una sintassi e una libreria di base relativamente stabili. È considerato semplice da imparare per le sue poche idee fondamentali, ma difficile da applicare, richiedendo un allenamento mentale specifico. L'esperienza con il C è trasferibile ad altri linguaggi e viceversa.
*   **Il C come linguaggio compilato e il processo di compilazione**:
    *   Un programma C non può essere eseguito direttamente; deve essere prima compilato.
    *   La compilazione avviene tramite un **compilatore C** (es. `cc`, GCC, Clang). Viene menzionato Richard Stallman per il suo impatto sul software libero e lo sviluppo di GCC.
    *   Il compilatore trasforma il codice sorgente in un file **eseguibile** (es. `a.out`), che è un file binario in **linguaggio macchina** e include intestazioni specifiche della piattaforma.
*   **Ottimizzazioni del compilatore e generazione di assembly**:
    *   È possibile generare l'**assembly** dal codice C utilizzando l'opzione `-S` del compilatore.
    *   Il compilatore C può produrre diversi livelli di assembly con vari livelli di **ottimizzazione**, influenzando notevolmente le performance del programma.
    *   Ad esempio, l'ottimizzazione di livello 2 (`-O2`) può portare il compilatore a sostituire la funzione `printf` con la più veloce `puts` per l'output di stringhe semplici, anche modificando l'input (come la rimozione del carattere di newline) per adattarsi alla semantica della nuova funzione. Questo dimostra la raffinatezza delle ottimizzazioni dei compilatori C maturi.
*   **Direttive del preprocessore (`#include <stdio.h>`)**:
    *   Le direttive iniziano con `#` e vengono elaborate da un **preprocessore** prima della compilazione vera e propria.
    *   `#include` serve a inserire il contenuto di un file specificato nel file sorgente, come una sostituzione testuale.
    *   `stdio.h` (Standard I/O header) è un file di libreria che contiene le **intestazioni (header)** delle funzioni standard di input/output, come `printf`.
    *   Viene chiarito che `printf` fa parte della libreria standard del C, non del linguaggio C stesso, che ha un numero limitato di parole chiave (es. `return`, `int`, `void`, `while`, `if`).
*   **Prototipi di funzione**:
    *   Se `printf` non è dichiarata (ad esempio, omettendo `#include <stdio.h>`), la compilazione fallisce con un errore.
    *   Un **prototipo di funzione** (es. `int printf(const char*, ...);`) definisce il tipo di ritorno e gli argomenti che la funzione accetta, terminando con un punto e virgola, senza fornire l'implementazione.
    *   Includere un prototipo è sufficiente per il compilatore per sapere come chiamare una funzione, permettendo la generazione del codice macchina.
