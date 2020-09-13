/* fibonacci.x : definicação da interface */

#define PROGRAM_NUMBER 12345678
#define VERSION_NUMBER 1

/* tipo de dado que será passado aos procedimentos remotos */

struct operands
{
	int n;
};

/* Definição da interface que será oferecida aos clientes */

program FIBONACCI_PROG
{
	version FIBONACCI_VERSION
	{
		int FIBONACCI (operands) = 1;
	}
	= VERSION_NUMBER;
}
= PROGRAM_NUMBER;