#include <thread>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include "thread.h"
#include "../TP1/Chrono.h"


Thread::Thread(int id) : id(id) {
    pthread_attr_t posixThreadAttrld;
    pthread_attr_init(&posixThreadAttrld);
    this->posixThreadAttrld = posixThreadAttrld;
}
Thread::~Thread(){
    pthread_attr_destroy(&posixThreadAttrld);
}

void Thread::start(int priority){
    sched_param schedParams;
    schedParams.sched_priority = priority;
    pthread_attr_setschedparam(&posixThreadAttrld,&schedParams);
    pthread_create(&posixThreadId, &posixThreadAttrld, call_run, this);
}

void Thread::join(){
    pthread_join(posixThreadId, NULL);
}

bool Thread::isStarted(){
    return posixThreadId != 0;
}

void Thread::run(){
    std::cout << "Exec" << std::endl;
}

void* Thread::call_run(void* v_thread){
    Thread* th = (Thread*)v_thread;    
    Chrono ch;
    ch.restart();
    th->run();
    th->duration = ch.lap_ms();
    return nullptr;

}

long Thread::duration_ms(){
    if(isStarted())
    {
        return duration;
    }
    return -1;
}

int Thread::getMaxPrio(int policy){
    return sched_get_priority_max(policy);
}

int Thread::getMinPrio(int policy){
    return sched_get_priority_min(policy);
}

void Thread::setMainSched(int policy){
    struct sched_param schedParam;
    schedParam.sched_priority = getMaxPrio(policy);
    pthread_setschedparam(pthread_self(), policy, &schedParam);
}

int Thread::getMainSched(int policy) {
    struct sched_param param;
    int current_policy;
    if (pthread_getschedparam(pthread_self(), &current_policy, &param) != 0) {
        return -1; 
    }
    return param.sched_priority;
}

