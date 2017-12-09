/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"
#include <math.h>/*
#include "CImg.h"

using namespace cimg_library;*/


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
/*    int width = input_data->getWidth();
    int height = input_data->getHeight();
    double image_matrix[width][height];

    for (int i = 0; i < image_vector.size() / width; i++)
	for (int j = 0; j < height; j++)
	    image_matrix[i][j] = image_vector(j + (width * i));

    CImg<double> image((const double*) image_matrix, width, height, 1, 1, true);
    image.display("Image");*/
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
    bool iterate;
    double lowestDistance;
    int lowestDistanceSubClass;
    std::map<int, Eigen::MatrixXd> sub_classes;
    std::map<int, std::vector<Eigen::VectorXd>> mean_vectors; /* class -> mean vector */

    Eigen::IOFormat fmt(2, Eigen::DontAlignCols, "\t", " ", "", "", "", "");

    std::cout << "\t-> Building mean class vectors (" << nbSubClasses << " subclasses)..." << std::endl;
    for (auto const& training_class : input_data->getTrainingElements()) {
        mean_vectors[training_class.first].resize(nbSubClasses);

        /* Init mean vectors */
        for (int i = 0; i < nbSubClasses; i++)
            mean_vectors[training_class.first].at(i) = training_class.second.at(i).data;

        /* Init sub classes vectors */
        for (int i = 0; i < nbSubClasses; i++) {
            sub_classes[i].resize(input_data->getVectorSize(), 0);
            sub_classes[i].setZero();
        }

        /* Run K-means */
        iterate = true;
        while (iterate) {
            for (auto const &training_element : training_class.second) {
                lowestDistance = -1;
                lowestDistanceSubClass = 0;
                for (int i = 0; i < nbSubClasses; i++) {
                    double distance = pow(
                            Eigen::VectorXd(training_element.data - mean_vectors[training_class.first].at(i)).norm(),
                            2);
                    if (distance < lowestDistance || lowestDistance == -1) {
                        lowestDistance = distance;
                        lowestDistanceSubClass = i;
                    }
                }
                sub_classes[lowestDistanceSubClass].conservativeResize(Eigen::NoChange, sub_classes[lowestDistanceSubClass].cols() + 1);
                sub_classes[lowestDistanceSubClass].col(sub_classes[lowestDistanceSubClass].cols() - 1) = training_element.data;
            }
            
            /* Check mean vectors movement: if the distance between the last iteration and this one is outside
             * the acceptance window, then we stop iterating and consider the K-means algorithm to be done */
            iterate = false;
            for (int i = 0; i < nbSubClasses; i++) {
                if (pow(
                        Eigen::VectorXd(sub_classes[i].rowwise().mean() - mean_vectors[training_class.first].at(i)).norm(),
                        2) > KMEANS_MAX_DISTANCE)
                    iterate = true;

                /* Update mean vectors */
                mean_vectors[training_class.first].at(i) = sub_classes[i].rowwise().mean();
            }
        }
    }

    /* Run NCC */
    std::cout << "\t-> Running classification..." << std::endl;
    for (auto &element : input_data->getTestingElements()) {
        /* Calculate the distance for each mean class vector */
        double distance = 0, minDistance = 0;
        int optimumClass = 0;

        for (auto const& sub_class_vectors : mean_vectors) {
            for (auto const &mean_vector : sub_class_vectors.second) {
                distance = pow(Eigen::VectorXd(element.data - mean_vector).norm(), 2.0);

                if (distance < minDistance || !minDistance) {
                    minDistance = distance;
                    optimumClass = sub_class_vectors.first;
                }
            }
        }

        /* Classify the element by setting its label to the best match */
        element.given_class = optimumClass;
    }
}

