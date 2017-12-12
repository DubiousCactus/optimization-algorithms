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
#define LEARNING_RATE 0.1

class Algorithm {

	private:
		DataInput *input_data;
		Eigen::VectorXd training_data_mean_vector;
		Eigen::MatrixXd training_data_eigen_vectors;

		void train_perceptrons_MSE(Eigen::MatrixXd &weights);
		void train_perceptrons_BPG(Eigen::MatrixXd &weights);
		void classify_perceptrons_MSE(Eigen::MatrixXd weights);
		void classify_perceptrons_BPG(Eigen::MatrixXd weights);

	public:
		Algorithm(MNISTData *data);
		Algorithm(ORLData *data);
		~Algorithm();

		void applyPCA(); /* Generate 2D data based on the input_data */
		double nearestClassCentroid();
		double nearestSubClassCentroid(int nbSubClasses);
		double nearestNeighbour();
		double threadedNearestNeighbour();
		double perceptronBPG(); //Back-propagation
		double perceptronMSE(); //Minimal Square Error
		static void generateCSV(std::string fileName, std::vector<std::vector<double> > rows); /* Generate a CSV file to plot it in Matlab */
		double calculateAccuracy();
};

#endif
