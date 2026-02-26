#ifndef INCREMENTER_H
#define INCREMENTER_H
#include "counter.h"
#include  "thread.h"

class  Incrementer : public Thread {
    private:
        const double nLoops;
        Counter& r_counter;
    public:
        Incrementer(int id, double nLoops, Counter& counter) : Thread(id), nLoops(nLoops), r_counter(counter) {}
    protected:
        virtual void run() override {
            for (int i = 0; i < nLoops; ++i) {
                r_counter.increment();
            }
        }
};

#endif