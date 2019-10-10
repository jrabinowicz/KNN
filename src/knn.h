#pragma once

#include "types.h"


class KNNClassifier {
public:
	KNNClassifier(unsigned int n_neighbors);

    void fit(SparseMatrix X, Matrix y);

    Vector predict(SparseMatrix X);

    unsigned int vecinos();
	MatrixXd dame_X();
	Matrix dame_y();
private:
	unsigned int _n_neighbors;
	SparseMatrix _X;
	Matrix _y;
	
	double predict_row(Vector row);
	Vector distance_to_row(Vector row);
};
