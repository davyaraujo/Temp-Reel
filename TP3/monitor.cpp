#include "monitor.h"
#include "Mutex.h"
#include <cerrno>
#include <string>


Monitor::Monitor(Mutex& mutex) : Mutex(mutex) {
    pthread_cond_init(&posixCPondId, nullptr);
}

Monitor::~Monitor() {
    pthread_cond_destroy(&posixCPondId);
}


void Monitor::notify() {
    pthread_cond_signal(&posixCPondId);
}

void Monitor::notifyAll() {
    pthread_cond_broadcast(&posixCPondId);
}

void Monitor::Lock::wait() {
    pthread_cond_wait(&mon.posixCPondId, getPosixMutexId());
}

