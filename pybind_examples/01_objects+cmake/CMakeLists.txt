cmake_minimum_required(VERSION 2.8.12)
project(petlib)

add_subdirectory(pybind11)
pybind11_add_module(petlib pet.cpp petlib.cpp)
