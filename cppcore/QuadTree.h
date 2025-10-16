#pragma once
#include "Quad.h"
#include <memory>

class Quadtree {
public:
    Quad boundary;
    Particle* particle;
    bool subdivided;
    std::unique_ptr<Quadtree> NW, NE, SW, SE;

    Quadtree(Quad b);
    void insert(Particle* p);
    void subdivide();
    Vec2 compute_force(Particle* p, double theta, double G);
};
