#include <iostream> 
#include <time.h>
#include <signal.h>
#include "../TP2/timer.h"
#include <unistd.h>

class CountDown : public Timer {
    private:
        int count;
    public:
        CountDown(int c) : count(c) {}
        void callback() override {
            if (count > 0) {
                cout << "|Competeur: " << count << endl;
                count--;
            } else {
                cout << "Fin" << endl;
                stop();
            }
        }
};

int main() {
    CountDown cd(15);
    cd.start_ms(1000, true);

    while (true) {
        pause();
    }

    return 0;
}