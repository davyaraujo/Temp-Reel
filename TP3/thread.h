#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>

using namespace std;

class Thread {
    private:
        pthread_t posixThreadId;
        pthread_attr_t posixThreadAttrld;
        const int id;
        static void* call_run(void* v_thread);
    public:
        long duration;
        Thread(int id) : id(id){}
        ~Thread(){}
        void start(int priority = 0);
        void join();
        bool isStarted();
        long duration_ms();
        static int getMaxPrio(int policy);
        static int getMinPrio(int policy);
        static void setMainSched(int policy);
        static int getMainSched(int policy);
    protected:
        virtual void run() = 0;


}; 



#endif