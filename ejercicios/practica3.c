#include <stdio.h>
#include <mpi.h>

int main(void){
	int comm_sz; // Número de procesos
	int my_rank; // Nombre de procesos

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank==0){

		int proceso0=1;
		MPI_Send(&proceso0,1,MPI_INT,1,0,MPI_COMM_WORLD);

		int resultadoGlobal;
		MPI_Recv(&resultadoGlobal,1,MPI_INT,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

		printf("El valor total de la suma es %d\n",resultadoGlobal );
	}
	else if(my_rank==1){

		int mi_variable;
		MPI_Recv(&mi_variable,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int resultado=mi_variable+1;
		MPI_Send(&resultado,1,MPI_INT,2,0,MPI_COMM_WORLD);
	}
	else if(my_rank==2){

		int mi_variable;
		MPI_Recv(&mi_variable,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int resultado=mi_variable+2;
		MPI_Send(&resultado,1,MPI_INT,3,0,MPI_COMM_WORLD);

	}
	else if(my_rank==3){

		int mi_variable;
		MPI_Recv(&mi_variable,1,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int resultado=mi_variable+3;
		MPI_Send(&resultado,1,MPI_INT,0,0,MPI_COMM_WORLD);

	}
	MPI_Finalize();
	return 0;
}