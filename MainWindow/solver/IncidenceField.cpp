#include "IncidenceField.h"

#include <iostream>
#include <cmath>

IncidenceField::IncidenceField(int s, double cr, int beginIndx):
    nSize(s), CrNum(cr), pulseBeginIndx(beginIndx)
{
    step = 0;
    ez = new double[nSize]();
    hx = new double[nSize]();
    pulse = new ZeroPulse();
}

void IncidenceField::update(){
    ++step;
    
    double ezFront1 = ez[0];
    double ezFront2 = ez[1];
    double ezEnd1 = ez[nSize-1];
    double ezEnd2 = ez[nSize-2];

    for(int i=0; i<nSize; ++i){
        ez[i] = ez[i] - CrNum*(hx[i]-hx[i-1]);
    }

    ez[0] = ezFront2 + (CrNum-1)/(CrNum+1)*( ez[1] - ezFront1 );
    ez[nSize-1] = ezEnd2 + (CrNum-1)/(CrNum+1)*( ez[nSize-2] -ezEnd1 );

    ez[pulseBeginIndx] = pulse->get( double(step) );
    for(int i=0; i<nSize; ++i){
        hx[i] = hx[i] - CrNum*( ez[i+1]-ez[i] );
    }
}

void IncidenceField::rezeroClock(){
    step = 0;
}
