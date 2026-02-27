#include <iostream>
#include <vector>
#include <cfloat>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "../TP2/looper.h"
#include "../TP2/calibrator.h"

using namespace std;


class CPULoop : public Looper {
    private:
        const Calibrator& calibrator;
    public:
        CPULoop(const Calibrator& calib): Looper(),calibrator(calib){}
        double runTime(double duration_ms){
            Chrono ch;
            Looper lp;
            double loops = calibrator.nLoops(duration_ms);
            ch.restart();
            this->runLoop(loops);
            ch.stop();

            double error = (ch.lap_ms() - duration_ms)/duration_ms;

            return error;
        }
};