#include <iostream>



using namespace std;

const int MAX = 10;
int acum = 0;

void* add(void *param){
    for(int i  0; i < MAX; i++){
        acum = acum + 1;
        cout << "Add acum = " << acum << "\n";
    }
    pthreads_exit(0);
}

void* sub(void *param){
    for(int i = 0; i < MAX; i++){
        acum = acum - 1;
        cout << "sub acum = " << acum << "\n";
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, add NULL);
    pthread_create(&t2, NULL, add NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

/**
 * condición de carrera: cuando uno o más hilos llevan a cabo un conjunto de instrucciones accediento a un mismo 
 * conjunto de datos o recursos, por lo que no es posible repetir las instrucción así como saber el resultado.
 * Esto se soluciona haciendo uso de herramientas de sincronización. COmo el semáforo de Dixstra.
 * Las operaciones atómicas son aquellas que no pueden desalojarse del procesador hasta haber completado sus instrucciones
 */