#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int numeroDeHilos;
void check_circuit (int id, int z);
void* Llamada(void* rank);
int main (int argc, char *argv[]) {
   long hilo;
   pthread_t* manejadorDeHilos;
   numeroDeHilos=strtol(argv[1],NULL,10);
   manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));
   for(hilo=0; hilo < numeroDeHilos; hilo++){
      pthread_create(&manejadorDeHilos[hilo],NULL,Llamada,(void*)hilo);
    }

    for(hilo=0; hilo<numeroDeHilos; hilo++){
      pthread_join(manejadorDeHilos[hilo],NULL);
    }
    free(manejadorDeHilos);
   return 0;

}

#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

void check_circuit (int id, int z)
{
  int v[16];
  int i; 


   for(i=0; i<16; i++) v[i] = EXTRACT_BIT(z,i);

if((v[0] || v[1]) && (!v[1] || !v[3]) &&(v[2] || v[3])&& (!v[3] || !v[4]) && (v[4] || !v[5]) && (v[5] || !v[6]) && (v[5] || v[6])&& (v[6] || !v[15]) && (v[7] || !v[8]) && (!v[7] || !v[13]) && (v[8] || v[9]) && (v[8] || !v[9]) && (!v[9] || !v[10]) && (v[9] || v[11]) && (v[10] || v[11]) && (v[12] || v[13]) && (v[13] || !v[14]) && (v[14] || v[15])) 
    {
    printf("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", id,v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15]);
       fflush (stdout);
   }
}

void* Llamada(void* rank){
  int i;
  int my_rank=(long)rank;
  for( i = my_rank; i < 655356; i += numeroDeHilos)
     check_circuit (my_rank, i);

   printf("Proceso %d esta hecho\n", my_rank);

   fflush (stdout);
   return NULL;
}