#include "../TP3/thread.h"
#include "../TP3/semaphore.h"
#include <atomic>
#include <iostream>
#include <vector>

using namespace std;

class TokenProducer : public Thread {
private:
    Semaphore& semaphore;
    unsigned long tokensToCreate;
    std::atomic<unsigned long> tokensProduced{0};
    int producerId;

public:
    TokenProducer(int id_thread,Semaphore& sem, unsigned long tokens, int id_producer) : Thread(id_thread), semaphore(sem), tokensToCreate(tokens), producerId(id_producer) {} 
    virtual ~TokenProducer() = default;
    
    void run() override
    {
        for (unsigned long i = 0; i < tokensToCreate; ++i) {
            semaphore.give();
            tokensProduced++;
        }
    }
    unsigned long getTokensProduced() const{
        return tokensProduced.load();
    }
    int getId() const{
        return producerId;
    }
};

class TokenConsumer : public Thread {
private:
    Semaphore& semaphore;
    std::atomic<unsigned long> tokensConsumed{0};
    int consumerId;
    static const double TIMEOUT_MS;
public:
    TokenConsumer(int id_thread, Semaphore& sem, int id_consumer) : Thread(id_thread), semaphore(sem), consumerId(id_consumer) {}
    virtual ~TokenConsumer() = default;
    
    void run() override
    {
        while (true) {
            if (semaphore.take(TIMEOUT_MS)) {
                tokensConsumed++;
            } else {
                break; 
            }
        }
    }
    unsigned long getTokensConsumed() const{
        return tokensConsumed.load();
    }
    int getId() const{
        return consumerId;
    }
};

const double TokenConsumer::TIMEOUT_MS = 1000.0;
int main(int argc, char* argv[]){
    if (argc != 4) {
        cerr << "Usage: " << argv[0]
            << " <num_consumers> <num_producers> <tokens_per_producer>" << endl;        
        return 1;
    }
    int NumConsumers = stoi(argv[1]);
    int NumProducers = stoi(argv[2]);
    int InitialTokensperProducer = stoi(argv[3]);

    try
    {
        if (NumConsumers <= 0 || NumProducers <= 0 || InitialTokensperProducer < 0) {
                cerr << "All arguments must be positive integers." << endl;
                return 1;
            }

        unsigned long totalTokens = NumProducers * InitialTokensperProducer;
        Semaphore semaphore(0, totalTokens);
        
        std::cout << "Starting " << std::endl;
        std::cout << "Producers: " << NumProducers << std::endl;
        std::cout << "Consumers: " << NumConsumers << std::endl;
        std::cout << "Initial Tokens per Producer: " << InitialTokensperProducer << std::endl;
        std::cout << "Total Tokens to Produce: " << totalTokens << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        Semaphore producerDone(0, totalTokens);
        vector<TokenProducer*> producers;
        vector<TokenConsumer*> consumers;

        for (int i = 0; i < NumProducers; ++i) {
            producers.push_back(new TokenProducer(i, semaphore, InitialTokensperProducer, i + 1));   
        }
        for (int i = 0; i < NumConsumers; ++i) {
            consumers.push_back(new TokenConsumer(i, semaphore, i + 1));   
        }

        std::cout << "Starting producers..." << std::endl;
        for (auto& producer : producers) {
            producer->start();
        }
        std::cout << "Starting consumers..." << std::endl;
        for (auto& consumer : consumers) {
            consumer->start(); 
        }
        std::cout << "Waiting for producers to finish..." << std::endl;
        for (auto& producer : producers) {
            producer->join();
            producerDone.give();
            std::cout << "Producer " << producer->getId() << " produced " << producer->getTokensProduced() << " tokens." << std::endl;
        }
        std::cout << "All producers finished. Waiting for consumers to finish..." << std::endl;
        for (auto& consumer : consumers) {
            consumer->join();
            std::cout << "Consumer " << consumer->getId() << " consumed " << consumer->getTokensConsumed() << " tokens." << std::endl;
        }

        unsigned long totalProduced = 0;
        std::cout << "Summary for Producer:" << std::endl;
        for (auto& producer : producers) {
            totalProduced += producer->getTokensProduced();
            std::cout << "Producer " << producer->getId() << ": " << producer->getTokensProduced() << " tokens produced." << std::endl;
        }
        unsigned long totalConsumed = 0;
        std::cout << "Summary for Consumer:" << std::endl;
        for (auto& consumer : consumers) {
            totalConsumed += consumer->getTokensConsumed();
            std::cout << "Consumer " << consumer->getId() << ": " << consumer->getTokensConsumed() << " tokens consumed." << std::endl;
        }
        std::cout << "Total Tokens Produced: " << totalProduced << std::endl;
        std::cout << "Total Tokens Consumed: " << totalConsumed << std::endl;
        std::cout << "Full Total: " << totalTokens << std::endl;

        if (totalProduced == totalConsumed) {
            std::cout << "Success: Total produced tokens match total consumed tokens." << std::endl;
        } else {
            std::cout << "Error: Total produced tokens do not match total consumed tokens." << std::endl;
        }

        if (totalProduced != totalTokens) {
            std::cout << "Error: Total produced tokens do not match expected total tokens." << std::endl;
        } else {
            std::cout << "Success: Total produced tokens match expected total tokens." << std::endl;
        }

        for (auto& producer : producers) {
            delete producer;
        }
        for (auto& consumer : consumers) {
            delete consumer;
        }
        return 0;
    }
    catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}
   