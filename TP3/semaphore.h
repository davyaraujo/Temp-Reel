#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <Mutex.h>
#include <monitor.h>
#include <condition_variable>
#include <stdexcept>
#include <string>
#include <iostream>


using namespace std;

class Semaphore : public  Mutex {
    public: 
        using CounterType = unsigned long;
        Semaphore(CounterType initialCounter, CounterType maxCounter);
        ~Semaphore() = default;
        void give();
        void take(Monitor& monitor);
        bool take(double timeout_ms);
    private:
        CounterType counter;
        CounterType maxCounter;
};

#endif