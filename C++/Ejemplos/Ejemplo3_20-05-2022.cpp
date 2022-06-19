#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

#define THREADS 8

typedef struct {
    int start, end;
    int *arr;
    double acum;
} Data;

void* partial_sum(void *param){
    Data *data;
    int i;

    data = (Data*) param;
    data->acum = 0;

    for(i= data->start; i < data->end; i++){
        data->acum = data->arr[i];
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]){
    pthread_t tids[THREADS];
    Data data[THREADS];
    int *arr, j, i, block;
    double result, ms;

    arr= (int*) malloc(sizeof(int) * SIZE);
    fill_array(arr, SIZE);
    display_array("array =", arr);

    block = SIZE/THREADS;

    for (i = 0; i < THREADS; i++)
    {
        data[i].arr;
        data[i].start = i * block;
        data[i].end = (i != (THREADS - 1))? ((i +1) * block) : SIZE;
        data[i].acum = 0;
    }

    ms = 0;
    for(i= 0; i < N; i++){
        start_timer();

        for(j= 0; j < THREADS; j++){
            pthread_create(&tids[i], NULL, partial_sum, (void*) &data[i])
        }

        result = 0;

        for(j= 0; j < THREADS; j++){
            pthread_join(tids[i], NULL);
            result += data[i].acum;
        }

        ms += stop_timer();
    }

    printf("result = %lf\n", result);
   printf("time %.2lf ms\n", (ms/N));

   free(arr);

   return 0;
}