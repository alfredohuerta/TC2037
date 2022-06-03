#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define MAX 5000000
#define LIMIT 5

bool primo_convencional(int x){
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

/*void* task(void* param) {
  int i;

  for (i = 0; i < LIMIT; i++) {
    printf("PID = %i, TID = %li <=> i = %i\n", getpid(),
            pthread_self(), i);
  }
  pthread_exit(NULL);
}*/

int main(int argc, char* argv[]) {
  int count= 0;
  int correct = 1078070388;
  double concour;

  for(int i = 0; i<=MAX; i++){
    if(primo_convencional(i) == true){
        count += i;
    }
  }

  if(count == correct){
    cout << "EXITO!!!" << endl;
  }else{
    cout << "FALLO!!!   " << count << "   !=   " << correct << endl;
  }

  cout << "Suma final: " << count << endl;

  pthread_t tid;

  pthread_create(&tid, NULL, task, NULL);

  pthread_join(tid, NULL);

  return 0;
}