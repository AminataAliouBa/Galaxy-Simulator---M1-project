#include "Particle.h"

Particle::Particle(double m, double px, double py, double vx, double vy)
    : mass(m), position(px, py), velocity(vx, vy), net_force(0,0) {}

void Particle::reset_force() {
    net_force = Vec2(0,0);
}

void Particle::update_position(double dt) {
    double ax = net_force.x / mass;
    double ay = net_force.y / mass;
    position.x += velocity.x * dt + 0.5 * ax * dt * dt;
    position.y += velocity.y * dt + 0.5 * ay * dt * dt;
    velocity.x += ax * dt;
    velocity.y += ay * dt;
}
