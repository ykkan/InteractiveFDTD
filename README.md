# Interactive FDTD
## Introduction
This is a dynamic, interactive GUI programm for simulating 2D electromagnetic scattering problem. The core algorithm is
finite difference time domain method (FDTD), which is based on the discretization of Maxwell's equation on spatial grid.
This program was developed with c++ and Qt. The qcustomplot library is also used to draw heatmap plot.

Watch this video to get some ideas of this program:
[2D Scattering Phenomenon](https://www.youtube.com/watch?v=wrgAEh-n87I&feature=youtu.be)

## Class Diagram
![Class Diagram](/images/classDiagram.png)

## Description for main components
### MainWindow:
Contorller of the the program.

### Canvas:
A interactive canvas generating heatmap plot of Ez field. The user can draw  arbitrary shape of media inside specific region of this Canvas.

### MediaSettingPanel:
Panel for Setting Media. 

### PlaneWaveSettingPanel:
Panel for setting different types of plane wave.

### EMSolver:
Solver implementing the algorithm of 2D FDTD. We adapt Sullivan's FDTD formalism.

### IncidenceField
Simulating 1D plane wave. This plane wave will be used by EMSolver as incidence source.

## Installation
### Linux:
Move to the directory MainWindow and type:
qmake and make

