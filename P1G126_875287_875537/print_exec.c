/*P1G126 875287 875537*/
#include "project.h"
#include "print_exec.h"
#include <stdio.h>

int print_instructions (int *parsed_arr, int file_dim) /*Silvia Bertoldi*/
{
	int i, return_value = 0;
	for (i = 0; i < file_dim && !return_value; ++i) /*scorro l' array di istruzioni*/
	{
		switch (parsed_arr[i])
		{
			case 0:
				printf ("[%d] HALT\n", i);
				break;
			case 1:
				printf ("[%d] DISPLAY R%d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 2:
				printf ("[%d] PRINT_STACK %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 10:
				printf ("[%d] PUSH R%d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 11:
				printf ("[%d] POP R%d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 12:
				printf ("[%d] MOV R%d %d\n", i, parsed_arr[i + 1], parsed_arr[i + 2]);
				i += 2;
				break;
			case 20:
				printf ("[%d] CALL %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 21:
				printf ("[%d] RET\n", i);
				break;
			case 22:
				printf ("[%d] JMP %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 23:
				printf ("[%d] JZ %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 24:
				printf ("[%d] JPOS %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 25:
				printf ("[%d] JNEG %d\n", i, parsed_arr[i + 1]);
				++i;
				break;
			case 30:
				printf ("[%d] ADD R%d R%d\n", i, parsed_arr[i + 1], parsed_arr[i + 2]);
				i += 2;
				break;
			case 31:
				printf ("[%d] SUB R%d R%d\n", i, parsed_arr[i + 1], parsed_arr[i + 2]);
				i += 2;
				break;
			case 32:
				printf ("[%d] MUL R%d R%d\n", i, parsed_arr[i + 1], parsed_arr[i + 2]);
				i += 2;
				break;
			case 33:
				printf ("[%d] DIV R%d R%d\n", i, parsed_arr[i + 1], parsed_arr[i + 2]);
				i += 2;
				break;
			default:
				return_value = 900; /*caso funzione non riconosciuta*/
				break;
		}
	}
	return return_value;
}

int execute_instructions (int *parsed_arr, int file_dim) /*Silvia Bertoldi*/
{
	int stack [DIMSTACK]; /*di dimensione 64KB*/
	unsigned int SP = 0;
	int registers [DIMREGISTERS]; /*32 registri*/
	unsigned int IP = 0;
	int return_value = 0;
	while ((int) IP < file_dim && !return_value)
	{
		switch (parsed_arr[IP])
		{
			case 0:
				return_value = HALT ();
				break;
			case 1:
				return_value = DISPLAY (parsed_arr[IP + 1], registers[parsed_arr[IP + 1]]);
				IP += 2;
				break;
			case 2:
				return_value = PRINT_STACK (stack, SP, parsed_arr[IP + 1]);
				IP += 2;
				break;
			case 10:
				return_value = PUSH (stack, &SP, registers[parsed_arr[IP + 1]]);
				IP += 2;
				break;
			case 11:
				return_value = POP (stack, &SP, registers, parsed_arr[IP + 1]);
				IP += 2;
				break;
			case 12:
				return_value = MOV (registers, parsed_arr[IP + 1], parsed_arr[IP + 2]);
				IP += 3;
				break;
			case 20:
				return_value = CALL (stack, &SP, &IP, parsed_arr, file_dim);
				break;
			case 21:
				return_value = RET (stack, &SP, &IP);
				break;
			case 22:
				return_value = JMP (&IP, parsed_arr[IP + 1], file_dim);
				break;
			case 23:
				return_value = JZ (stack, &SP, &IP, parsed_arr[IP + 1], file_dim);
				break;
			case 24:
				return_value = JPOS (stack, &SP, &IP, parsed_arr[IP + 1], file_dim);
				break;
			case 25:
				return_value = JNEG (stack, &SP, &IP, parsed_arr[IP + 1], file_dim);
				break;
			case 30:
				return_value = ADD (stack, &SP, registers, parsed_arr[IP + 1], parsed_arr[IP + 2]);
				IP += 3;
				break;
			case 31:
				return_value = SUB (stack, &SP, registers, parsed_arr[IP + 1], parsed_arr[IP + 2]);
				IP += 3;
				break;
			case 32:
				return_value = MUL (stack, &SP, registers, parsed_arr[IP + 1], parsed_arr[IP + 2]);
				IP += 3;
				break;
			case 33:
				return_value = DIV (stack, &SP, registers, parsed_arr[IP + 1], parsed_arr[IP + 2]);
				IP += 3;
				break;
			default:
				return_value = 900;
				break;
		}
	}
	return return_value;
}