#include <stdio.h>
#include <string.h>

const int MAX_STRING=100;

int main(void){

	int arreglo_enteros[MAX_STRING];

	for(int i=0; i<MAX_STRING; i++){
		arreglo_enteros[i]=i;
	}

	int suma=0;
	for(int i=0; i<MAX_STRING; i++){
		suma+=arreglo_enteros[i]=i;
	}

	printf("resultado suma: %d\n", suma);

}