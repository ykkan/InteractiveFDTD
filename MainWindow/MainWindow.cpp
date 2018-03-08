#include "MainWindow.h"

MainWindow::MainWindow(){
    this->setWindowTitle( tr("Interactive FDTD") );

    drudeMedia = new DrudeMedia(1.0, 0.0);
    solver = new EMSolver(400, 0.1);

    canvasTimer = new QTimer();
    canvasTimer->setInterval(50);
    canvasTimer->start();
    connect( canvasTimer, SIGNAL( timeout() ), this, SLOT(evolve()) );

  

    canvas = new Canvas(this, solver);
    setCentralWidget(canvas);

    mediaSettingPanel = new MediaSettingPanel(this);
    mediaSettingDockWidget = new QDockWidget(tr("Media Setting"), this);
    mediaSettingDockWidget->setWidget(mediaSettingPanel);
    this->addDockWidget(Qt::LeftDockWidgetArea, mediaSettingDockWidget);

    planeWaveSettingPanel = new PlaneWaveSettingPanel(this);
    planeWaveSettingDockWidget = \
        new QDockWidget(tr("Plane Wave Setting"), this);
    planeWaveSettingDockWidget->setWidget(planeWaveSettingPanel);
    this->addDockWidget(Qt::LeftDockWidgetArea, \
        planeWaveSettingDockWidget);
}

void MainWindow::evolve(){
    solver->update();
    canvas->update();
}

void MainWindow::clearMedia(){
    canvas->clearMedia();
    solver->clearMedia();
}

void MainWindow::setPlaneWaveNone(){
    solver->setPlaneWaveZero();
}
void MainWindow::setPlaneWaveSine(double period){
    solver->setPlaneWaveSine(period);
}
void MainWindow::setPlaneWaveGaussian(double period){
    solver->setPlaneWaveGaussian(period);
}

void MainWindow::setMediaColorMapVisible(){
    canvas->setMediaColorMapVisible();
}

void MainWindow::setMediaColorMapInVisible(){
    canvas->setMediaColorMapInVisible();
}
