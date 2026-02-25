#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <time.h>
#include <iostream>
#include <cerrno>
#include "Chrono.h"

double timespec_to_ms(const struct timespec& time_ts) {
    return (time_ts.tv_sec * 1000) + (time_ts.tv_nsec/1000000.0);
}
    
struct timespec timespec_from_ms(double time_ms) {
    struct timespec ts;

    ts.tv_sec = (time_t)(time_ms / 1000.0);

    double partir_ms = time_ms - (ts.tv_sec*1000);

    ts.tv_nsec = (long)(partir_ms*1e06);

    if (ts.tv_nsec < 0) {
        ts.tv_sec -= 1;
        ts.tv_nsec += 1000000000;
    }

    return ts;
}

timespec timespec_now(){
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    std::cout << "secondes: " << abstime.tv_sec << std::endl;
    std::cout << "nanosecondes: " << abstime.tv_nsec << std::endl;
    return abstime;
}

timespec timespec_negate(const timespec& time_ts){
    timespec result;
    result.tv_sec = -time_ts.tv_sec;
    result.tv_nsec = -time_ts.tv_nsec;
    if (result.tv_sec < 0){
        result.tv_nsec -= 1;
        result.tv_sec += 1000000000; 
    }
    else if(result.tv_nsec > 1000000000)
    {
        result.tv_nsec += 1;
        result.tv_sec -= 1000000000;
    }
    return result;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts){
    timespec result;

    result.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    result.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;

    if (result.tv_nsec > 0){
        result.tv_nsec += 1;
        result.tv_sec -= 1000000000;
    }
    return result;
}

timespec timespec_sub(const timespec& time1_ts, const timespec& time2_ts){
    timespec result;

    result.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    result.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;

    if (result.tv_nsec > 0){
        result.tv_nsec -= 1;
        result.tv_sec += 1000000000;
    }
    return result;
}

void timespec_wait(const timespec& delay_ts)
{
    struct timespec duration = delay_ts;
    struct timespec rem;
    errno = 0;
    if (nanosleep(&duration,&rem) == -1)
    {
        switch (errno)
        {
        case EINTR:
            printf("interrupted by a signal"
                    "handler\n");
            break;
        case EINVAL:
            duration = rem;
            printf("tv_nsec - not in range or "
                    "tv_sec is negative\n");
            break;
        default:
            perror("nanosleep");
            break;
        }
    }
}

timespec operator- (const timespec& time_ts) {
    return {-time_ts.tv_sec, -time_ts.tv_nsec};
}

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts) {
    timespec result = {time1_ts.tv_sec + time2_ts.tv_sec, time1_ts.tv_nsec + time2_ts.tv_nsec};
    if (result.tv_nsec >= 1000000000L) {
        result.tv_sec++;
        result.tv_nsec -= 1000000000L;
    }
    return result;
}

timespec operator- (const timespec& time1_ts, const timespec& time2_ts) {
    timespec result = {time1_ts.tv_sec - time2_ts.tv_sec, time1_ts.tv_nsec - time2_ts.tv_nsec};
    if (result.tv_nsec < 0) {
        result.tv_sec--;
        result.tv_nsec += 1000000000L;
    }
    return result;
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts) {
    time_ts = time_ts + delay_ts;
    return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts) {
    time_ts = time_ts - delay_ts;
    return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts) {
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts) {
    return !(time1_ts == time2_ts);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts) {
    if (time1_ts.tv_sec < time2_ts.tv_sec) return true;
    if (time1_ts.tv_sec > time2_ts.tv_sec) return false;
    return time1_ts.tv_nsec < time2_ts.tv_nsec;
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts) {
    return time2_ts < time1_ts; 
}





// int main(){
//     struct timespec tsp;
//     struct timespec tsn;
//     tsp.tv_sec = 2;
//     tsp.tv_nsec = 700000000;
    
//     // 2. Configurando -2.7 segundos (Normalizado)
//     // -3 segundos + 300 milhões de nanosegundos = -2.7s
//     tsn.tv_sec = -3;
//     tsn.tv_nsec = 300000000;

//     std::cout << "to ms : " << timespec_to_ms(tsp) << "ms" <<std::endl;
//     std::cout << "to ms : " << timespec_to_ms(tsn) << "ms" <<std::endl;

//     double t1 = -2750;

//     struct timespec ts1 = timespec_from_ms(t1);

//     std::cout << "from ms : " << t1 <<std::endl;
//     std::cout << "from ms : " << ts1.tv_sec << " seg" <<std::endl;
//     std::cout << "from ms : " << ts1.tv_nsec << " nano" <<std::endl;

//     timespec_now();


//     return 0;
// }