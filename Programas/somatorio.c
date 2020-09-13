#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define tam 50000
#define NUM_THREADS 16

int vet[tam];

int main(int argc, char **argv){
	int i, somaL;
	double time_s, time_e;

	for(i = 0; i < tam; i++){
		vet[i] = rand()%10;
		//printf("%d\n", vet[i]);
	}

	time_s = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel for reduction(+:somaL)
		for(i = 0; i < tam; i++){
			somaL += vet[i];
		}
	

	printf("parallel sum = %d\n", somaL);
	time_e = omp_get_wtime();

	printf("O tempo levado para execução: %f\n", (time_e-time_s));
	return 0;
}