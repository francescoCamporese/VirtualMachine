/*P1G126 875287 875537*/
#define DIMSTACK 16384
#define DIMREGISTERS 32

int HALT ();
int DISPLAY (int pos, int val);
int PRINT_STACK (int stack[], int SP, int n);
int PUSH (int stack[], unsigned int *SP, int val);
int POP (int stack[], unsigned int *SP, int registers[], int pos);
int MOV (int registers[], int pos, int n);
int CALL (int stack[], unsigned int *SP, unsigned int *IP, int *instructions, int n_instructions);
int RET (int stack[], unsigned int *SP, unsigned int *IP);
int JMP (unsigned int *IP, int new_IP, int n_instructions);
int JZ (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions);
int JPOS (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions);
int JNEG (int stack[], unsigned int *SP, unsigned int *IP, int new_IP, int n_instructions);
int ADD (int stack[], unsigned int *SP, int registers[], int pos1, int pos2);
int SUB (int stack[], unsigned int *SP, int registers[], int pos1, int pos2);
int MUL (int stack[], unsigned int *SP, int registers[], int pos1, int pos2);
int DIV (int stack[], unsigned int *SP, int registers[], int pos1, int pos2);