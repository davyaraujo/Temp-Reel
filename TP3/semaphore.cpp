#include "semaphore.h"

Semaphore::Semaphore(CounterType initialCounter,CounterType maxCounter) :counter(initialCounter), 
maxCounter(maxCounter) {
    if (initialCounter > maxCounter) {
        throw std::invalid_argument("Initial counter cannot be greater than max counter");
    }
}

void Semaphore::give(){
    Mutex::Lock lock(*this);
    if (counter >= maxCounter) {
        throw std::overflow_error("Counter cannot exceed max counter");
    }
    counter++;

}

void Semaphore::take(Monitor& monitor){
    Mutex::Lock lock(*this);
    while (counter == 0) {
        Monitor::Lock monitorLock(monitor);
        monitorLock.wait();
    }
    counter--;
}

bool Semaphore::take(double timeout_ms){
    Mutex::Lock lock(*this, double(timeout_ms));
    try{
        if (counter == 0) {
            return false;
        }
        counter--;
        return true;
    }
    catch (const std::exception& e) {
        return false;
    }
}   