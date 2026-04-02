#include <iostream>
#include <iomanip>

#include "../TP1/Chrono.h"
#include "../TP2/looper.h"
#include "../TP2/calibrator.h"

int main() {
    const double samplingPeriod_ms = 200.0;
    const unsigned int nSamples = 10;

    std::cout << "Calibration: samplingPeriod_ms=" << samplingPeriod_ms
              << " nSamples=" << nSamples << "\n";

    Calibrator calib(samplingPeriod_ms, nSamples);

    std::cout << "a=" << calib.getA() << " loops/ms, "
              << "b=" << calib.getB() << " loops\n";

    Looper lp;
    Chrono ch;

    std::cout << std::fixed << std::setprecision(2);

    for (double t_ms = 500.0; t_ms <= 10000.0; t_ms += 200.0) {
        const double loops = calib.nLoops(t_ms);

        ch.restart();
        lp.runLoop(loops);
        ch.stop();

        const double real_ms = ch.lap_ms();
        const double err = (real_ms - t_ms) / t_ms;

        std::cout << "Target=" << std::setw(7) << t_ms << " ms"
                  << " | Real=" << std::setw(7) << real_ms << " ms"
                  << " | Err=" << std::setw(7) << (err * 100.0) << " %"
                  << " | loops=" << std::setprecision(0) << loops
                  << std::setprecision(2)
                  << "\n";
    }

    return 0;
}