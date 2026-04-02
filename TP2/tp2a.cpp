#include <iostream> 
#include <time.h>
#include <signal.h>
#include "../TP2/timer.h"
#include <unistd.h>

using namespace std;

volatile int cont = 0;

static void myHandler(int sig, siginfo_t* si, void* uc) {
    cont++;
    cout << "|Competeur: " << cont << endl;
}

int main() {
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN,&sa , nullptr);

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;

    sev.sigev_value.sival_ptr = &timerid;
    timer_create(CLOCK_MONOTONIC,&sev,&timerid);

    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500000000;   
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 500000000;
    timer_settime(timerid, 0, &its, NULL);

    while (cont < 15){
        pause();
    }

    cout << "Fin" << endl;
    timer_delete(timerid);

    return 0;
}

