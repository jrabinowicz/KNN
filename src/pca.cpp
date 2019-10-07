#include <iostream>
#include "pca.h"
#include "eigen.h"

using namespace std;


PCA::PCA(unsigned int n_components): alpha(n_components) {}

void PCA::fit(Matrix X){
	//fit recibe matrix X y devuelve la matriz de autovectores de la matriz de covarianza
	
	X.rowwise() -= X.colwise().mean();

	Matrix cov = X.transpose() * X;
	cov /= X.size()-1; 
	this->autovectores = get_first_eigenvalues(cov,this->alpha).second;
}

// void PCA::fit(Matrix X){
// 	//fit recibe matrix X y devuelve la matriz de autovectores de la matriz de covarianza

// 	X.rowwise() -= X.colwise().mean();
// 	Matrix cov;
// 	cov.noalias() = (X.transpose()).eval() * X;
// 	cov /= X.size()-1; 
// 	this->autovectores = get_first_eigenvalues(cov,cov.size()).second;
// }


MatrixXd PCA::transform(SparseMatrix X){
	MatrixXd aux = MatrixXd(X);
	Matrix cambioDeBase = this->autovectores;
	aux = aux * cambioDeBase;
	return aux;
}
