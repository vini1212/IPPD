/* Arquivo cliente.c : um cliente RPC simples*/

#include <stdio.h>
#include "fibonacci.h"

/* função que chama a RPC fibonacci_1*/
int fibonacci (CLIENT *clnt, int n)
{
	operands ops;
	int *result;

	/* junta os parâmetros em um struct */
	ops.n = n;

	/* chama a função remota */
	result = fibonacci_1(&ops, clnt);
	if(result == NULL)
	{
		printf("Problemas ao chamar a função remota\n");
		exit(1);
	}

	return (*result);
}

int main( int argc, char *argv[])
{
	CLIENT *clnt;
	int n;

	if (argc!=3)
	{
		fprintf(stderr, "Usage: %s hostname num1\n", argv[0]);
		exit(1);
	}

	/* cria uma struct CLIENT que referencia uma interface RPC*/
	clnt = clnt_create (argv[1], FIBONACCI_PROG, FIBONACCI_VERSION, "udp");

	/* verifica se a referência foi criada */
	if(clnt == (CLIENT *) NULL)
	{
		clnt_pcreateerror(argv[1]);
		exit(1);
	}

	/* obtém o parâmetro para realização do cálculo de fibonacci que será passado via RPC*/
	n = atoi(argv[2]);

	/* executa os procedimentos remotos */
	printf("fibonacci(%d) = %d\n", n, fibonacci (clnt, n));

	return(0);
}	