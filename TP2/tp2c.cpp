#include <iostream>
#include <iomanip>
#include <cstdlib>      // strtod
#include "../TP1/Chrono.h"
#include "looper.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <nLoops>\n";
        return 1;
    }

    char* end = nullptr;
    double nLoops = std::strtod(argv[1], &end);
    if (end == argv[1] || *end != '\0' || nLoops < 0) {
        std::cerr << "Invalid nLoops: " << argv[1] << "\n";
        return 1;
    }

    Looper looper;
    Chrono chrono;

    chrono.restart();
    looper.runLoop(nLoops);
    chrono.stop();

    double time_s = chrono.lap_ms() / 1000.0;

    std::cout << std::fixed
              << "nLoops=" << std::setprecision(0) << nLoops
              << " time_s=" << std::setprecision(2) << time_s
              << "\n";
    return 0;
}