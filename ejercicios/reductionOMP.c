#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int Suma(int a, int b);
int sumaglobal=0;
int main(int argc, char *argv[]){
	int numeroDeHilos=strtol(argv[1],NULL,10);
	int resultado=0;
	int a=10, b=20;
	#pragma omp parallel num_threads(numeroDeHilos) \
		reduction(+ : resultado)
	resultado+=Suma(a,b);
	printf("El resultado de la operación es %d\n", resultado);
	return 0;
}

int Suma(int a, int b){
	int my_rank=omp_get_thread_num();
	int numeroDeHilos=omp_get_num_threads();
	int mi_suma=a+b;
	printf("Suma del hilo %d de %d: %d\n",my_rank, numeroDeHilos, mi_suma);
	return mi_suma;
}