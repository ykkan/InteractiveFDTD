######################################################################
# Automatically generated by qmake (3.1) Thu Mar 8 09:55:52 2018
######################################################################

TEMPLATE = app
TARGET = InteractiveFDTD
INCLUDEPATH += .

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += MainWindow.h \
           Canvas/Canvas.h \
           qcustomplot/qcustomplot.h \
           SettingPanel/MediaSettingPanel.h \
           SettingPanel/PlaneWaveSettingPanel.h \
           solver/DrudeMedia.h \
           solver/EMSolver.h \
           solver/IncidenceField.h \
           solver/Pulse/GaussianPulse.h \
           solver/Pulse/Pulse.h \
           solver/Pulse/SinePulse.h \
           solver/Pulse/ZeroPulse.h
SOURCES += main.cpp \
           MainWindow.cpp \
           Canvas/Canvas.cpp \
           qcustomplot/qcustomplot.cpp \
           SettingPanel/MediaSettingPanel.cpp \
           SettingPanel/PlaneWaveSettingPanel.cpp \
           solver/EMSolver.cpp \
           solver/IncidenceField.cpp
