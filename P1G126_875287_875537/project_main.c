/*P1G126 875287 875537*/
#include "project.h"
#include "parser.h"
#include "print_exec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Progetto realizzato da:
-Bertoldi Silvia matr. 875537
-Camporese Francesco matr. 875287
Gruppo: P1G126
*/

int main (int argc, char *argv[]) /*Silvia Bertoldi*/
{
	int res;
	if (argc != 3) /*argc è il numero di argomenti passati, argv contiene le stringhe passate*/
		res = 100;
	else if (strcmp (argv[1], "esegui") && strcmp (argv[1], "stampa"))
		res = 101;
	else
	{
		int *parsed_arr = NULL, file_dim = 0; /*array di istruzioni e lunghezza dell' array*/
		res = parser (&parsed_arr, &file_dim, argv[2]); /*riempie l' array dinamico parsed_arr con le istruzioni contenute nel file, argv[2] è il nome del file*/
		if (!res) /*se il parsing è riuscito eseguo o stampo*/
		{
			if (!strcmp (argv[1], "stampa"))
				res = print_instructions (parsed_arr, file_dim);
			else
				res = execute_instructions (parsed_arr, file_dim);
			free(parsed_arr);
			parsed_arr = NULL;
		}
	}
	if (res == 999)
		res = 0; /*programma eseguito correttamente*/
	if (res) /*se è stato rilevato un errore lo stampo*/
	{
		printf ("ERRORE %d\n", res);
		switch (res)
		{
			case 1:
				printf ("STACK OVERFLOW\n");
				break;
			case 2:
				printf ("STACK UNDERFLOW\n");
				break;
			case 3:
				printf ("REGISTRO INESISTENTE\n");
				break;
			case 4:
				printf ("LO STACK NON CONTIENE ABBASTANZA ELEMENTI DA STAMPARE\n");
				break;
			case 5:
				printf ("OVERFLOW/UNDERFLOW DOVUTO AD UN CALCOLO\n");
				break;
			case 6:
				printf ("TENTATIVO DI DIVISIONE PER 0\n");
				break;
			case 7:
				printf ("RIGA INESISTENTE NEL FILE PASSATO: L' ISTRUZIONE NON ESISTE\n");
				break;
			case 100:
				printf ("QUANTITA' DI ARGOMENTI PASSATI NON CORRETTA\n");
				break;
			case 101:
				printf ("ARGOMENTO NON RICONOSCIUTO\n");
				break;
			case 200:
				printf ("FILE NON ESISTENTE \n");
				break;
			case 201:
				printf ("PROBLEMA DI ALLOCAZIONE DOVUTO AD UNA MALLOC\n");
				break;
			case 900:
				printf ("ISTRUZIONE MACCHINA NON ESISTENTE\n");
				break;
		}
	}
	return res;
}