#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "utils.h"

using namespace std;

#define SIZE 5000000
#define THREADS = 4;

typedef struct {
  int start, end;
  int *arr;
} Block;

bool isPrimo(int x){
    if(x < 2){
        return false;
    }

    for(int i = 2; i <= sqrt(x); i++){
        if(x % i == 0){
            return false;
        }
    }

    return true;
}

void* primo_multihilo(void* param) {
  double *acum;
  Block *block;
  int i;

  block = (Block *) paran;
  acum = new double;
  (*acum) = 0;

  for(i = block->start; i <= block->end; i++){
    if(isPrimo(i) == true){
      (*acum) += block->arr[i];
    }
  }
  
  return ((void**) acum);
}

int main(int argc, char* argv[]) {
  int correct = 1078070388;

  /*----------------------------------Secuencial--------------------------------------*/
  int count= 0;

  for(int i = 0; i<=SIZE; i++){
    if(isPrimo(i) == true){
        count += i;
    }
  }

  if(count == correct){
    cout << "EXITO!!!" << endl;
  }else{
    cout << "FALLO!!!   " << count << "   !=   " << correct << endl;
  }

  cout << "Suma final: " << count << endl;

  /*----------------------------------Multi-hilo--------------------------------------*/
  int *a, blocksize, i, j;
  double ms, result, *acum;
  Block blocks[THREADS];
  pthread_t tids[THREADS];

  a = new int[SIZE];
  fill_array(a, SIZE);

  blocksize = SIZE / THREADS;

  for(i = 0; i < THREADS; i++){
    blocks[i].arr = a;
    blocks[i].start = i * blocksize;

    if(i != (THREADS - 1)){
      blocks[i].end = (i + 1) * blocksize;
    } else{
      blocks[i].end = SIZE;
    }
  }

  ms = 0;

  for(j = 0; j < N; j++){
    start_timer();

    result = 0;

    for(i = 0; i < THREADS; i++){
      pthread_create(&tids[i], NULL, primo_multihilo, (void*) &blocks[i]);
    }

    for(i = 0; i < THREADS; i++){
      pthread_join(tids[i], (void**) &acum);
      delete acum;
    }

    ms += stop_timer();
  }
  cout << "sum = " << setprecision(5) << result << "\n";
  cout << "avg time =  " << setprecision(5) << (ms / N) << "\n";

  delete [] a;

  return 0;
}