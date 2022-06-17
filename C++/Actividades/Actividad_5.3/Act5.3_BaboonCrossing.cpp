#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

//Valores iniciales de la capacidad y babuinos
const int BABOONS = 10;
const int MAX_CAP = 3;

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condRight = PTHREAD_COND_INITIALIZER;
pthread_cond_t condLeft = PTHREAD_COND_INITIALIZER;

//Numero de babuinos en la cuerda
int rope_right = 0;
int rope_left = 0;

//Numero de babuinos que cruzaron
int crossed_right = 0;
int crossed_left = 0;

//funcion que cruza del lado izquierdo
void* left_crossing(void *arg){
  pthread_mutex_lock(&mutex_lock);
  while (rope_left == MAX_CAP){
    cout << "Babuino izquierdo esperando..." << endl;
    pthread_cond_wait(&condRight, &mutex_lock);
  }
  rope_left++;
  crossed_left++;
  cout << "Babuino izquierdo cruzando" << endl;
  if (rope_left == MAX_CAP || crossed_left == BABOONS){
    rope_right = 0;
  }
  pthread_mutex_unlock(&mutex_lock);
  pthread_cond_signal(&condLeft);
  pthread_exit(NULL);
}

//funcion que cruza del lado derecho
void* right_crossing(void *arg){
  pthread_mutex_lock(&mutex_lock);
  while (rope_right == MAX_CAP){
      cout << "Babuino derecho esperando..." << endl;
      pthread_cond_wait(&condLeft, &mutex_lock);
  } 
  rope_right++;
  crossed_right++;
  cout << "Babuino derecho cruzando" << endl;
  if (rope_right == MAX_CAP){
    rope_left = 0;
  }
  pthread_mutex_unlock(&mutex_lock);
  pthread_cond_signal(&condRight);
  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
  pthread_t babuino[BABOONS];

  for (int i = 0; i < BABOONS; i++){
    pthread_create(&babuino[i], NULL, left_crossing, NULL);
  }
  for (int i = 0; i < BABOONS; i++){
    pthread_create(&babuino[i], NULL, right_crossing, NULL);
  }
  for (int i = 0; i < BABOONS; i++){
    pthread_join(babuino[i], NULL);
  }

  
  cout << "Babuinos que cruzaron al lado derecho: " << crossed_right << endl;
  cout << "Babuinos que cruzaron al lado izquierdo: " << crossed_left << endl;

  pthread_mutex_destroy(&mutex_lock);
	pthread_cond_destroy(&condRight);
	pthread_cond_destroy(&condLeft);

  return 0;
}
