#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <time.h>
#include <iostream>
#include <cerrno>
#include "Chrono.h"
#include "timespec.h"



int main(){
    struct timespec tsp;
    struct timespec tsn;
    tsp.tv_sec = 2;
    tsp.tv_nsec = 700000000;
    
    // 2. Configurando -2.7 segundos (Normalizado)
    // -3 segundos + 300 milhões de nanosegundos = -2.7s
    tsn.tv_sec = -3;
    tsn.tv_nsec = 300000000;

    std::cout << "to ms : " << timespec_to_ms(tsp) << "ms" <<std::endl;
    std::cout << "to ms : " << timespec_to_ms(tsn) << "ms" <<std::endl;

    double t1 = -2750;

    struct timespec ts1 = timespec_from_ms(t1);

    std::cout << "from ms : " << t1 <<std::endl;
    std::cout << "from ms : " << ts1.tv_sec << " seg" <<std::endl;
    std::cout << "from ms : " << ts1.tv_nsec << " nano" <<std::endl;

    timespec_now();


    return 0;
}