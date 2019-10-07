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
	temp.rowwise() -= row.transpose();

	Vector res = res.rowwise().norm();
	return res;
}

#define POS 'pos'
#define NEG 'neg'

double KNNClassifier::predict_row(Vector row)
{
	Vector dist = this->distance_to_row(row);
	vector<pair<double, int> > argsort;
	for (int i = 0; i < dist.size(); ++i)
	{
	 	argsort[i].first = dist(i);
	 	argsort[i].second = i;
	}
	sort(argsort.begin(), argsort.end());
	cout << "anda argsort" << endl;

	cout << "[ ";
	for (int i = 0; i < argsort.size(); ++i)
	{
		cout << "(" << argsort[i].first << "," << argsort[i].second << "), "; 
	}
	cout << "]";

	//Matrix kvecinos;
	int pos = 0;
	int neg = 0;
	for (unsigned int i = 0; i < _n_neighbors; ++i)
	{
		int j = argsort[i].second;
		//kvecinos.row(i) = _y(j,1);
		//VERIFICAR QUE LOS VALORES DE _y SEAN 0(NEG) Y 1(POS)
		cout << _y(j,1) << endl; 
		if(_y(j,1) == POS)
			pos++;
		else
			neg++;
	}

	double res = POS;
	if(neg>pos)
		res = NEG;
	return res;
}

Vector KNNClassifier::predict(SparseMatrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());
    cout << "anda esto" << endl;

    for (unsigned k = 0; k < X.rows(); ++k)
    {
        ret(k) = this->predict_row(X.row(k));
		cout << "anda la iter " << k << endl;        
    }

    return ret;
}

