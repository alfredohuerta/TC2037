#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h" //buscar en el repo del profe

#define SIZE 1e9

double sum(int* arr, int size){
    double acum= 0;
    int i;

    for(i = 0; i < SIZE; i++){
        acum += arr[i];
    }
}

int main(int argc, char* argv[]){
    int *arr, i;
    double result, ms;
    /**debido a que el funcionamiento de los hilos está subordinada al poder de procesamiento que tenga el procesador 
     * en ese momento, sólo puede medirse la complejidad del algoritmo usando el tiempo que tarda, por lo que se corre
     * diez veces el programa y se promedia el tiempo.
    */

   arr= (int *) malloc(sizeof(int) * SIZE); //arr = new int[SIZE]
   fill_array(arr, SIZE);
   display_array("array =", arr);

   ms= 0; 

   for(i= 0; i < N; i++){
       star_timer();
       result = sum(array, SIZE);
       ms += stop_timer();
   }

   printf("result = %lf\n", result);
   printf("time %.2lf ms\n", (ms/N));

   free(arr);

    return 0;
}