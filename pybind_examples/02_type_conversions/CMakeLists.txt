cmake_minimum_required(VERSION 2.8.12)
project(mylib)

add_subdirectory(pybind11)
pybind11_add_module(mylib mylib.cpp)
