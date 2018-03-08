#ifndef INTERATIVE_FDTD_H
#define INTERATIVE_FDTD_H

#include <QMainWindow>
#include <QWidget>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "./Canvas/Canvas.h"

#include "./solver/DrudeMedia.h"
#include "./solver/EMSolver.h"

#include "./SettingPanel/MediaSettingPanel.h"
#include "./SettingPanel/PlaneWaveSettingPanel.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public slots:
    void evolve();
public:
    MainWindow();

    void clearMedia();
    void setDrudeEpsr(double epsr){ drudeMedia->epsr = epsr;};
    void setDrudeSigma(double sigma){ drudeMedia->sigma = sigma;};
    DrudeMedia* getDrudeMedia(){ return drudeMedia; };
    void setMediaColorMapVisible();
    void setMediaColorMapInVisible();

    void setPlaneWaveNone();
    void setPlaneWaveSine(double period);
    void setPlaneWaveGaussian(double sigma);
private:
    Canvas* canvas;
    EMSolver* solver;
    
    QTimer* canvasTimer;

    DrudeMedia* drudeMedia;

    QDockWidget* mediaSettingDockWidget; 
    QDockWidget* planeWaveSettingDockWidget;
    MediaSettingPanel* mediaSettingPanel;
    PlaneWaveSettingPanel* planeWaveSettingPanel;
};

#endif
