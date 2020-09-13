// Vinícius Renato Rocha Geraldo

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <queue>

using namespace std;

// Os parâmetros para as entradas dos produtores e consumidores são os mesmos
typedef struct{
	queue<int> *b; //buffer -> onde os itens produzidos são armazenados
	int *nptotal, *nctotal; // contador dos produtores e consumidores ao realizar suas ações
	pthread_cond_t *c; // uma variável de condição 
	pthread_mutex_t *m; //um mutex onde ambos (cond_t e mutex_t) são para controlar o acesso no buffer
} Thread;

queue<int> buff;
int nptotal, nctotal;
pthread_cond_t condBuf;
pthread_mutex_t mutBuf;

// o produtor recebe um buffer como parâmetro
void* prod(void* par){
	int cont = 0;
	bool fim = false;
	int it;
	Thread *in = (Thread*) par;

	// em um laço infinito enquanto não seja produzidos os nprod
	while(fim == false){
		it = rand(); //gera um número aleátorio qualquer
		pthread_mutex_lock(in->m);//obtém o mutex
		cont++;
		in->b->push(it); //colocando o dado no buffer

		// se o size do buffer for igual a 1 quer dizer que ele estava vázio
		if(in->b->size() == 1) //essa queue contém os números de elementos e obtém o total com a função size()
			pthread_cond_signal(in->c); // necessita mandar um signal para os consumidores para saber que podem consumir
		--*(in->nptotal); // decrementando o número total de itens produzidos
		if(*(in->nptotal) <= 0)
			fim = true; // sai do laço quanto produzir tudo 
		pthread_mutex_unlock(in->m); // saindo da seção crítica permitindo que outro produtor insira seu dado ou que outro consumidor consuma
	}
	fprintf(stderr, "Produtor id[%d] = %d\n", (int)pthread_self(), cont);
	return NULL;
}

// recebem os mesmo conjuntos de dados de entrada
void* cons (void *par){
	int cont = 0;
	bool fim = false;
	int it;
	Thread *in = (Thread*) par;

	// nesse laço infinito eles tentam obter o mutex
	while(fim == false){
		pthread_mutex_lock(in->m);
		//se o número de elementos no buffer for 0 quer dizer que está vazio e assim precisando ficar em um estado de wait
		while(in->b->size() == 0) // verifica a condição para poder fazer o processamento na seção crítica, essa condição é ter um elemento no buffer
			pthread_cond_wait(in->c, in->m);
	//se não for zero ele pode entra na seção crítica pasa consumir o dado
		cont++;
		it = in->b->front();
		in->b->pop(); //consome o dado
		--*(in->nctotal); // contabiliza que mais um dado é consumido
		if(*(in->nctotal) <= 0) // se ele verificar que não existe mais dado a ser consumido, terminou o laço então entrando nessa condição
			fim = true;
		pthread_mutex_unlock(in->m);
	}
	fprintf(stderr, "Consumidor id[%d] = %d\n", (int)pthread_self(), cont);

	return NULL;
}

int main (int argc, char **argv){
	int i, nprod, ncons;
	pthread_t *ptid, *ctid;
	Thread *dta;

	if( argc != 4 ){
		fprintf(stderr, "Parâmetros -> <numElementosVetor> <numProd> <numCons>\n");
		exit(1);
	}

	if((nctotal = nptotal = atoi(argv[1])) < 100){
		fprintf(stderr, "O tamanho do vetor precisa ser maior ou igual a 100\n");
		exit(1);
	}

	if((nprod = atoi(argv[2])) < 2){
		fprintf(stderr, "O número de produtores precisa ser maior ou igual a 2\n");
		exit(1);
	}

	if((ncons = atoi(argv[2])) < 2){
		fprintf(stderr, "O número de produtores precisa ser maior ou igual a 2\n");
		exit(1);
	}

	ptid = (pthread_t*) malloc(nprod*sizeof(pthread_t));
	ctid = (pthread_t*) malloc(ncons*sizeof(pthread_t));
	
	// Uma estrutura de dados de parâmetros de entrada para os produtores e consumidores
	dta = (Thread*) malloc(sizeof(Thread));
	dta->b = &buff;
	dta->nptotal = &nptotal;
	dta->nctotal = &nctotal;
	dta->c = &condBuf;
	dta->m = &mutBuf;

	printf("Número Buffer = %d\n", *dta->nptotal);

	// São criadas nprod -> número de threads produtoras
	for(i = 0; i < nprod; i++){
		pthread_create(&(ptid[i]), NULL, prod, (void*)dta);
	}

	// São criadas ncons -> número de threads consumidoras
	for(i = 0; i < ncons; i++){
		pthread_create(&(ctid[i]), NULL, cons, (void*)dta);
	}

	// Quando ao término dessas threads sendo executadas são sincronizadas nessa parte do código
	for(i = 0; i < nprod; i++){
		pthread_join(ptid[i], (void**)NULL);
	}

	for(i = 0; i < ncons; i++){
		pthread_join(ctid[i], (void**)NULL);
	}

	free(ptid);
	free(ctid);
	free(dta);

	return 0;
}