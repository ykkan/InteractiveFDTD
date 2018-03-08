# Interactive FDTD
## Introduction
This is a dynamic, interactive GUI programm for simulating 2D electromagnetic scattering problem. The core algorithm
implemented in this programm is finite difference time domain method (FDTD), which discretize Maxwell's equation in both
spatial and time domain. This program was developed with c++ and Qt. The QCustoplot library is also used.

Watch this video for 

## Class Diagram
![Class Diagram](/images/classDiagram.png)

## Description for each components
### MainWindow:
Contorller of the the programm.

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
