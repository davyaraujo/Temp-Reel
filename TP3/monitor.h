#ifndef MONITOR_H
#define MONITOR_H

#include "Mutex.h"

class Monitor : public Mutex {
    private:
        pthread_cond_t posixCPondId;
    public:
        class Lock;     
        Monitor(Mutex& mutex);
        virtual ~Monitor();
        void notify();
        void notifyAll();  
};

class Monitor::Lock : public Mutex::Lock {
    public:
        Lock(Monitor& monitor) : Mutex::Lock(monitor) , mon(monitor) {}
        Lock(Monitor& monitor, long timeout_ms) : Mutex::Lock(monitor, timeout_ms) , mon(monitor) {}
        ~Lock() = default;
        void wait();
        void wait(long timeout_ms);
    protected:
        Monitor& mon;
};

#endif
