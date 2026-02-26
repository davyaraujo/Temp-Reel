#include <iostream> 
#include <time.h>
#include <signal.h>
#include "../TP2/looper.cpp"
#include "../TP1/Chrono.cpp"
#include "../TP2/calibrator.cpp"


int main() {
    Calibrator calib(200.0, 10);
    Looper testLp;
    Chrono ch;

    for (double t = 500.0; t <= 10000.0; t += 200.0) {
        double loops = calib.nLoops(t);
        ch.restart();
        testLp.runLoop(loops);
        ch.stop();

        std::cout << "Target: " << t << "ms | Real: " << ch.lap_ms() << "ms" << std::endl;
    }
    return 0;
}