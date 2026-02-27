#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "counter.h"
#include "incrementer.h"
#include "../TP1/Chrono.h"
#include "Mutex.h"
#include "../TP2/cpuloop.h"
#include "../TP2/calibrator.h"
#include "thread.h"
#include "../TP2/looper.h"


class ThreadA : public Thread {
    private:
        CPULoop cpuLoop;
        Mutex& R;
    public:
        ThreadA(int id, const Calibrator& calib, Mutex& R): Thread(id), cpuLoop(calib), R(R){}
        void run() override {
            cpuLoop.runTime(1000);
            for (int i = 0; i < 10; i++) {
                {
                    Mutex::Lock lock(R);
                    std::cout << "Thread A: " << i << std::endl;
                    cpuLoop.runTime(1000);

                }
            }

        }
                
};

class ThreadB : public Thread {
    private:
        CPULoop cpuLoop;
        Mutex& R;
    public:
        ThreadB(int id,  const Calibrator& calib, Mutex& R): Thread(id), cpuLoop(calib), R(R){}
        void run() override {
            cpuLoop.runTime(1000);
            for (int i = 0; i < 10; i++) {
                {
                    Mutex::Lock lock(R);
                    std::cout << "Thread B: " << i << std::endl;
                    cpuLoop.runTime(1000);

                }
                cpuLoop.runTime(2000);
            }

        }
                
};

class ThreadC : public Thread {
    private:
        CPULoop cpuLoop;
        Mutex& R;
    public:
        ThreadC(int id, const Calibrator& calib, Mutex& R): Thread(id), cpuLoop(calib), R(R){}
        void run() override {
            cpuLoop.runTime(2000);
            for (int i = 0; i < 10; i++) {
                {
                    Mutex::Lock lock(R);
                    std::cout << "Thread C: " << i << std::endl;
                    cpuLoop.runTime(2000);
                }
                cpuLoop.runTime(1000);
            }
        }             
};





int main() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset); // Affinité sur le CPU 0
    if(sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
        std::cerr << "Erreur lors de la définition de l'affinité CPU" << std::endl;
        return 1;
    }
    std::cout<<"processus lié ao CPU 0"<<std::endl;
    Calibrator calib(10, 100);
    Mutex mutexA, mutexB, mutexC;
    ThreadA taskA(1, calib, mutexA);
    ThreadB taskB(2, calib, mutexB);
    ThreadC taskC(3, calib, mutexA);
    taskC.start(10);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    taskA.start(30);
    taskB.start(20);

    taskA.join();
    taskB.join();
    taskC.join();
    return 0;
}