#include <stdio.h>
#include "fibonacci.h"

/* implementação da função fibonacci desejada */
int * fibonacci_1_svc (operands *argp, struct svc_req *rqstp)
{
	static int result;
	int i;
	int f[argp->n];

	printf("Requisição de chamado para fibonacci(%d)\n", argp->n);

	f[0] = f[1] = 1;

	for(i = 2; i < argp->n; i++){
		f[i] = f[i-1] + f[i-2];
	}

	result = f[argp->n - 1];

	return (&result);
}