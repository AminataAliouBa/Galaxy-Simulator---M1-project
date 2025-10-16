#pragma once
#include <pybind11/pybind11.h>

struct Vec2 {
    double x, y;
    Vec2(double x_=0, double y_=0) : x(x_), y(y_) {}
};

class Particle {
public:
    double mass;
    Vec2 position;
    Vec2 velocity;
    Vec2 net_force;

    Particle(double m, double px, double py, double vx, double vy);
    void reset_force();
    void update_position(double dt);
};
