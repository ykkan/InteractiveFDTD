#include "PlaneWaveSettingPanel.h"
#include "../MainWindow.h"
PlaneWaveSettingPanel::PlaneWaveSettingPanel(MainWindow* mainWindow){
    this->mainWindow = mainWindow;

    noneButton = new QRadioButton(tr("None"), this);
    noneButton->setChecked(true);
    connect(noneButton, SIGNAL( clicked() ), \
        this, SLOT( checkNoneButton() ) );

    sineButton = new QRadioButton(tr("Sine"), this);
    connect(sineButton, SIGNAL( clicked() ), \
        this, SLOT( checkSineButton() ) );
    sineWavePeriod = new QDoubleSpinBox();
    sineWavePeriod->setRange(10, 200);
    sineWavePeriod->setValue(50);
    sineWavePeriod->setSuffix( tr(" dt") );

    gaussianButton = new QRadioButton(tr("Gaussian"), this);
    connect(gaussianButton, SIGNAL( clicked() ), \
        this, SLOT( checkGaussianButton() ) );
    gaussianWaveSigma = new QDoubleSpinBox();
    gaussianWaveSigma->setRange(10, 200);
    gaussianWaveSigma->setValue(10);
    gaussianWaveSigma->setSuffix( tr(" dt") );

    gridLayout = new QGridLayout();
    gridLayout->addWidget(noneButton, 0, 0, 1, 1);

    gridLayout->addWidget(sineButton, 1, 0, 1, 1);
    gridLayout->addWidget(new QLabel(tr("Period: ")), 1, 1, 1, 1);
    gridLayout->addWidget(sineWavePeriod, 1, 2, 1, 1);

    gridLayout->addWidget(gaussianButton, 2, 0, 1, 1);
    gridLayout->addWidget(new QLabel(tr("Duration(S.D.): ")), 2, 1, 1, 1);
    gridLayout->addWidget(gaussianWaveSigma, 2, 2, 1, 1);

    planeWaveBox = new QGroupBox();
    planeWaveBox->setLayout(gridLayout);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(planeWaveBox);
    this->setLayout(mainLayout);
}
void PlaneWaveSettingPanel::checkNoneButton(){
    mainWindow->setPlaneWaveNone();
}
void PlaneWaveSettingPanel::checkSineButton(){
    double period = sineWavePeriod->value();
    mainWindow->setPlaneWaveSine(period);
}
void PlaneWaveSettingPanel::checkGaussianButton(){
    double sigma = gaussianWaveSigma->value();
    mainWindow->setPlaneWaveGaussian(sigma);
}
