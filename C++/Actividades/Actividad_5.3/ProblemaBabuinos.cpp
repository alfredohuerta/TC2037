#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

using namespace std;

const int size = 10;
const int herd = 20;
const int cap = 3;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef enum {RIGHT, LEFT} Position;

typedef struct{
    int cap = 3;
    int current;
    bool status;
} Rope;

typedef struct{
    int id;
    Position position;
} Baboon;

typedef struct{
    Baboon baboons;
    Rope rope;
}Bridge;

Baboon* baboons[size];
pthread_t tids[size];

void print_crossing(int id){
    cout << "Baboon " << id <<" crossing..." << endl;
}

void cross(Baboon *baboon, Rope *rope){
    int resting = 10;
    
    if (rope->current <= rope->cap){
        print_crossing(baboon->id);

        rope->current = rope->current -1;
        if(baboon->position == LEFT){
            baboon->position = RIGHT;
        }else{
            baboon->position = LEFT;
        }
    }else{
        pthread_mutex_unlock(&mutex);
        sleep(resting);
    }

}

void* task(void *param){
    Bridge *bridge = (Bridge *) param;

    pthread_mutex_lock(&mutex);

    for(int i = 0; i <= size; i++){
        cross(bridge->baboons, bridge->rope);
    }

    return ( (void *) 0 );
}

int main (int argc, char* argv[]){
    for (int i = 0; i <= size; i++){
        baboons[i] = (Baboon *) malloc(sizeof(Baboon));
        baboons[i]->id= i;
        baboons[i]->position = LEFT;

        pthread_create(&tids[i], NULL, task, baboons[i]);
    }

    for (int i = 0; i <= size; i++){
        baboons[i] = (Baboon *) malloc(sizeof(Baboon));
        baboons[i]->id= i;
        baboons[i]->position = RIGHT;

        pthread_create(&tids[i], NULL, task, baboons[i]);
    }

    for (int i = 0; i < herd; i++) {
    pthread_join(tids[i], NULL);
    free(baboons[i]);
    }

    return 0;
}