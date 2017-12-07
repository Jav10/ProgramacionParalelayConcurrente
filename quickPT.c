#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_STRING = 20;
int numeroDeHilos;
int arreglo[]={1,20,3,56,23,28,14,94,24,19,82,76,59,43,78,64,86,80,94,30};

int pivot(int *unarray, int izq, int der);
void Quicksort(int *unarray, int izq, int der);
void* Llamada(void* rank);

int main(int argc, char* argv[]){

    int i;
    long hilo;
    pthread_t* manejadorDeHilos;
    for(i=0;i<MAX_STRING;i++){
        printf("\nSin orden ");
        printf("%d ",arreglo[i]);
                    
    }
    printf("\n");
    //obtener el número de hilos de la linea de comandos
    numeroDeHilos=strtol(argv[1],NULL,10);
    if((MAX_STRING%numeroDeHilos)==0){
        manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));

        for(hilo=0; hilo < numeroDeHilos; hilo++){
            pthread_create(&manejadorDeHilos[hilo],NULL,Llamada,(void*)hilo);
        }

        for(hilo=0; hilo<numeroDeHilos; hilo++){
            pthread_join(manejadorDeHilos[hilo],NULL);
        }
        free(manejadorDeHilos);

        Quicksort(arreglo,0,19);
        printf("\n");
        for(i=0;i<MAX_STRING;i++){
        printf("\nOrden proceso principal ");
        printf("%d ",arreglo[i]);
                    
        }

    }
    else{
        printf("El número de procesos no es adecuado para la operación\n");
    }
    
    return 0;
}

int pivot(int *unarray, int izq, int der)
{
    int i;
    int pivote, valor_pivote;
    int aux;

    pivote = izq;
    valor_pivote = unarray[pivote];
    for (i=izq+1; i<=der; i++){
        if (unarray[i] < valor_pivote){
                pivote++;
                aux=unarray[i];
                unarray[i]=unarray[pivote];
                unarray[pivote]=aux;

        }
    }
    aux=unarray[izq];
    unarray[izq]=unarray[pivote];
    unarray[pivote]=aux;
    return pivote;
}

void Quicksort(int *unarray, int izq, int der)
{
     int pivote;
     if(izq < der){
        pivote=pivot(unarray, izq, der);
        Quicksort(unarray, izq, pivote-1);
        Quicksort(unarray, pivote+1, der);
     }
}

void* Llamada(void* rank){
    long my_rank=(long)rank;
    int i;
    if(my_rank==0){
        Quicksort(arreglo,0,4);
        for(i=0;i<5;i++){
            printf("\norden proceso %ld ",my_rank);
            printf("%d ",arreglo[i]);
                    
        }
    }
    else if(my_rank==1){
        Quicksort(arreglo,5,9);
        for(i=5;i<10;i++){
            printf("\norden proceso %ld ",my_rank);
            printf("%d ",arreglo[i]);
                    
        }
    }
    else if(my_rank==2){
        Quicksort(arreglo,10,14);
        for(i=10;i<15;i++){
            printf("\norden proceso %ld ",my_rank);
            printf("%d ",arreglo[i]);
                    
        }
    }
    else if(my_rank==3){
        Quicksort(arreglo,15,19);
        for(i=15;i<20;i++){
            printf("\norden proceso %ld ",my_rank);
            printf("%d ",arreglo[i]);
                    
        }
    }
    return NULL;
}