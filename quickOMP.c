#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
const int MAX_STRING = 20;
int pivot(int *unarray, int izq, int der);
void Quicksort(int *unarray, int izq, int der);

int main(int argc, char *argv[]){
    int arreglo[]={1,20,3,56,23,28,14,94,24,19,82,76,59,43,78,64,86,80,94,30};
    int i;
    int numeroDeHilos=strtol(argv[1],NULL,10);
    for(i=0;i<MAX_STRING;i++){
        printf("\nSin orden  ");
        printf("%d ",arreglo[i]);
                    
    }
    #pragma omp parallel num_threads(numeroDeHilos)
    {   
        #pragma omp parallel for
        for(i=0;i<20;i++){
            Quicksort(arreglo,i,19);
        }
    }
    for(i=0;i<MAX_STRING;i++){
        printf("\nOrden  ");
        printf("%d ",arreglo[i]);
                    
    }
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