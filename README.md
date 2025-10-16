# Galaxy Simulator – Barnes–Hut Algorithm

This project is a real-time galaxy simulator based on the Barnes–Hut algorithm, designed to model gravitational interactions among thousands of particles efficiently.
The simulator combines a C++ physics engine for performance-critical calculations with a Python (Pygame) graphical interface for interactive visualization.

## Features
- Real-time simulation of gravitational systems.
- Efficient computation of forces using the Barnes–Hut approximation.
- Integration of C++ core and Python visualization via pybind11.
- Scalable Quadtree structure reducing complexity from O(N²) to O(N log N).
- Interactive and visual rendering using Pygame.

## Project Structure
GalaxySimulator/
│
├─ cppcore/
│   ├─ Particle.h
│   ├─ Particle.cpp
│   ├─ Quad.h
│   ├─ Quad.cpp
│   ├─ QuadTree.h
│   ├─ QuadTree.cpp
│   └─ pybind_module.cpp
│
├─ py/
│   └─ main.py
│
└─ CMakeLists.txt

## Installation
### Requirements
- C++17 or later
- Python 3.8+
- CMake
- pybind11
- Pygame
- NumPy

### Build Instructions
git clone 
cd galaxy-simulator
mkdir build && cd build
cmake ..
make
cd ../py
python3 main.py

## Technical Notes
The Barnes–Hut algorithm approximates distant particle clusters as single bodies, significantly reducing computation time.
The Quadtree data structure organizes space hierarchically, enabling efficient spatial queries.
The simulation integrates the equations of motion in discrete time steps for dynamic visualization.

## Future Improvements
GPU acceleration with CUDA or OpenCL.
3D simulation support.
Parameter tuning via a graphical control panel.
Improved visualization (zoom, color coding, trails...).
