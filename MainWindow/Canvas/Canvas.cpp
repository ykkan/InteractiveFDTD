#include "Canvas.h"
#include "./qcustomplot/qcustomplot.h"
#include "MainWindow.h"

Canvas::Canvas(MainWindow* mainWindow, EMSolver* solver){
    emSolver = solver;

    drudeMedia = mainWindow->getDrudeMedia();
    
    nxCell = emSolver->getSize();
    nyCell = emSolver->getSize();

    this->resize(nxCell, nyCell);
    this->xAxis->setRange(0, nxCell);
    this->yAxis->setRange(0, nyCell);
    this->xAxis->setLabel( tr("x") );
    this->yAxis->setLabel( tr("y") );

    fieldData = emSolver->getEz();
    
    cursorSize = 5;
    this->setMediaRegionBound();
    this->initMediaColorMap();

    colorMap = new QCPColorMap(this->xAxis, this->yAxis);
    colorMap->data()->setRange(QCPRange(0,nxCell), QCPRange(0,nyCell));
    colorMap->data()->setSize(nxCell, nyCell);
     QCPColorScale* colorScale = new QCPColorScale(this);

    this->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorScale->axis()->setLabel(tr("Ez Field"));
    
    colorMap->setGradient(QCPColorGradient::gpSpectrum);
    QCPRange fieldDataRange = QCPRange(-1.5, 1.5);
    colorMap->setDataRange(fieldDataRange);
}

void Canvas::setMediaRegionBound(){
    int iTSMin;
    int iTSMax;
    int jTSMin;
    int jTSMax;
    emSolver->getTSBound(iTSMin, iTSMax, jTSMin, jTSMax);
    int factor = 10;
    iMediaMin = iTSMin + factor;
    iMediaMax = iTSMax - factor;
    jMediaMin = jTSMin + factor;
    jMediaMax = jTSMax - factor;
}

void Canvas::initMediaColorMap(){
    mediaColorMap = new QCPColorMap(this->xAxis, this->yAxis);
    mediaColorMap->data()->setRange(QCPRange(0, nxCell), QCPRange(0, nyCell));
    mediaColorMap->data()->setSize(nxCell, nyCell); 
    mediaColorMap->setDataRange(QCPRange(0,1));
    mediaColorMap->data()->fillAlpha(0);
    mediaColorMap->data()->fill(0);

    for(int i=iMediaMin; i<iMediaMax; ++i){
        for(int j=jMediaMin; j<jMediaMax; ++j){
            mediaColorMap->data()->setAlpha(i, j, 120);
        }
    }

    QCPColorGradient twoColorGradient(QCPColorGradient::gpGrayscale);
    twoColorGradient.setLevelCount(2);
    mediaColorMap->setGradient(twoColorGradient.inverted());
    mediaColorMap->setLayer("overlay");
}

bool Canvas::isInMediaRegion(int iMouse, int jMouse){
    return ( iMouse>iMediaMin && iMouse<iMediaMax && \
        jMouse>jMediaMin && jMouse<jMediaMax);
}

void Canvas::setMedia(int iMouse, int jMouse){
    int iCursorMin = std::max(iMouse - cursorSize, iMediaMin);
    int iCursorMax = std::min(iMouse + cursorSize, iMediaMax);
    int jCursorMin = std::max(jMouse - cursorSize, jMediaMin);
    int jCursorMax = std::min(jMouse + cursorSize, jMediaMax);
    for(int i=iCursorMin; i<iCursorMax; ++i){
        for(int j=jCursorMin; j<jCursorMax; ++j){
            mediaColorMap->data()->setCell(i, j, 1);
        }
    }
    emSolver->setBulkMedia(iCursorMin, iCursorMax, \
                jCursorMin, jCursorMax, drudeMedia);
}

void Canvas::clearMedia(){
    mediaColorMap->data()->fill(0);
}

void Canvas::mousePressEvent(QMouseEvent* event){
    if(event->buttons() == Qt::LeftButton){
        int iMouse = int( xAxis->pixelToCoord(event->x()) );
        int jMouse = int( yAxis->pixelToCoord(event->y()) );
        if( isInMediaRegion(iMouse, jMouse) ){
            setMedia(iMouse, jMouse);
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event){
    if(event->buttons() == Qt::LeftButton){
        int iMouse = int( xAxis->pixelToCoord(event->x()) );
        int jMouse = int( yAxis->pixelToCoord(event->y()) );
        if( isInMediaRegion(iMouse, jMouse) ){
            setMedia(iMouse, jMouse);
        }
    }
}

void Canvas::update(){
    for(int i=1; i<nxCell; ++i){
        for(int j=1; j<nyCell; ++j){
            colorMap->data()->setCell(i, j, fieldData[i][j]);
        }
    }
    this->replot();
}

void Canvas::setMediaColorMapVisible(){
    mediaColorMap->setVisible(true);
}
void Canvas::setMediaColorMapInVisible(){
    mediaColorMap->setVisible(false);
}
