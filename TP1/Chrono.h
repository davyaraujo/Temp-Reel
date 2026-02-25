#ifndef CHRONO_H
#define CHRONO_H
#include <iostream>
#include <time.h>

double timespec_to_ms(const struct timespec& time_ts);
struct timespec timespec_from_ms(double time_ms);
timespec timespec_now();
timespec timespec_negate(const timespec& time_ts);
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);
timespec timespec_sub(const timespec& time1_ts, const timespec& time2_ts);
void timespec_wait(const timespec& delay_ts);

// --- Operator Overloads ---
timespec operator- (const timespec& time_ts);
timespec operator+ (const timespec& time1_ts, const timespec& time2_ts);
timespec operator- (const timespec& time1_ts, const timespec& time2_ts);
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);
bool operator== (const timespec& time1_ts, const timespec& time2_ts);
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);
bool operator< (const timespec& time1_ts, const timespec& time2_ts);
bool operator> (const timespec& time1_ts, const timespec& time2_ts);

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