#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include "../qcustomplot/qcustomplot.h"
#include "../solver/EMSolver.h"
#include <QTimer>
#include <QDockWidget>
class MainWindow;
class Canvas: public QCustomPlot{
    Q_OBJECT
public:
    Canvas(MainWindow* mainWindow, EMSolver* solver);
    void update();
    void setFieldData(double** data);

    bool isInMediaRegion(int iMouse, int jMouse);
    void setMedia(int iMouse, int jMouse);
    void clearMedia();

    void setMediaColorMapVisible();
    void setMediaColorMapInVisible();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    void setMediaRegionBound();
    void initMediaColorMap();
    
    EMSolver* emSolver;

    int nxCell;
    int nyCell;
    double** fieldData;
    QCPColorMap* colorMap;
    QCPColorMap* mediaColorMap;

    DrudeMedia* drudeMedia;
    int cursorSize;
    int iMediaMin;
    int iMediaMax;
    int jMediaMin;
    int jMediaMax;
};

#endif
