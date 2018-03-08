#ifndef PLANE_WAVE_SETTING_PANEL_H
#define PLANE_WAVE_SETTING_PANEL_H
#include <QRadioButton>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

class MainWindow;

class PlaneWaveSettingPanel : public QWidget{
    Q_OBJECT
public slots:
    void checkNoneButton();
    void checkSineButton();
    void checkGaussianButton();
public:
    PlaneWaveSettingPanel(MainWindow* mainWindow);
private:
    MainWindow* mainWindow;

    QRadioButton* noneButton; 

    QRadioButton* sineButton;
    QDoubleSpinBox* sineWavePeriod;

    QRadioButton* gaussianButton;
    QDoubleSpinBox* gaussianWaveSigma;

    QGroupBox* planeWaveBox;
    QVBoxLayout* mainLayout;
    QGridLayout* gridLayout;
};

#endif
