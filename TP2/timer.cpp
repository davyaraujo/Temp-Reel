#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <signal.h>
#include <time.h>
using namespace std;


volatile int cont = 0;

void myHandler(int sig, siginfo_t* si, void* uc) {
    cont++;
    cout << "|Competeur: " << cont << endl;
}

class Timer {
    private:
        timer_t timerId;
    public:
        Timer(){
            struct sigevent sev;
            struct itimerspec its;

            struct sigaction sa;
            sa.sa_flags = SA_SIGINFO;
            sa.sa_sigaction = Timer::call_callback;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGRTMIN,&sa , nullptr);

            sev.sigev_notify = SIGEV_SIGNAL;
            sev.sigev_signo = SIGRTMIN;

            sev.sigev_value.sival_ptr = this;
            timer_create(CLOCK_MONOTONIC,&sev,&timerId);
        }   

        ~Timer(){
            timer_delete(timerId);
        }

        void start(struct timespec duration , bool isPeriodic){
            struct itimerspec its;
            its.it_value = duration;
            if (isPeriodic){
                its.it_interval = duration;
            }
            else{
                its.it_interval.tv_sec = 0;
                its.it_interval.tv_nsec = 0;
            }
            timer_settime(timerId, 0, &its, NULL);
        }
        void start_ms(long duration_ms , bool isPeriodic){
            struct timespec ts;
            ts.tv_sec = (duration_ms / 1000);
            ts.tv_nsec = (duration_ms % 1000 ) * 1000000;
            start(ts,isPeriodic);
        }
        void stop()
        {
        struct itimerspec its = {}; 
        timer_settime(timerId, 0, &its, NULL);
        }

        virtual void callback() = 0;

        static void call_callback(int sig, siginfo_t* si, void* uc)
        {
            Timer* timerInstance = static_cast<Timer*>(si->si_value.sival_ptr);
            if (timerInstance) {
                timerInstance->callback();
            }
        }
};


#endif