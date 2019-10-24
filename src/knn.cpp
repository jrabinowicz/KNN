#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"
#include <vector> 

using namespace std;

// Entrenamos KNN con el mayor k que vamos a usar
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
	Eigen::SparseMatrix<double,Eigen::ColMajor> temp(X.rows(), _n_neighbors);
	_vote_mat = temp;
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

void KNNClassifier::predict_row(Vector row, unsigned k)
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
	//int pos = 0;
	//int neg = 0;
	for (unsigned int i = 0; i < _n_neighbors; ++i)
	{
		int j = argsort[i].second;
		_vote_mat.insert(k, i) = _y.transpose()(j,0);
		/* viejo
		if((_y.transpose())(j,0) == POS)
			pos++;
		else
			neg++;
		*/
	}
	/* viejo
	int res = POS;
	if(neg>pos)
		res = NEG;
	return (double) res;
	*/
}

Vector KNNClassifier::predict(SparseMatrix X)
{
    // Creamos vector columna a devolver
    auto res = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); ++k)
    {
    	cout << "predigo " << k << endl;
        // ret(k) = this->predict_row(X.row(k));       
    }
    // Tengo vote_mat completa, tengo que hacer suma rowwise para obtener las predicciones de cada linea con k vecinos
    // o quitarle columnas a vote_mat para sacar vecinos y ahi hacer la suma rowwise (eso hace predictNewK)
    // suma rowwise con sparse_Matrix = sparse_mat * VectorXd::Ones(sparse_mat.cols())
    // (sacado de aca: https://forum.kde.org/viewtopic.php?f=74&t=122971)
    res = _vote_mat * Eigen::VectorXd::Ones(_vote_mat.cols());
    return res;
}

// Precondición: knuevo es menor al k con el que se entrenó el clasificador por última vez.
// Predice los resultados para una nueva cantidad de vecinos (menor)
Vector KNNClassifier::predictNewK(unsigned int knuevo){
	if(knuevo > _n_neighbors){
		cerr << "knuevo debe ser mayor que kviejo" << endl;
		// Si falla devuelve vector de ceros
		return -Eigen::VectorXd::Ones(_vote_mat.cols());
	}
	_vote_mat = _vote_mat.leftCols(knuevo-1);
	_n_neighbors = knuevo;
	Vector res = _vote_mat * Eigen::VectorXd::Ones(_vote_mat.cols());
	return res;
}

