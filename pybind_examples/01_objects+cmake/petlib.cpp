#include <pybind11/pybind11.h>
#include "pet.h"

namespace py=pybind11;

// el primer argumento es el nombre...
PYBIND11_MODULE(petlib, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);
}
