#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <iomanip>
#include "/home/davy/Ensta/TempReel/TP1/Chrono.h"
using namespace std;

class Looper {
    private:
        bool doStop;
        double iLoop;
    public:
        Looper(){

        }
        double runLoop(double nLoops = __DBL_MAX__ ){
            iLoop = 0;
            doStop = false;
            while (iLoop < nLoops && doStop == false){
                iLoop++;
            }
            return iLoop;
        }
        double getSample(){
            return iLoop;
        }
        double stopLoop(){
            doStop = true;
            return doStop;
        }
};

    // int main(int argc, char* argv[]){
    //     if (argc < 2) {
    //             std::cerr << "Usage: " << argv[0] << " <nLoops>" << std::endl;
    //             return 1;
    //         }
    //     double nLoops = atof(argv[1]);

    //     Chrono ch;
    //     Looper lp;
    //     ch.restart();
    //     double iLoop = lp.runLoop(nLoops);
    //     timespec time = ch.stop();

    //     cout << "LOOPS : " << nLoops << endl;


    //     cout << "SEG: " << time.tv_sec << endl;
    //     cout << "Nano: " << time.tv_nsec << endl;



        
    //     return 0;
    // }
