#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]){
	int numeroDeHilo=strtol(argv[1],NULL,10);

	int x=5;

	#pragma omp parallel num_threads(numeroDeHilo) private(x)
	{
		int my_rank=omp_get_thread_num();
		//printf("Este es el valor de x=%d en el hilo %d antes de la operación\n",x,my_rank);
		x=my_rank*2+2;
		printf("Este es el valor de x=%d en el hilo %d después de la operación\n",x,my_rank);
	}

	printf("Este es el valor de x=%d en el hilo principal\n",x);

	return 0;
}