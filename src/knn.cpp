#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include <vector> 

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
	: _n_neighbors(n_neighbors) {
}

unsigned int KNNClassifier::vecinos(){
	return this->_n_neighbors;
}
MatrixXd KNNClassifier::dame_X(){
	return MatrixXd(this->_X);
}
Matrix KNNClassifier::dame_y(){
	return this->_y;
}

void KNNClassifier::fit(SparseMatrix X, Matrix y)
{
	_X = X;
	_y = y.transpose();
}

Vector KNNClassifier::distance_to_row(Vector row)
{	
	//Convierto a dense matrix porque sparse no tiene rowwise y entre norm y for termina siendo peor
	Matrix temp = MatrixXd(_X);
	// Vector res(_X.rows());
	// for (int i = 0; i < _X.rows(); ++i)
	// {
	// 	double norm = 0;
	// 	Vector rowsub = _X.row(i) - row.transpose();
	// 	norm = rowsub.norm();
	// 	res(i) = norm;
	// }
	temp.rowwise() -= (row.transpose()).eval();
	Vector res = temp.rowwise().norm();
	return res;
}

#define POS 1
#define NEG 0

double KNNClassifier::predict_row(Vector row)
{
	Vector dist = this->distance_to_row(row);
	vector<pair<double, int> > argsort;
	for (int i = 0; i < dist.size(); ++i)
	{
	 	pair<double,int> par;
	 	par.first = dist(i);
	 	par.second = i;
	 	argsort.push_back(par);
	}
	sort(argsort.begin(), argsort.end());
	int pos = 0;
	int neg = 0;
	for (unsigned int i = 0; i < _n_neighbors; ++i)
	{
		int j = argsort[i].second;
		if((_y.transpose())(j,0) == POS)
			pos++;
		else
			neg++;
	}

	int res = POS;
	if(neg>pos)
		res = NEG;
	return (double) res;
}

Vector KNNClassifier::predict(SparseMatrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); ++k)
    {
        ret(k) = this->predict_row(X.row(k));       
    }

    return ret;
}

