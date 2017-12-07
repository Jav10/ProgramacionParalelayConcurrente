#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAESTRO 0
const int MAX_STRING = 20;

int pivot(int *unarray, int izq, int der);
void Quicksort(int *unarray, int izq, int der);

int main(){

    int comm_sz; 
    int my_rank;
    int arreglo[]={1,20,3,56,23,28,14,94,24,19,82,76,59,43,78,64,86,80,94,30};
    int ordenado[20];
    int i;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int tareas= MAX_STRING % comm_sz;
    int pedazo= 20/comm_sz;
    int p=pedazo;

    if(tareas!=0){
        printf("El número de procesos no es adecuado para la operación\n");
    }
    else{
        if(my_rank==MAESTRO){
            printf("Arreglo sin ordenar\n");
            for(i=0;i<MAX_STRING;i++){
                printf("\nSin orden ");
                printf("%d ",arreglo[i]);
                    
            }
        }  
        int local[pedazo];
        MPI_Scatter(arreglo,pedazo,MPI_INT,local,pedazo,MPI_INT,MAESTRO,MPI_COMM_WORLD);
            
        Quicksort(local,0,pedazo-1);
            
        MPI_Gather(local,pedazo,MPI_INT,ordenado,pedazo,MPI_INT,MAESTRO,MPI_COMM_WORLD);
        
        if(my_rank==MAESTRO){
            printf("\n\nTrozos reunidos con MPI_Gather\n");
            for(i=0;i<MAX_STRING;i++){
                printf("\norden con procesos ");
                printf("%d ",ordenado[i]);
                    
            }
            printf("\n");
            Quicksort(ordenado,0,19);
            for(i=0;i<MAX_STRING;i++){
                printf("\norden final con MAESTRO ");
                printf("%d ",ordenado[i]);
                    
            }
        }

    }

    MPI_Finalize();
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