#ifndef LOOPER_H
#define LOOPER_H


#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <iomanip>
#include "../TP1/Chrono.h"
using namespace std;

class Looper {
    private:
        bool doStop;
        double iLoop;
    public:
        Looper(){

        }
        double runLoop(double nLoops = __DBL_MAX__ ){
            iLoop = 0;
            doStop = false;
            while (iLoop < nLoops && doStop == false){
                iLoop++;
            }
            return iLoop;
        }
        double getSample(){
            return iLoop;
        }
        double stopLoop(){
            doStop = true;
            return doStop;
        }
};

#endif

