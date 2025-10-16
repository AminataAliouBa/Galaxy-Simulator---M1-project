#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Particle.h"
#include "Quad.h"
#include "QuadTree.h"

namespace py = pybind11;

PYBIND11_MODULE(cppcore, m) {
    py::class_<Vec2>(m, "Vec2")
        .def(py::init<double,double>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y);

    py::class_<Particle>(m, "Particle")
        .def(py::init<double,double,double,double,double>())
        .def_readwrite("mass", &Particle::mass)
        .def_readwrite("position", &Particle::position)
        .def_readwrite("velocity", &Particle::velocity)
        .def_readwrite("net_force", &Particle::net_force)
        .def("reset_force", &Particle::reset_force)
        .def("update_position", &Particle::update_position);

    py::class_<Quad>(m, "Quad")
        .def(py::init<double,double,double,double>())
        .def("contains", &Quad::contains);

    py::class_<Quadtree>(m, "Quadtree")
        .def(py::init<Quad>())
        .def("insert", &Quadtree::insert)
        .def("compute_force", &Quadtree::compute_force);
}
