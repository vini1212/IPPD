#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fiboParalelo (int n){
	int r1, r2;

	if(n < 2) {
		return n;
	}

	#pragma omp task shared(r1) firstprivate(n)
	r1 = fiboParalelo(n - 1);
	

	#pragma omp task shared(r2) firstprivate(n)
	r2 = fiboParalelo(n - 2);

	#pragma omp taskwait
	 return r1+r2;
}

int main(int argc, char **argv){
	int r, n;

	n = atoi(argv[1]);

	#pragma omp parallel
	{
		#pragma omp single
		r = fiboParalelo(n); 	 
	}

	printf("Fibonacci(%d) = %d\n", n, r);

	return 0;
}

/*#include <iostream>
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define N 1000000

using namespace std;
int a[N];

int main(int argc, char const *argv[])
{
	double start, end;
    long sum1=0,sum2=0;
    long i;
    
    for (i = 0; i < N; ++i)
    {
    	a[i]=rand()%10;
    }
    
    //Serial block for array sum
    cout<<"The Serial Block:\n";
    start = omp_get_wtime( );
    for (i = 0; i < N; ++i)
    {
    	sum1+=a[i];
    }
    printf("Sum=%ld\n",sum1 );
    end = omp_get_wtime( );
    cout<<"The time taken is: "<<(end-start)<<endl;
    cout<<endl;

    //Parallel block for array sum
    cout<<"The Parallel Block:\n";
    start = omp_get_wtime( );
    #pragma omp parallel for reduction(+:sum2)
    #pragma omp_set_num_threads(4)
    for (i = 0; i < N; ++i)
    {
    	sum2 += a[i];
    }
    printf("Sum=%ld\n", sum2);
    end = omp_get_wtime( );
    cout<<"The time taken is:"<<(end-start)<<endl;

	return 0;
}       */