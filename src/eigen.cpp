#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double eps)
{
    Vector b = Vector::Random(X.cols());
    double eigenvalue;
    /***********************
     * COMPLETAR CODIGO
     **********************/
    //puede que haya que hacer reshape de b
    unsigned i = 0;
    while (i < num_iter)
    {
    	Vector prod = X * b; 
    	prod /= prod.norm();
    	b = prod;
    	i++;
    }

    eigenvalue = b.transpose() * X * b; 
    eigenvalue /= b.norm();

    return make_pair(eigenvalue, b / b.norm());
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon)
{
    Matrix A(X);
    Vector eigvalues(num);
    Matrix eigvectors(A.rows(), num);

    /***********************
     * COMPLETAR CODIGO
     **********************/
    unsigned i = 0;
    while (i < num)
    {
    	pair<double, Vector> powerIt = power_iteration(A, num_iter, epsilon);
    	eigvalues(i) = powerIt.first;
    	//puede que haya que hacer reshape de powerIt.second
    	eigvectors(Eigen::all,i) = (powerIt.second).transpose();
    	A -= powerIt.first * (powerIt.second * powerIt.second.transpose());
    	i++;
    }

    return make_pair(eigvalues, eigvectors);
}

