#include "Quad.h"

Quad::Quad(double x_, double y_, double w_, double h_)
    : x(x_), y(y_), w(w_), h(h_) {}

bool Quad::contains(Particle* p) {
    return p->position.x >= x && p->position.x <= x + w &&
           p->position.y >= y && p->position.y <= y + h;
}
