#pragma once
#include "Particle.h"

class Quad {
public:
    double x, y, w, h;
    Quad(double x_, double y_, double w_, double h_);
    bool contains(Particle* p);
};
