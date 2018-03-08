#ifndef GAUSSIAN_PULSE_H
#define GAUSSIAN_PULSE_H
#include "Pulse.h"
#include <cmath>

class GaussianPulse : public Pulse{
public:
    GaussianPulse(double s):sigma(s), shiftFactor(4.0){};
    double get(double t) const{ 
        return exp( -0.5*pow( (shiftFactor*sigma-t)/sigma, 2.0) ); 
    };
private:
    // unit is timestep
    double sigma;
    double shiftFactor;
};
#endif

