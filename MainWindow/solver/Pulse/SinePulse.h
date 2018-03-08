#ifndef SINE_PULSE_H
#define SINE_PULSE_H
#include "Pulse.h"
#include <cmath>

class SinePulse : public Pulse{
public:
    SinePulse(double T):period(T){};
    double get(double t) const{ 
        return sin(2*3.14159*t/period); 
    };
private:
    // unit is timestep
    double period;
};
#endif

