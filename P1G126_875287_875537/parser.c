/*P1G126 875287 875537*/
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int parser (int **parsed_arr, int *dim, char* file_name) /*Francesco Camporese*/
{
	FILE *f_in = fopen (file_name, "r");
	if (!f_in)
		return 200;
	else
	{
		int i, instr_pos = 0, is_first_line = 1, n_chars, mem_problem = 0; /*nell' array, in posizione instr_pos salvo l' ultimo numero estrapolato dal file, mem_ctr controlla il riuscimento delle malloc*/
		char *buffer = NULL; /*contenuto di una riga, per volta*/
		size_t line_length = 0;
		while ((n_chars = (int) (getline (&buffer, &line_length, f_in))) != -1 && !mem_problem) /*per ogni riga del file*/
		{
			char *temp_line = (char*) malloc (sizeof (char) * ((int) line_length));/*array contenente caratteri numerici prima del ;*/
			if (temp_line)
			{
				int temp_pos = 0; /*posizione in cui inserire una cifra alla volta, le cifre sono tutte contenute prima del ; di ogni riga*/
				i = 0;
				while (buffer[i] != ';' && buffer[i] != '\n'  && buffer[i] != '\r') /*finchè non arrivo a fine riga o trovo un ;*/
				{
					if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '-') /*se trovo una cifra la salvo nell' array temporaneo, se ha segno negativo mi salvo il -*/
					{
						temp_line[temp_pos] = buffer[i];
						++temp_pos;
					}
					++i;
				}
				if (temp_pos > 0) /*se ho inserito almeno un numero*/
				{
					temp_line[temp_pos] = '\0'; /*così l' array temporaneo contiene una stringa di cifre*/
					if (is_first_line)
					{
						*dim = atoi (temp_line); /*salvo nell' array di istruzioni l' intero ricavato dalla stringa il quale è la dimensione dell' array di istruzioni*/
						*parsed_arr = (int*) malloc (sizeof (int) * (*dim)); /*alloco l' array di istruzioni*/
						if (parsed_arr)
							is_first_line = 0; /*d' ora in poi mi troverò dopo della prima riga*/
						else
							mem_problem = 201; /*allocazione dell' array di istruzioni*/
					}
					else
					{
						*((*parsed_arr) + instr_pos) = atoi (temp_line); /*salvo nell' array di istruzioni l' intero ricavato dalla stringa*/
						++instr_pos;
					}
				}
				free (temp_line);
				temp_line = NULL;
			}
			else
				mem_problem = 201; /*allocazione della copia della riga fallita*/
		}
		fclose (f_in);
		if (buffer)
		{
			free (buffer);
			buffer = NULL;
		}
		return mem_problem;
	}
}