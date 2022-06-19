#include <iostream>
#include <algorithm>
#include "utils.h"

const int RECTS = 1000000000;
const double PI = 3.1416;

using namespace std;

/* Mono-hilo */
double integration(double inf, double, sup, double (*fn) (double)){
    double 
}

/*Multi hilo*/
typedef struct{
    int start, end;
    double (*fn) (double);
    double dx;
    double acum;
} Block;
