#include <stdio.h>
#include <mpi.h>


int main(void){
	int comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank == 0){
		for(int q=1; q<comm_sz;q++){
			MPI_Send(&q, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
		}
		printf("El valor de my_rank %d \n", my_rank);
		for(int q=1; q<comm_sz;q++){
			int res;
			MPI_Recv(&res, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Se imprime el resultado %d\n", res);
		}
		
	}
	else{
		int res;
		MPI_Recv(&res, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int cuadrado = res*res;
		MPI_Send(&cuadrado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}