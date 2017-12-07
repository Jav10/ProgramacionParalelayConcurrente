#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

void check_circuit (int id, int z);
int main (int argc, char *argv[]) {
   int i;
   int numeroDeHilos=strtol(argv[1],NULL,10);

   #pragma omp parallel num_threads(numeroDeHilos)
   {
   for( i = omp_get_thread_num(); i < 655356; i += numeroDeHilos)
     check_circuit (omp_get_thread_num(), i);

   printf("Proceso %d esta hecho\n", omp_get_thread_num());

   fflush (stdout);
   } 
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