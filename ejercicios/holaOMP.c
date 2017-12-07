#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void HolaMundo(void);

int main(int argc, char *argv[]){
	int numeroDeHilos=strtol(argv[1],NULL,10);

	#pragma omp parallel num_threads(numeroDeHilos)
	HolaMundo();

	return 0;
}

void HolaMundo(void){
	int my_rank=omp_get_thread_num();
	int numeroDeHilos=omp_get_num_threads();
	printf("Hola del hilo %d de %d\n",my_rank,numeroDeHilos);
}