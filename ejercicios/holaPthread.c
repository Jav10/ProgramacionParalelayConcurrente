#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variable global accesible a todos los hilos
int numeroDeHilos;

void* Hola(void* rank); //Función del Hilo

int main(int argc, char* argv[]){
	long hilo;
	pthread_t* manejadorDeHilos;
	//obtener el número de hilos de la linea de comandos
	numeroDeHilos=strtol(argv[1],NULL,10);

	manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));

	for(hilo=0; hilo < numeroDeHilos; hilo++){
		pthread_create(&manejadorDeHilos[hilo],NULL,Hola,(void*)hilo);
	}
	printf("Hola del hilo principal\n");

	for(hilo=0; hilo<numeroDeHilos; hilo++){
		pthread_join(manejadorDeHilos[hilo],NULL);
	}
	free(manejadorDeHilos);

	return 0;
}

void* Hola(void* rank){
	long my_rank=(long)rank;
	printf("Hola desde el hilo %ld de %d\n",my_rank,numeroDeHilos );
	return NULL;
}