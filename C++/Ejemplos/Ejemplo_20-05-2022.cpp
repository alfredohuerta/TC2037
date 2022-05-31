#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 4
#define TIMES 3

void* task(void *param){
    int i, id;

    id= *((int *) param);

    for (int i = 0; i < TIMES; i++){
        printf("TID = %li - i = %i\n", pthread_self(), i)
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]){
    pthread_t tids[THREADS];
    int i;

    for(i = 0; i < THREADS; i++){
        pthread_create(&tids[i], NULL, task, (void*) &i);
    }

    for (i = 0; i < THREADS; i++)
    {
        pthread_join(&tids[i], NULL);
    }
    
    /*Una vez creados los hilos, se ejecutan de acuerdo a cómo el sistema operativo desea y sólo se pueden modificar 
    haciendo una sincronización desde el inicio.*/
    return 0;
}