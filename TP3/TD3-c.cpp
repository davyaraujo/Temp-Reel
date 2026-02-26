#include "thread.h"
#include "Mutex.h"
#include <vector>
#include <iostream>

class CounterThread : public Thread {
private:
    int& sharedCounter;
    int nIterations;
    Mutex& mutex;

public:
    CounterThread(int id, int& counter, int iterations, Mutex& m) 
        : Thread(id), sharedCounter(counter), nIterations(iterations), mutex(m) {}

protected:
    void run() override {
        for (int i = 0; i < nIterations; ++i) {
            Mutex::Lock lock(mutex); 
            sharedCounter++;
        }
    }
};

int main() {
    int counter = 0;
    int nThreads = 4;
    int iterations = 100000;
    Mutex mutex;
    std::vector<CounterThread*> threads;

    for (int i = 0; i < nThreads; ++i) {
        threads.push_back(new CounterThread(i, counter, iterations, mutex));
        threads[i]->start(); 
    }

    // Remplacement de pthread_join
    for (int i = 0; i < nThreads; ++i) {
        threads[i]->join();
    }

    std::cout << "Valeur finale du compteur : " << counter << std::endl;
    std::cout << "Attendu : " << nThreads * iterations << std::endl;

    // Nettoyage
    for (auto t : threads) delete t;

    return 0;
}