#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "utils.h"

using namespace std;

const int size = 5000000;
const int threads = 4;

typedef struct {
  int start, end;
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

  block = (Block *) param;
  acum = new double;
  (*acum) = 0;

  for(i = block->start; i < block->end; i++){
    if(isPrimo(i) == true){
      (*acum) += i;
    }
  }
  
  return ((void**) acum);
}

int main(int argc, char* argv[]) {
  double correct = 838596693108;

  /*----------------------------------Secuencial--------------------------------------*/
  double count= 0;

  for(int i = 0; i<=size; i++){
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
  int blocksize, i, j;
  double ms, result, *acum;
  Block blocks[threads];
  pthread_t tids[threads];

  blocksize = size / threads;

  for(i = 0; i < threads; i++){
    blocks[i].start = i * blocksize;

    if(i != (threads - 1)){
      blocks[i].end = (i + 1) * blocksize;
    } else{
      blocks[i].end = size;
    }
  }

  ms = 0;

  for(j = 0; j < N; j++){
    start_timer();

    result = 0;

    for(i = 0; i < threads; i++){
      pthread_create(&tids[i], NULL, primo_multihilo, (void*) &blocks[i]);
    }

    for(i = 0; i < threads; i++){
      pthread_join(tids[i], (void**) &acum);
      result += (*acum);
      delete acum;
    }

    ms += stop_timer();
  }
  
  if(result == correct){
    cout << "EXITO!!!   " << result << endl;
  }else{
    cout << "FALLO!!!   "<< result << "   !=   " << correct << endl;
  }

  cout << "avg time =  " << setprecision(5) << (ms / N) << "ms\n";

  return 0;
}