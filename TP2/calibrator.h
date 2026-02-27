#ifndef CALIBRATOR_H
#define CALIBRATOR_H
#include <vector>
#include <cfloat>
#include <iostream>
#include "timer.cpp"   
#include "looper.h"  


class  Calibrator  : public Timer {
    private:
        double a, b;               
        double samplingPeriod_ms;
        unsigned int nSamples;
        std::vector<double> samples;
        Looper looper;

    public:
        Calibrator(double samplingPeriod_ms, unsigned int nSamples) 
            : Timer(), samplingPeriod_ms(samplingPeriod_ms), nSamples(nSamples) 
        {   
            std::cout << "Start" << std::endl;

            this->start_ms(samplingPeriod_ms, true);
            looper.runLoop(DBL_MAX);
            a = (samples.back() - samples.front()) / (nSamples * samplingPeriod_ms);
            b = samples.front();

            std::cout << "Finish: " << samples.size() << std::endl;
        }

        void callback() override {
            if (samples.size() < nSamples) {
                samples.push_back(looper.getSample());
            } 
            else {
                this->stop();
                looper.stopLoop(); 
            }
        }

        double nLoops(double t_ms) const {
            return a * t_ms + b;
        }

        double getA() const { return a; }
        double getB() const { return b; }
    };

#endif