/* Capitolo 25 Esercizio 16
Formulare 20 regole di stile di codifica (non limitarsi a copiare quelle in §25.6). 
Applicali a un programma di più di 300 righe che hai scritto di recente. 
Scrivi un breve commento (una o due pagine) sull'esperienza di applicazione di tali regole. 
Hai trovato errori nel codice? Il codice è diventato più chiaro? Alcuni codici sono diventati meno chiari? Ora modifica l'insieme di regole in base a questa esperienza.
*/

// *** Regole
/*
*  1. Dopo ogni nome di blocco codice (di funzione, classe, template ecc..) si apre la parentesi graffa e si va a capo (semplifica la lettura)
*  2. Le parentesi che delimitano il codice devono essere sempre in colonna e il codice un tab rientrato.
*  3. ogni blocco di codice come funzioni o anche cicli devono avere una riga vuota prima e dopo il blocco (semplifica l'individuazione dei blocchi
*  4. Ogni blocco di codice deve avere una riga di commento appena sopra il blocco per spiegare l'esistenza di quel blocco (semplifica l'individuazione e la comprensione del codice)
*  5. I commenti lunghi vanno messi in un blocco di commenti, slah asterisco, in modo da individuare testi che spiegano l'intero programma e non una sola porzione del programma
*  6. Per delimitare una sezione di codice che si ripete o che va rivista usare una riga di commento con 3 asterischi // *** per semplificare l'individuazione del blocco
*  7. I nomi di variabili sono scritte tutte in minuscolo e senza spazi, se serve lo spazio per avere un nome più chiaro usare lo underscore
*  8. I nomi di tipi definiti iniziano con una lettera maiuscola: ad esempio il tipo definito Risorsa e la variabile risorsa di tipo Risorsa
*  9. In caso di nomi variabili e tipi o template con nomi simili si può usare un prefisso seguito da underscore per individuare meglio la funzione di quel nome: ad esempio type_Risorsa e risorsa
* 10. Nei template, per definire i tipi dei parametri usare typedef per quei tipi già definiti dal linguaggio e class per i propri tipi
* 11. Se un un if non necessita del blocco codice l'unica istruzione segue sulla stessa riga, semplifica la lettura
* 12. Se ad if segue else vale la stessa regola, per una sola istruzione continua sulla riga dell'if altrimenti si parte dalla riga successiva con else { e a capo il codice fino all'ultima riga con la chiusura
* 13. Usare sempre le parentesi tonde per delimitare una serie di operazioni e far capire che il risultato aspettato è proprio lo svolgimento della parentesi,
*     ad esempio se usiamo una espressio come parametro da passare tipo funzione(origine + media) diventa funzione( (origine + media) ) in modo da esaltare di voler passare il risultato della parentesi
* 14. quando ci sono parentesi che si susseguono dividerle con uno spazio per meglio identificare il blocco di istruzioni che racchiude
* 15. usare uno spazio anche tra variabili e operatori o istruzioni, uno spazio prima e uno spazio dopo per semplificare la lettura e la loro individuazione
* 16. Usare un blocco di commenti nel file dove si risiede la funzione main() prima di ogni cosa per spiegare il programma
* 17. Includere le librerie dopo il blocco di codice separato da una riga vuota sopra e sotto il blocco degli #include, elencati in ordine di utilizzo e possibilmente commentando il loro utilizzo
* 18. Commentare l'esistenza delle variabili o tipi definiti
* 19. Dove i commenti brevi si alternano alle linee di codice che altrimenti starebbero meglio in blocco mettere il commento alla fine della riga di istruzione, 
*     ad esempio quando si spiega l'utilizzo della singola variabile in blocco di variabili dichiarate
* 20. Incolonnare sempre le righe anche nei blocchi di commenti come questo, semplifica la ricerca di informazioni all'interno dello stesso.
* 21. usare dei propri file header per tutte le funzioni e tipi definiti per lasciare il più pulito possibile il file principale.
* 22. Restringere il più possibile lo scope delle variabili, ad esempio se una variabile è utilizzata nel ciclo for non dichiararla in uno scope più globale
* 23. Non usare nomi duplicati per le variabili anche se hanno vita in blocchi diversi di codice perché potrebbero confondere sull'aspettativa del loro valore durante la programmazione.
*/

// *** Esercizio
/* 
* E' stato scelto l'eserizio precedente che una volta fatto non è stato rivisto come molti esercizi fatti per questo libro,
* sarà rivisto in questa occasione con le regole che utilizzo solitamente.
* E' stato copiato il file originale dell'esercizio 15 in esercizio15_originale e sarà creato uno o più file con prefisso 'esercizio15_'
* di cui il principale che ha la funzione main() sarà esercizio15_rivisto
* Per provare che il tutto funziona ancora la funzione main() sarà lasciata solo nel file rivisto, questo file avrà solo commenti e il file originale sarà interamente commentato.
*/

