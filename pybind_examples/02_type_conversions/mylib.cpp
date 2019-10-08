//#include "lists.h"
#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

namespace py=pybind11;


void print_list(py::list mylist)
{
    for (auto item: mylist)
    {
        py::print(item);
    }
}

void print_vector(const vector<int>& v)
{
    for (auto item: v)
    {
        cout << item << endl;
    }

}



// el primer argumento es el nombre...
PYBIND11_MODULE(mylib, m) {
    m.def(
        "print_list", &print_list,
        "Function that prints lists"
    );
    m.def(
        "print_vec", &print_vector,
        "Function that prints vector"
    );

}
