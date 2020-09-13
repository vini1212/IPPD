#include <stdio.h>
#include <mpi.h>

void emParalelo(int myRank, int worldSize){
	int aux, dest;
	MPI_Status st;
	
	if (myRank == 0){
		MPI_Send((void*)&myRank, 1, MPI_INT, myRank+1, 0, MPI_COMM_WORLD);
		MPI_Recv(&aux, 1, MPI_INT, worldSize-1, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
		printf("Soma dos Ranks = %d\n", aux+myRank);
	} else {
		dest = (myRank == worldSize-1)?0:myRank+1;
		MPI_Recv(&aux, 1, MPI_INT, myRank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
		aux += myRank;
		MPI_Send(&aux, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
	}

	//MPI_Send( <DESCRIÇÃO DO DADO>, <DESTINO>, <TAG>, <COMUNICADOR> );
	//MPI_Recv(<DESCRIÇÃO DO DADO>, <ORIGEM>, <TAG>, <COMUNICADOR>, <STATUS> );
}

int main(int argc, char** agrv){
	int worldSize, myRank, aux = 0;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	emParalelo(myRank, worldSize);
	
	MPI_Finalize();
}   
