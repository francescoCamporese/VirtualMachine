/*P1G126 875287 875537*/
#include "project.h"
#include <stdio.h>
#include <limits.h>

int HALT () /*Silvia Bertoldi*/
{
	return 999;
}

int DISPLAY (int pos, int val) /*Silvia Bertoldi*/
{
	if (pos >= 0 && pos < DIMREGISTERS) /*se il registro esiste*/
	{
		printf ("R%d = %d\n", pos, val);
		return 0;
	}
	else
		return 3;
}

int PRINT_STACK (int stack[], int SP, int n) /*Silvia Bertoldi*/
{
	if (n > (SP)) /*errore se gli chiedo di stampare più elementi di quelli contenuti nello stack*/
		return 4;
	else
	{
		int i;
		for (i = 1; i <= n; ++i)
			printf("[%d] = %d\n", SP - i, stack[SP - i]); /*SP è la posizione dove in caso di push inserisco un valore, quindi l' elemento più recente è in posizione SP - 1*/
		return 0;
	}
}

int PUSH (int stack[], unsigned int *SP, int val) /*Silvia Bertoldi*/
{
	if (*SP < DIMSTACK)
	{
		stack[*SP] = val;
		++(*SP);
		return 0;
	}
	else
		return 1; /*stack overflow*/
}

int POP (int stack[], unsigned int *SP, int registers[], int pos) /*Silvia Bertoldi*/
{
	if (pos >= 0 && pos < DIMREGISTERS) /*se il registro esiste*/
	{
		if (*SP != 0) /*se c'è almeno un elemento, da prelevare, nello stack*/
		{
			--(*SP);
			registers[pos] = stack[*SP];
			return 0;
		}
		else
			return 2; /*stack underflow: cerco di prelevare un elemento che non esiste*/
	}
	else
		return 3;
}

int MOV (int registers[], int pos, int n) /*Silvia Bertoldi*/
{
	if (pos >= 0 && pos < DIMREGISTERS)
	{
		registers[pos] = n;
		return 0;
	}
	else
		return 3;
}

int CALL (int stack[], unsigned int *SP, unsigned int *IP, int *instructions, int n_instructions) /*Francesco Camporese*/
{
	int res;
	res = PUSH (stack, SP, *IP + 2); /*push dell' indice dell' istruzione che si trova dopo della call*/
	if (!res)
		res = JMP (IP, instructions[*IP + 1], n_instructions); /*cambia il valore dell' IP il quale assume il valore passato alla call*/
	return res;
}

int RET (int stack[], unsigned int *SP, unsigned int *IP) /*Francesco Camporese*/
{
	if (*SP != 0)
	{
		--(*SP);
		*IP = stack[*SP]; /*assegno ad IP il valore che avevo "pushato" facendo la call*/
		return 0;
	}
	else
		return 2;
}

int JMP (unsigned int *IP, int new_IP, int n_instructions) /*Francesco Camporese*/
{
	if (new_IP >= 0 && new_IP < n_instructions)
	{
		*IP = new_IP;
		return 0;
	}
	else
		return 7; /*l' istruzione non è contenuta nell' array*/
}

int JZ (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions) /*Francesco Camporese*/
{
	if (*SP != 0)
	{
		int removed;
		POP (stack, SP, &removed, 0); /*fingo che removed sia un registro, devo immaginare removed come un array di una sola cella ovvero faccio *(removed + 0) = valore che prelevo dallo stack*/
		if (removed == 0)
			return JMP (IP, new_IP, n_instructions);
		else
		{
			*IP += 2; /*se non faccio la jump ho bisogno di passare all' istruzione dopo (come si fa per le altre funzioni in execute_instructions)*/
			return 0;
		}
	}
	else
		return 2;
}

int JPOS (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions) /*Francesco Camporese*/
{
	if (*SP != 0)
	{
		int removed;
		POP (stack, SP, &removed, 0);
		if (removed > 0)
			return JMP (IP, new_IP, n_instructions);
		else
		{
			*IP += 2;
			return 0;
		}
	}
	else
		return 2;
}

