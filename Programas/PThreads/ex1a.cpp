// Vinícius Renato Rocha Geraldo

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>

using namespace std;

// essa estrutura vai descrever os parâmetros que vão ser passados ao thread
typedef struct {
	/* esse parâmetros são:
	begin/end/*v -> ponteiro para o vetor (endereço de memória)
	endereço de memória onde está *acum e o endereço de memória onde está criada o *m (mutex) que é para ser manipulado para fazer o controle ao acesso
	que é dessa variável de acumulação*/
	int begin, end, *v;
	int *acum;
	pthread_mutex_t *m;
}vetorThread;

// Declara na área estática a thread e o acumulador para ser visível em todo meu programa, assim o dado é compartilhado para ser acumulado
/* Nessa área de declaração do meu programa em C/C++ ele indica que está sendo alocada na área de memória estática do processo*/

int acum; // um identificador -> a variável mesmo é um espaço de 4 bytes de mémoria na memória estática
pthread_mutex_t m; //é declarado um identificador do thread para que seja visto em todo o programa para que seja concorrente a execução

// a função recebe um ponteiro para void
void *soma(void *par){
	int i, somaL;
	vetorThread *in = (vetorThread*) par; // assim é feito uma coerção para ter um tipo que seja para o meu programa
	
	somaL = 0;
	
	for(i = in->begin; i < in->end; i++) // fazer um for da posição inicial até a posição final do vetor
		somaL += in->v[i]; //faço o acumulo local dos dados	

	// uma vez de posse desse valor local assim obtém o mutex 
	pthread_mutex_lock(&m);
	*(in->acum) += somaL; // entra na seção crítica acumulando a variável global que vai receber o somatório final 
	pthread_mutex_unlock(&m);
	// liberando o recurso da thread e acabando a execução

	/* caso seja trocada a área de obtenção do mutex pode afetar diretamente o desempenho do meu código
	pois acaba deixando mais lenta a execução por aumentar o regime de exclusão mútua onde é executado por todos os threads
	, ou seja, o programa vai ser serializado*/
	return NULL;
}

int main(int agrc, char **argv){
	int i, tam, nthreads, *vet, acum;
	pthread_t *tid;
	vetorThread *dta;
	
	acum = 0;
	
	// retira as informações do terminal como entrada
	if ( agrc != 3 ){
		fprintf(stderr, "Uso: acumula <tamanhoVetor> <numeroThreads>\n");
		exit(1);
	}

	if((tam = atoi(argv[1])) < 100){
		fprintf(stderr, "O tamanho do vetor deve ser maior ou igual a 100\n");
		exit(1);
	}
	
	if((nthreads = atoi(argv[2])) < 2){
		fprintf(stderr, "O numero de threads deve ser maior ou igual a 2\n");
		exit(1);
	}
	
	// assim é processado cada parâmetro que ele recebe dos threads como entrada dos dados e da função
	tid = (pthread_t*) malloc(nthreads*sizeof(pthread_t));
	dta = (vetorThread*) malloc(nthreads*sizeof(vetorThread)); //dta é um array de tamanho nthreads e é uma estrutura do tipo vetorThread
	vet = (int*) malloc(tam*sizeof(int));
	
	for(i = 0; i < tam; i++){
		vet[i] = i;
	}
	
	// cada thread vai calcular o somatório de um segmento desse vetor, a entrada para o thread precisa do segmento de vetor que ele vai trabalhar
	// precisa do vetor, mais indice inicial e indice final que vai percorrer
	for(i = 0; i < nthreads; i++){
		// composto um conjunto de parâmetros um a um para cada thread que vai ser criada, onde é criado um novo registro para cada thread
		//dta[i].s = tam; -> caso queira criar uma variável com o tamanho do vetor
		dta[i].v = vet;
		dta[i].begin = i*(tam/nthreads);
		dta[i].end = (i + 1)*(tam/nthreads);
		dta[i].acum = &acum;
		dta[i].m = &m;
		pthread_create( &(tid[i]), NULL, soma, (void*)&(dta[i])); //aqui está sendo passado o endereço de cada uma dessa estruturas nesse array dta
		/* tem três parâmetros para passar o begin, end e o endereço do próprio vetor para o thread que preciso criar
		a estratégia para isso é criar uma estrutura de dados que vai descrever os parâmetros que são passados ao thread*/
	}
	
	for (i = 0; i < nthreads; i++){
		// aqui utilizamos join no identificador do thread que desejamos sincronizar
		pthread_join(tid[i], (void**)NULL); // no entanto ela não retorna nenhum valor, sem nenhum resultado. O thread sincronizado é tid[i]
	}
	
	fprintf(stdout, "Soma = %d\n", acum);
	
	free(tid);
	free(dta);
	free(vet);
	
	return 0;
}
	
	
