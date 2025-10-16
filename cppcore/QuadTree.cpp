#include "QuadTree.h"
#include <cmath>

Quadtree::Quadtree(Quad b) : boundary(b), particle(nullptr), subdivided(false) {}

void Quadtree::insert(Particle* p) {
    if (!boundary.contains(p)) return;

    if (!particle && !subdivided) {
        particle = p;
        return;
    }

    if (!subdivided) subdivide();

    if (NW) NW->insert(p);
    if (NE) NE->insert(p);
    if (SW) SW->insert(p);
    if (SE) SE->insert(p);
}

void Quadtree::subdivide() {
    double w2 = boundary.w / 2;
    double h2 = boundary.h / 2;

    NW = std::make_unique<Quadtree>(Quad(boundary.x, boundary.y, w2, h2));
    NE = std::make_unique<Quadtree>(Quad(boundary.x + w2, boundary.y, w2, h2));
    SW = std::make_unique<Quadtree>(Quad(boundary.x, boundary.y + h2, w2, h2));
    SE = std::make_unique<Quadtree>(Quad(boundary.x + w2, boundary.y + h2, w2, h2));

    if (particle) {
        NW->insert(particle);
        NE->insert(particle);
        SW->insert(particle);
        SE->insert(particle);
        particle = nullptr;
    }
    subdivided = true;
}

Vec2 Quadtree::compute_force(Particle* p, double theta, double G) {
    if (!particle && !subdivided) return Vec2(0,0);

    double dx = (particle ? particle->position.x : (NW->boundary.x + NW->boundary.w/2)) - p->position.x;
    double dy = (particle ? particle->position.y : (NW->boundary.y + NW->boundary.h/2)) - p->position.y;
    double d = std::sqrt(dx*dx + dy*dy);
    if (d == 0) return Vec2(0,0);

    double f = (G * (particle ? particle->mass : 1.0) * p->mass) / (d*d);
    return Vec2(f*dx/d, f*dy/d);
}
