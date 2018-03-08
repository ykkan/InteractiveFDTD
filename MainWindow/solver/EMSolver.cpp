#include "EMSolver.h"
#include <iostream>
#include <cmath>
void make2dArray(int nx, int ny, double** &array){
    array = new double*[nx];
    for(int i=0; i<nx; ++i){
        array[i] = new double[ny]();
    }
}


EMSolver::EMSolver(int n, double delT):
    nSize(n), dt(delT),\
    CrNum(0.7), nPML(10)
{   
    step = 0;

    initField();
    initMedia();
    initPML();
    buildTSBoundary();
}

void EMSolver::initField(){
    make2dArray(nSize, nSize, dz);
    make2dArray(nSize, nSize, ez);
    make2dArray(nSize, nSize, ezSum);
    make2dArray(nSize, nSize, hx);
    make2dArray(nSize, nSize, hxSum);
    make2dArray(nSize, nSize, hy);
    make2dArray(nSize, nSize, hySum);
}

void EMSolver::initMedia(){
    //construct media
    media = new DrudeMedia**[nSize];
    for(int i=0; i<nSize; ++i){
        media[i] = new DrudeMedia*[nSize];
    }

    //initialize media
    for(int i=0; i<nSize; ++i){
        for(int j=0; j<nSize; ++j){
            media[i][j] = new DrudeMedia(1.0, 0.0);
        }
    }
}

void EMSolver::initPML(){
    gi2 = new double[nSize]();
    gi3 = new double[nSize]();
    fi1 = new double[nSize]();
    fi2 = new double[nSize]();
    fi3 = new double[nSize]();

    gj2 = new double[nSize]();
    gj3 = new double[nSize]();
    fj1 = new double[nSize]();
    fj2 = new double[nSize]();
    fj3 = new double[nSize]();

    for(int i=0; i<nSize; ++i){
        gi2[i] = 1.0;
        gi3[i] = 1.0;
        fi1[i] = 0.0;
        fi2[i] = 1.0;
        fi3[i] = 1.0;

        gj2[i] = 1.0;
        gj3[i] = 1.0;
        fj1[i] = 0.0;
        fj2[i] = 1.0;
        fj3[i] = 1.0; 
    }

    double sigmaMax = 0.33;
    for(int i=0; i<= nPML; ++i){
        double deepG = nPML - i;
        double xnG = sigmaMax*pow(deepG/nPML, 3.0);
        gi2[i] = 1.0/(1.0+xnG);
        gi2[nSize-i] = 1.0/(1.0+xnG);
        gi3[i] = (1.0-xnG)/(1.0+xnG);
        gi3[nSize-i] = (1.0-xnG)/(1.0+xnG);

        double deepF = nPML - i;
        double xnF = sigmaMax*pow(deepF/nPML, 3.0);
        fi1[i] = xnF;
        fi1[nSize-i] = xnF;
        fi2[i] = 1.0/(1.0+xnF);
        fi2[nSize-i] = 1.0/(1.0+xnF);
        fi3[i] = (1.0-xnF)/(1.0+xnF);
        fi3[nSize-i] = (1.0-xnF)/(1.0+xnF);
    }
    for(int j=0; j<= nPML; ++j){
        double deepG = nPML - j;
        double xnG = sigmaMax*pow(deepG/nPML, 3.0);
        gj2[j] = 1.0/(1.0+xnG);
        gj2[nSize-j] = 1.0/(1.0+xnG);
        gj3[j] = (1.0-xnG)/(1.0+xnG);
        gj3[nSize-j] = (1.0-xnG)/(1.0+xnG);

        double deepF = nPML - j;
        double xnF = sigmaMax*pow(deepF/nPML, 3.0);
        fj1[j] = xnF;
        fj1[nSize-j] = xnF;
        fj2[j] = 1.0/(1.0+xnF);
        fj2[nSize-j] = 1.0/(1.0+xnF);
        fj3[j] = (1.0-xnF)/(1.0+xnF);
        fj3[nSize-j] = (1.0-xnF)/(1.0+xnF);
    }
}

