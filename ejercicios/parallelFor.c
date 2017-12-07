#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int sumaglobal=0;

int main(int argc, char *argv[]){
	int numeroDeHilos=strtol(argv[1],NULL,10);
	long a[20],b[20];
	long resultado=0;
	int j;
	for(j=0;j<20;j++){
		a[j]=j*j;
		b[j]=j;
	}
	int i;
	#pragma omp parallel for num_threads(numeroDeHilos) \
	reduction(+ : resultado)
	for(i=0;i<20;i++)
		resultado+=a[i]+b[i];
	printf("El resultado de la operación es %ld\n", resultado);
	return 0;
}