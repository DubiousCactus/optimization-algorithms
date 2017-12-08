/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"
#include <math.h>
#include "CImg.h"

using namespace cimg_library;


Algorithm::Algorithm(MNISTData *data) {
    input_data = data;
}

Algorithm::Algorithm(ORLData *data) {
    input_data = data;
}

Algorithm::~Algorithm() {
    delete input_data;
    delete pca_data;
}

void Algorithm::visualiseData() {

}

/* Recompose an image matrix from a given vector, and display it on screen.
 * NB: halts the program execution until exited
 */
void Algorithm::visualiseImageVector(Eigen::VectorXd image_vector) {
    /* Build the matrix from the vector */
    int width = input_data->getWidth();
    int height = input_data->getHeight();
    double image_matrix[width][height];

    for (int i = 0; i < image_vector.size() / width; i++)
	for (int j = 0; j < height; j++)
	    image_matrix[i][j] = image_vector(j + (width * i));

    CImg<double> image((const double*) image_matrix, width, height, 1, 1, true);
    image.display("Image");
}

float Algorithm::calculateAccuracy() {
    float positives = 0;

    for (auto const &element : input_data->getTestingElements())
	if (element.label == element.given_class)
	    positives++;

    positives /= input_data->getTestingElements().size();

    return positives;
}

void Algorithm::nearestClassCentroid() {
    /* Training part: construct the mean vector of each class */
    std::map<int, Eigen::VectorXd> mean_class_vectors;

    std::cout << "\t-> Building mean class vectors..." << std::endl;
    for (auto const& training_class : input_data->getTrainingElements()) {
	/* Get class at index i: if class 0 is equal to "Blue", returns "Blue" */
	mean_class_vectors[training_class.first].resize(input_data->getVectorSize()); //Set Eigen Vector size
	mean_class_vectors[training_class.first].setZero();
	/* Iterate through the training data for the current class */
	for (auto const& element : training_class.second)
	    mean_class_vectors.at(training_class.first) += element.data; //Add up this picture's vector

	/* Calculate the average of the mean vector */
	mean_class_vectors.at(training_class.first) = mean_class_vectors.at(training_class.first) / training_class.second.size();
    }

    /* Classification part: classify the element to the smallest distance between
     * itself and each mean vector 
     */
    std::cout << "\t-> Running classification..." << std::endl;
    for (auto &element : input_data->getTestingElements()) {
	/* Calculate the distance for each mean class vector */
	double distance = 0, minDistance = 0;
	int optimumClass = 0;

	for (auto const& mean_class_vector : mean_class_vectors) {
	    distance = pow(Eigen::VectorXd(element.data - mean_class_vector.second).norm(), 2.0);

	    if (distance < minDistance || !minDistance) {
		minDistance = distance;
		optimumClass = mean_class_vector.first;
	    }
	}

	/* Classify the element by setting its label to the best match */
	element.given_class = optimumClass;
    }
	
    /*std::cout << "\t-> Visualizing first test element: label -> " << input_data->getTestingElements().at(0).label << " - class -> "
       << input_data->getTestingElements().at(0).given_class << std::endl;	
    visualiseImageVector(input_data->getTestingElements().at(0).data);*/
}

void Algorithm::nearestSubClassCentroid(int nbSubClasses) {
    /* Training part: apply K-means on the training data to find sub classes */
    bool iterate = true;
    double lowestDistance = -1;
    std::map<int, Eigen::MatrixXd> sub_classes;
    std::map<int, Eigen::VectorXd> mean_vectors; /* class -> mean vector */
    std::map<int, double> l; /* class -> distance */

    while (iterate) {
	for (auto const& training_class : input_data->getTrainingElements()) {
	    for (auto const& training_element : training_class.second) {
		lowestDistance = -1;
		for (int i = 0; i < nbSubClasses; i++) {
		    double distance = pow(Eigen::VectorXd(training_element.data - mean_vectors[i]).norm(), 2);
		    if (distance < lowestDistance || lowestDistance == -1) {
			lowestDistance = distance;
			sub_classes[i].conservativeResize(training_element.data.size(), sub_classes[i].cols() + 1);
			sub_classes[i].col(sub_classes[i].cols() - 1) = training_element.data;
		    }
		}
	    }
	}

	/* Update mean vectors */
	for (int i = 0; i < nbSubClasses; i++)
	    mean_vectors[i] = sub_classes[i].mean(); //Should be the mean of all the vectors of sub class i
    }
}

