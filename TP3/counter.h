#ifndef COUNTER_H
#define COUNTER_H
#include "Mutex.h"
#include <memory>
#include <functional>

class Counter{
    private:
        double m_value;
        std::unique_ptr<Mutex> p_mutex;
        std::function<double()> incrementFunc;
    public:
        Counter(bool protect){
            m_value = 0.0;
            if (protect) {
                p_mutex = std::make_unique<Mutex>();
                incrementFunc = [this] () {
                    Mutex::Lock lock(*p_mutex);
                    return ++m_value;
                };
            }
            else {
                p_mutex = nullptr;
                incrementFunc = [this] () {
                    return ++m_value;
                };
            }
        }
        double increment(){
            return incrementFunc();
        }
        double value(){
            return m_value;
        }
        bool isProtected() const {
            return p_mutex != nullptr;
        }
} ;

#endif