#ifndef MEDIA_SETTING_PANEL_H
#define MEDIA_SETTING_PANEL_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QPushButton>

class MainWindow;

class MediaSettingPanel : public QWidget{
    Q_OBJECT
public slots:
    void clickClearMediaButton();
    void changeDrudeEpsr();
    void changeDrudeSigma();

    void visibleButtonAction();
public:
    MediaSettingPanel(MainWindow* mainWindow);
private:
    MainWindow* mainWindow;
    QFormLayout* formLayout;
    QVBoxLayout* vBoxLayout;
    QDoubleSpinBox* drudeMediaEpsr;
    QDoubleSpinBox* drudeMediaSigma;

    QPushButton* clearMediaButton;

    QRadioButton* visibleButton;
};

#endif