void EMSolver::buildTSBoundary(){
    iIncBegin = int(1*nSize/5);
    iIncEnd = nSize - iIncBegin -1;
    jIncBegin = int(1*nSize/5);
    jIncEnd = nSize - jIncBegin -1;
    incField = new IncidenceField(nSize, CrNum, iIncBegin-3);
}

void EMSolver::getTSBound(int& iMin, int& iMax, int& jMin, int& jMax){
    iMin = iIncBegin;
    iMax = iIncEnd;
    jMin = jIncBegin;
    jMax = jIncEnd;
}

void EMSolver::setBulkMedia(int iMin, int iMax, \
                  int jMin, int jMax, DrudeMedia* media){
    for(int i=iMin; i<iMax; ++i){
        for(int j=jMin; j<jMax; ++j){
           this->media[i][j] = media; 
        }
    }
}

void EMSolver::clearMedia(){
    for(int i=0; i<nSize; ++i){
        for(int j=0; j<nSize; ++j){
            media[i][j] = new DrudeMedia(1.0, 0.0);
        }
    }
}

void EMSolver::update(){
    incField->update();

    for(int i=1; i<nSize; ++i){
       for(int j=1; j<nSize; ++j){
            dz[i][j] = gi3[i]*gj3[j]*dz[i][j] \
                +gi2[i]*gj2[j]*CrNum*( hy[i][j] - hy[i-1][j] \
                - hx[i][j] + hx[i][j-1] );
            double epsr= media[i][j]->epsr;
            double sigma= media[i][j]->sigma;
            ez[i][j]  = 1.0/(epsr + sigma*dt)*( dz[i][j] - ezSum[i][j] );
            ezSum[i][j] += sigma*dt*ez[i][j];
        }
    }
    for(int j=jIncBegin; j<=jIncEnd; ++j){
        dz[iIncBegin][j] += CrNum*incField->getHx(iIncBegin-1);
        dz[iIncEnd][j] -= CrNum*incField->getHx(iIncEnd+1);
    }

    //ez[50][50] = exp( -0.5*pow((20.0-step)/5.0,2.0) );
    //step++;
    
    for(int i=0; i<nSize; ++i){
        ez[0][i] = 0;
        ez[nSize-1][i] = 0;
        ez[i][0] = 0;
        ez[i][nSize-1] = 0;
    } 
    
    
    for(int i=0; i< nSize-1; ++i){
        for(int j=0; j< nSize-1; ++j){
            double curlEzY = -( ez[i][j+1] - ez[i][j] );
            hxSum[i][j] = hxSum[i][j] + fi1[i]*curlEzY;
            hx[i][j] = fj3[j]*hx[i][j] \
                + fj2[j]*CrNum*(curlEzY + hxSum[i][j]);

            double curlEzX = ez[i+1][j] - ez[i][j];
            hySum[i][j] = hySum[i][j] + fj1[j]*curlEzX;
            hy[i][j] = fi3[i]*hy[i][j] \
                + fi2[i]*CrNum*(curlEzX + hySum[i][j]);
        }
    }
    for(int i=iIncBegin; i<=iIncEnd; ++i){
        hx[i][jIncBegin-1] += CrNum*incField->getEz(i);
        hx[i][jIncEnd+1] -= CrNum*incField->getEz(i);
    }
    for(int j=jIncBegin; j<=jIncEnd; ++j){
        hy[iIncBegin-1][j] -= CrNum*incField->getEz(iIncBegin-1);
        hy[iIncEnd+1][j] += CrNum*incField->getEz(iIncEnd+1);
    }
}



void EMSolver::setPlaneWaveZero(){
    incField->setPulse( new ZeroPulse() );
    incField->rezeroClock();
}
void EMSolver::setPlaneWaveGaussian(double sigma){
    incField->setPulse( new GaussianPulse(sigma) ); 
    incField->rezeroClock();
}
void EMSolver::setPlaneWaveSine(double period){
    incField->setPulse( new SinePulse(period) );
    incField->rezeroClock();
}

void EMSolver::clearAllField(){
    initField();
}
