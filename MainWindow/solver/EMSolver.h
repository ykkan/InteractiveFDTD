#ifndef EM_SOLVER_H
#define EM_SOLVER_H
#include "DrudeMedia.h"
#include "./Pulse/Pulse.h"
#include "IncidenceField.h"

class EMSolver{
public:
    EMSolver(int n, double delT);
    void update();
    void dump();
    int getSize(){return nSize;};
    double** getEz(){return ez;};
    void getTSBound(int& iMin, int& iMax, int& jMin, int& jMax);
    void setBulkMedia(int iMin, int iMax, \
                  int jMin, int jMax, DrudeMedia* media);
    void clearMedia();

    void setPlaneWaveZero();
    void setPlaneWaveGaussian(double sigma);
    void setPlaneWaveSine(double lambda);

    void clearAllField();
private:
    void initField();
    void initMedia();
    void initPML();
    void buildTSBoundary();

    const int nSize;
    const double dt;
    const double CrNum;
    int step;

    double **dz;
    double **ez;
    double **ezSum;
    double **hx;
    double **hxSum;
    double **hy;
    double **hySum;

    DrudeMedia ***media; 

    int nPML;
    double *gi2;
    double *gi3;
    double *fi1;
    double *fi2;
    double *fi3;
    double *gj2;
    double *gj3;
    double *fj1;
    double *fj2;
    double *fj3;

    Pulse *incPulse;

    IncidenceField *incField;
    int iIncBegin;
    int iIncEnd;
    int jIncBegin;
    int jIncEnd;
};
#endif
