P1G126 875287 875537
Francesco Camporese, Silvia Bertoldi.


COMANDI
_________________________
Compilazione: make
Esecuzione: ./progetto esegui placeholder.cvm
Stampa: ./progetto stampa placeholder.cvm

Eliminazione dei file .o e dell' eseguibile: make clean



ERRORI POSSIBILI E CAUSE
_________________________
1: push/call/add/sub/mul/div non riuscita (stack overflow)
2: pop/ret/jz/jpos/jneg non riuscita (stack underflow)
3: display/pop/mov/add/sub/mul/div non riuscita (cerco di usare un registro che non esiste)
4: print_stack non riuscita (voglio stampare più elementi di quelli contenuti nello stack)
5: add/sub/mul/(div) non riuscita (overflow/underflow dovuto agli operandi)
6: div non riuscita (tentativo di divisione per 0)
7: call/jmp/jz/jpos/jneg non riuscita (l' istruzione non esiste)
100: passo troppi/troppi pochi argomenti al main
101: argomento diverso da esegui o stampa
200: il file non esiste
201: parsing non riuscito (problema di allocazione dovuto ad una malloc)
900: print_instructions/execute_instructions (il numero non corrisponde al codice macchina di una funzione)
999: risultato HALT: non è un errore (fine esecuzione: successo)