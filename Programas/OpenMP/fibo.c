#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int fiboSequencial(int n){
	int i;
	int f[n];

	f[0] = f[1] = 1;
	for(i=2; i < n; i++){
		f[i] = f[i-1] + f[i-2];
	}

	return f[n-1];
}

int fiboParalelo(int n){
	int i;
	int f[n];

	f[0] = f[1] = 1;
	#pragma omp parallel for
	for (i = 2; i < n; i++){
		f[i] = f[i-1] + f[i-2];
	}

	return f[n-1];
}

int main(int argc, char **argv){
	int n = atoi(argv[1]);

	printf("Fibonacci Sequencial(%d) = %d\n", n, fiboSequencial(n));
	printf("Fibonacci Paralelo(%d) = %d\n", n, fiboParalelo(n));

	return 0;
}