int JNEG (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions) /*Francesco Camporese*/
{
	if (*SP != 0)
	{
		int removed;
		POP (stack, SP, &removed, 0);
		if (removed < 0)
			return JMP (IP, new_IP, n_instructions);
		else
		{
			*IP += 2;
			return 0;
		}
	}
	else
		return 2;
}

int ADD (int stack[], unsigned int *SP, int registers[], int pos1, int pos2) /*Silvia Bertoldi*/
{
	if ((pos1 >= 0 && pos1 < DIMREGISTERS) && (pos2 >= 0 && pos2 < DIMREGISTERS))
	{
		if (registers[pos1] < 0 && registers[pos2] < 0)
		{
			if (registers[pos1] < (INT_MIN - registers[pos2]))
				return 5;
		}
		else if (registers[pos1] > 0 && registers[pos2] > 0)
		{
			if (registers[pos1] > (INT_MAX - registers[pos2]))
				return 5;
		}
		return PUSH (stack, SP, registers[pos1] + registers[pos2]);
	}
	else
		return 3;
}

int SUB (int stack[], unsigned int *SP, int registers[], int pos1, int pos2) /*Silvia Bertoldi*/
{
	if ((pos1 >= 0 && pos1 < DIMREGISTERS) && (pos2 >= 0 && pos2 < DIMREGISTERS))
	{
		if (registers[pos1] < 0 && registers[pos2] > 0)
		{
			if (registers[pos1] < (INT_MIN + registers[pos2]))
				return 5;
		}
		else if (registers[pos1] > 0 && registers[pos2] < 0)
		{
			if (registers[pos1] > (INT_MAX + registers[pos2]))
				return 5;
		}
		return PUSH (stack, SP, registers[pos1] - registers[pos2]);
	}
	else
		return 3;
}

int MUL (int stack[], unsigned int *SP, int registers[], int pos1, int pos2) /*Francesco Camporese*/
{
	if ((pos1 >= 0 && pos1 < DIMREGISTERS) && (pos2 >= 0 && pos2 < DIMREGISTERS))
	{
		if ((registers[pos1] == INT_MIN && registers[pos2] < 0) || (registers[pos1] < 0 && registers[pos2] == INT_MIN)) /*se entrassi nel controllo dove faccio il modulo farei -INT_MIN che equivale a INT_MAX + 1*/
			return 5;
		if ((registers[pos1] == INT_MAX && registers[pos2] < -1) || (registers[pos1] < -1 && registers[pos2] == INT_MAX)) /*underflow assicurato*/
			return 5;

		if ((registers[pos1] > 0 && registers[pos2] > 0) || (registers[pos1] < 0 && registers[pos2] < 0)) /*rendo entrambi gli operandi positivi in modo da testare il risultato (sicuramente positivo) grazie all' intero massimo*/
		{
			unsigned int i1, i2;
			if (registers[pos1] < 0)
				i1 = registers[pos1] * (-1);
			else
				i1 = registers[pos1];
			if (registers[pos2] < 0)
				i2 = registers[pos2] * (-1);
			else
				i2 = registers[pos2];
			if (i1 > (INT_MAX / i2))
				return 5;
		}
		else if (registers[pos1] > 0 && registers[pos2] < 0) /*segni discordi: il risultato sarà negativo*/
		{
			if (registers[pos1] > (INT_MIN / registers[pos2]))
				return 5;
		}
		else if (registers[pos1] < 0 && registers[pos2] > 0)
		{
			if (registers[pos1] < (INT_MIN / registers[pos2]))
				return 5;
		}
		return PUSH (stack, SP, registers[pos1] * registers[pos2]);
	}
	else
		return 3;
}

int DIV (int stack[], unsigned int *SP, int registers[], int pos1, int pos2) /*Francesco Camporese*/
{
	if ((pos1 >= 0 && pos1 < DIMREGISTERS) && (pos2 >= 0 && pos2 < DIMREGISTERS))
	{
		if (registers[pos1] == INT_MIN && registers[pos2] == -1) /*risultato > INT_MAX + 1*/
			return 5;

		if (registers[pos2] == 0) /*tentativo di divisione per zero*/
			return 6;
		else
			return PUSH (stack, SP, registers[pos1] / registers[pos2]);
	}
	else
		return 3;
}