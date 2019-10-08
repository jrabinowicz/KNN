//#include "lists.h"
#include <iostream>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::SparseMatrix;

using namespace std;

namespace py=pybind11;


MatrixXd add_one(MatrixXd mat)
{
    auto ret = mat + MatrixXd::Constant(mat.rows(), mat.cols(), 1.0);
    return ret;
}

MatrixXd multiply_by_scalar(const MatrixXd& mat, float scalar)
{
    return scalar * mat;
}

MatrixXd add_row(const MatrixXd& mat, const VectorXd& v) {
    return (mat.rowwise() + v.transpose());
}


// el primer argumento es el nombre...
PYBIND11_MODULE(mylib, m) {
    m.def(
        "add_one", &add_one,
        "Function that adds one to every element of the matrix"
    );

    m.def(
        "multiply_by_scalar", &multiply_by_scalar,
        "Function that adds one to every element of the matrix"
    );
    m.def(
        "add_row", &add_row,
        "Function that adds one to every element of the matrix"
    );

}
