/*
 * Algorithm.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "DataInput.h"
#include "MNISTData.h"
#include "ORLData.h"

#define KMEANS_MAX_DISTANCE 1 //Max distance allowed between two iterations of the same mean vector

class Algorithm {

	private:
		DataInput *input_data;
		DataInput *pca_data; /* 2D data after applying PCA */
		Eigen::VectorXd training_data_mean_vector;
		Eigen::MatrixXd training_data_eigen_vectors;

		void visualiseImageVector(Eigen::VectorXd image_vector);

	public:
		Algorithm(MNISTData *data);
		Algorithm(ORLData *data);
		~Algorithm();

		void applyPCA(); /* Generate 2D data based on the input_data */
		void nearestClassCentroid(bool usePCA);
		void nearestSubClassCentroid(bool usePCA, int nbSubClasses);
		void nearestNeighbour(bool usePCA);
		void threadedNearestNeighbour(bool usePCA);
		void generateCSV(); /* Generate a CSV file to plot it in Matlab */
		float calculateAccuracy(bool usePCA);
};

#endif
