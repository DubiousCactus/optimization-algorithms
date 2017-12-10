#ifndef PCA_H
#define PCA_H

#include <iostream>
#include <assert.h>
#include <vector>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"

using namespace Eigen;
using namespace std;

class PCA
{
public:

    /*
     * Computes the princcipal component of a given matrix. Computation steps:
     * Assert that the input matrix is square matrix.
     * Compute the mean image.
     * Subtract mean image from the data set to get mean centered data vector
     * Compute the covariance matrix from the mean centered data matrix
     * Calculate the eigenvalues and eigenvectors for the covariance matrix
     * Normalize the eigen vectors
     * Find out two eigenvectors with the largest eigenvalues
     * 
     * @input MatrixXd D the data samples matrix.
     * 
     * @returns MatrixXd The principal component matrix
     */
    static MatrixXd Compute(MatrixXd D)
    {
        // The matrix must be square matrix.
        assert(D.rows() == D.cols());
        int N = D.rows();

        // 1. Compute the mean image
        MatrixXd mean(1, N);
        mean.setZero();

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                mean(0, j) += D(i, j) / N;
            }
        }

        // 2. Subtract mean image from the data set to get mean centered data vector
        MatrixXd U = D;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                U(i, j) -= mean(0, j);
            }
        }

        // 3. Compute the covariance matrix from the mean centered data matrix
        MatrixXd covariance = (U.transpose() * U) / (double)(N);

        // cout << covariance << endl;

        // 4. Calculate the eigenvalues and eigenvectors for the covariance matrix
        EigenSolver<MatrixXd> solver(covariance);
        MatrixXd eigenVectors = solver.eigenvectors().real();
        VectorXd eigenValues = solver.eigenvalues().real();

        // 5. Normalize the eigen vectors
        eigenVectors.normalize();

        // cout << eigenVectors << endl;
        // cout << eigenValues << endl;

        // 6. Find out an eigenvector with the largest eigenvalue
        //    which distingushes the data
        sort(eigenValues.derived().data(), eigenValues.derived().data() + eigenValues.derived().size());
        short index = eigenValues.size() - 1;
        VectorXd featureVector = eigenVectors.row(index);

        //return featureVector;
		
		/* I need a matrix of the two last (sorted) eigen vectors instead */
		MatrixXd pca_matrix;
		pca_matrix << eigenVectors.row(eigenValues.size() - 1), eigenVectors.row(eigenValues.size() - 2);

		return pca_matrix;
    }
};

#endif // PCA_H
