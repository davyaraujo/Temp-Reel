#include <iostream>
#include <vector>
#include <cfloat>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "calibrator.cpp"

using namespace std;


class CPULoop : public Looper {
    private:
        Calibrator& calibrator;
    public:
        CPULoop(Calibrator& calib): Looper(),calibrator(calib){}
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


int main(){
    Calibrator calib(200.0,10);
    CPULoop cpl(calib);

    for (double t = 500.0; t <= 10000.0; t += 200.0) {
        double error = cpl.runTime(t);
        cout << error << endl;
    }

    return 0;
}