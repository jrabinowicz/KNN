#include <iostream>
#include <pybind11/pybind11.h>

using namespace std;
namespace py=pybind11;

void print_lists(py::list mylist)
{
    for (auto item: mylist)
        cout << item << endl;
}
