#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include <vector> 

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
	: _n_neighbors(n_neighbors) {
}

void KNNClassifier::fit(SparseMatrix X, Matrix y)
{
	_X = X;
	_y = y;
}

Vector KNNClassifier::distance_to_row(Vector row)
{	
	//Convierto a dense matrix porque sparse no tiene rowwise y entre norm y for termina siendo peor
	Matrix temp = MatrixXd(_X);
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
		if(_y(j,1) == POS)
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

