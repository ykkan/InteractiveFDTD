#include <QApplication>
#include "./solver/EMSolver.h"
#include "MainWindow.h"
#include <iostream>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow* interFDTD = new MainWindow();
    interFDTD->show();
    return a.exec();
}
