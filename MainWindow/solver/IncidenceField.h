#ifndef INCIDENCE_FIELD_H
#define INCIDENCE_FIELD_H
#include "./Pulse/Pulse.h"
#include "./Pulse/ZeroPulse.h"
#include "./Pulse/SinePulse.h"
#include "./Pulse/GaussianPulse.h"

class IncidenceField{
public:
    IncidenceField(int s, double cr, int beginIndx);
    void update();
    void rezeroClock();
    void setPulse(Pulse *p){ pulse = p;};
    double getEz(int i) const { return ez[i]; };
    double getHx(int i) const { return hx[i]; };
    //debug
    void dump();
private:
    long int step;
    int nSize;
    int pulseBeginIndx;

    double CrNum;

    double *ez;
    double *hx;

    Pulse* pulse;
};
#endif
