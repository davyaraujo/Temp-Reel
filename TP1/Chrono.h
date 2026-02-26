#ifndef CHRONO_H
#define CHRONO_H
#include <iostream>
#include <time.h>
#include "timespec.h"


class Chrono {
    public:
        Chrono();
        timespec stop();
        void restart();
        bool isActice();
        timespec lap();
        double lap_ms();
    private:
        timespec m_startTime;
        timespec m_stopTime;

};
#endif