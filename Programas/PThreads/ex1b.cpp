// Vinícius Renato Rocha Geraldo

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

using namespace std;

typedef struct 
{
	int s, begin, end, *v;

}vetorThread;

//Essa implementação não manipula uma área de dados compartilhada
void *soma(void *par){
	//faz a soma local e localmente existe o resultado retornando a soma parcial realizada
	int i, *somaL;
	vetorThread *in = (vetorThread*) par;

	somaL = (int*) malloc(sizeof(int)); //cada um dos threads alocam uma área de memória no heap
	// Utilizando essa área de memória para fazer o acumulo desse resultado parcial
	*somaL = 0;

	for (i = in->begin; i < in->end; i++)
	{
		*somaL += in->v[i];
	}

	return somaL; //retornado o endereço de memória onde o valor do acumulado está armazenado
	// Assim o mutex não vai existir nessa implementação pois para obter um mutex necessita de uma área de dados compartilhada
}

int main(int argc, char **argv)
{
	int i, tam, nthreads, *vet, acum, *aux;
	pthread_t *tid;
	vetorThread *dta;

	if(argc != 3){
		fprintf(stderr, "Falta de parâmetros ou excedente, esses são: <tamanhoVetor> <numeroThreads\n");
		exit(1);
	}

	if((tam = atoi(argv[1])) < 100){
		fprintf(stderr, "O tamanho do vetor precisa ser maior ou igual a 100");
		exit(1);
	}

	if((nthreads = atoi(argv[2])) < 2){
		fprintf(stderr, "O número de threads necessita ser maior ou igual a 2");
		exit(1);
	}

	tid = (pthread_t*) malloc(nthreads*sizeof(pthread_t));
	dta = (vetorThread*) malloc(nthreads*sizeof(vetorThread));
	vet = (int*) malloc(tam*sizeof(int));

	for(i = 0; i < tam; i++)
	{
		vet[i] = i;
	}

	// parâmetros de entrada são os mesmos, porém sem a declaração do mutex pois necessita de uma área de dados compartilhadas
	for(i = 0; i < nthreads; i++){
		//dta[i].s = tam;
		dta[i].v = vet;
		dta[i].begin = i*(tam/nthreads);
		dta[i].end = (i+1)*(tam/nthreads);
		pthread_create(&(tid[i]), NULL, soma, (void*)&(dta[i]));
	}

	acum = 0;
	// join está recebendo o resultado do cálculo parcial
	for (i = 0; i < nthreads; i++){
		// o aux é um ponteiro para um inteiro, para atualizar o endereço contido nesse ponteiro necessita fazer passando como dado um ponteiro de um ponteiro para voida
		// &aux -> endereço de um ponteiro de memória
		pthread_join(tid[i], (void**)&aux); // Esses endereços são recebidos e colocados em um resultado que a variável aux está se referenciando
		acum += *aux;
		free(aux);

		/* o endereço da área alocada para cada thread onde utilizam a acumulação na memória é recolhido no join, depois que não é mais necessária é liberada*/
	}

	fprintf(stderr, "Soma = %d\n", acum);

	free(tid);
	free(vet);
	free(dta);

	return 0;
}