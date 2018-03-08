#include "MediaSettingPanel.h"
#include "../MainWindow.h"

MediaSettingPanel::MediaSettingPanel(MainWindow* mainWindow){
    this->mainWindow = mainWindow;

    formLayout = new QFormLayout();
    vBoxLayout = new QVBoxLayout();

    drudeMediaEpsr = new QDoubleSpinBox();
    drudeMediaSigma = new QDoubleSpinBox();
    drudeMediaEpsr->setRange(1, 500);
    drudeMediaSigma->setRange(0, 500);
    drudeMediaEpsr->setValue(1.0);
    drudeMediaSigma->setValue(0.0);
    connect( drudeMediaEpsr, SIGNAL( valueChanged(double) ), \
        this, SLOT( changeDrudeEpsr() ) );
    connect( drudeMediaSigma, SIGNAL( valueChanged(double) ), \
        this, SLOT( changeDrudeSigma() ) );

    formLayout->addRow(tr("epsr"), drudeMediaEpsr);
    formLayout->addRow(tr("sigma"), drudeMediaSigma);
    
    clearMediaButton = new QPushButton("clear all media", this);
    connect( clearMediaButton, \
        SIGNAL(clicked()), this, SLOT(clickClearMediaButton()) );

    visibleButton = new QRadioButton( tr("Visible"), this);
    visibleButton->setChecked(true);
    connect( visibleButton, \
        SIGNAL(toggled(bool)), this, SLOT(visibleButtonAction()) );

    vBoxLayout->addWidget(visibleButton);
    vBoxLayout->addWidget(clearMediaButton);
    vBoxLayout->addLayout(formLayout);

    vBoxLayout->setSpacing(10);
    vBoxLayout->setMargin(20);
    this->setLayout(vBoxLayout);
}

void MediaSettingPanel::clickClearMediaButton(){
    mainWindow->clearMedia();
}
void MediaSettingPanel::changeDrudeEpsr(){
    mainWindow->setDrudeEpsr( drudeMediaEpsr->value() );
}
void MediaSettingPanel::changeDrudeSigma(){
        mainWindow->setDrudeSigma( drudeMediaSigma->value() );
}

void MediaSettingPanel::visibleButtonAction(){
    if(visibleButton->isChecked()){
        mainWindow->setMediaColorMapVisible();
    }
    else{
        mainWindow->setMediaColorMapInVisible();
    }
}
