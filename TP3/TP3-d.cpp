#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "counter.h"
#include "incrementer.h"
#include "../TP1/Chrono.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " nLoops nTasks [protect] [policy]" << std::endl;
        return 1;
    }
    bool protect;
    int policy;
    int nLoops = std::stoi(argv[1]);
    int nTasks = std::stoi(argv[2]);
    if (argc > 3){
        protect = std::stoi(argv[3]) != 0;
    }
    else {
        protect = false;
    }
    if (argc > 4) {
        int policy_arg = std::stoi(argv[4]);
        if (policy_arg == 0) {
            policy = SCHED_OTHER;
        } else if (policy_arg == 1) {
            policy = SCHED_FIFO;
        } else if (policy_arg == 2) {
            policy = SCHED_RR;
        } else {
            std::cerr << "Invalid scheduling policy. Using default SCHED_OTHER." << std::endl;
            policy = SCHED_OTHER;
        }
    }

    Counter counter(protect);
    Chrono globalChrono;
    
    Thread::setMainSched(policy);

    std::vector<std::unique_ptr<Incrementer>> tasks;
    
    globalChrono.restart(); 
    for (int i = 0; i < nTasks; ++i) {
        tasks.push_back(std::make_unique<Incrementer>(i, nLoops, counter));
        tasks.back()->start(); 
    }

    for (auto& task : tasks) {
        task->join();
    }

    double totalDuration = globalChrono.lap_ms() / 1000.0;

    double finalValue = counter.value();
    double expectedValue = (double)nTasks * nLoops;
    double ratio = (finalValue / expectedValue) * 100.0;

    std::cout << "\n--- Resultats ---" << std::endl;
    std::cout << "Valeur finale : " << finalValue << std::endl;
    std::cout << "Valeur attendue : " << expectedValue << " (" << ratio << "%)" << std::endl;
    std::cout << "Temps d'execution total : " << totalDuration << " s" << std::endl;

    for (const auto& task : tasks) {
        std::cout << "Tache " << task->duration_ms() << " ms" << std::endl;
    }

    return 0;
}