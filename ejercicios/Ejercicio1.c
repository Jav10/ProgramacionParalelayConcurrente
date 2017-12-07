#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAESTRO 0

const int MAX_STRING = 20;

int verifica(float x){
	if(x<1){
		return 0;
	}
	else if(x<2){
		return 1;
	}
	else if(x<3){
		return 2;
	}
	else if(x<4){
		return 3;
	}
	else if(x<=5){
		return 4;
	}
}

int main(void){

	int comm_sz; 
	int my_rank;
	int i,j;
	int resultados[5]={0,0,0,0,0,};
	float numeros[20]={1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,
		4.4,3.9,0.4,4.2,4.5,4.9,0.9};

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
			for(i=0;i<pedazo;i++){
				resultados[verifica(numeros[i])]+=1;
			}
			for(i=0;i<comm_sz;i++){

				MPI_Send(&p,1,MPI_INT,i,0,MPI_COMM_WORLD);
				MPI_Send(&numeros[p],pedazo,MPI_INT,i,0,MPI_COMM_WORLD);
				p=p+pedazo;
			}
			printf("\n");
			printf("[%.2f,%.2f): ",my_rank,(my_rank+1));
			for(i=0;i<MAX_STRING;i++){
				if((numeros[i]>=my_rank) && (numeros[i]<(my_rank+1))){
					printf("*");
				}
			}
		
		}
		if(my_rank>MAESTRO){
			MPI_Recv(&p,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&numeros[p],pedazo,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			for(i=0;i<pedazo;i++){
				resultados[verifica(numeros[i])]+=1;
			}

		}

	}

	

	MPI_Finalize();
	return 0;
}