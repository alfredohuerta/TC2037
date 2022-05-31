#include <iostream>
// #include <unistd.h>
// #include < pthread.h>
// #include "utils.h"

const int RENS = 30000;
const int COLS = 30000;
const int THREADS = 8;

// C = M x V
void matrixXVector(int *C, const int *M, const int *V){
    double acum;

    for(int i = 0; i < RENS; i++){
        acum = 0; 
        for(int j = 0; j < COLS; j++){
            acum += M[(i * COLS) + j] * V[i];
        }
        C[i] =  acum;
    }
}

typedef struct{
    int start, end;
    int *C, *M, *V;
} Block;

void partialMult(void *param){
    Block *block;
    double acum;

    block = (Block*) param;
    for(int i = block->start; i < block->end; i++){
        acum = 0;
        for(int j = 0; j < COLS; j++){
            acum += block->M[(i * COLS) + j] * block->V[i];
        }
        block->C[i] = acum;
    }
    pthread_exit(0);
}

int main(int argc , char* argv[]){
    int *C, *M, *V, blocksize;
    double ms, acum;
    pthread_t tids[THREADS];
    Block blocks[THREADS];

    M = new int [RENS * COLS];
    V = new int [RENS];
    C = new int [RENS];

    for (int i = 0; i < RENS; i++){
        for (int j = 0; j < COLS; j++){
            M[(i * COLS) + j] = (j + 1);
        }
        V[i] = 1;
    }

    acum = 0;
    for (int j = 0; j < N; j++){
        start_timer();
        matrixXVector(C, M, V);
        ms += stop_timer();
    }
    cout << "Mono thread" << endl;
    display_array("C = ", C);
    cout << "Time " << (ms/N) << "ms/n";

    blocksize = RENS / THREADS;
    for(int i = 0; i < THREADS){
        blocks[i].start = i * blocksize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1 ) * blocksize : RENS;
        blocks[i].C = C;
        blocks[i].M = M;
        blocks[i].V = V;
    }
    ms = 0;
    for(int j = 0; j < N; j++){
        for( int i = 0; i < THREADS; i++){
            pthread_create(&tids[i], NULL, partialMult, (void*) &blocks[i]);
        }

        for(int i = 0; i < THREADS; i++){
            pthreads_join(tids[i], NULL);
        }
    }

    delete [] M;
    delete [] V;
    delete [] C;

    return 0;
}