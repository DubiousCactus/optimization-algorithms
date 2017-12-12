/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"
#include <math.h>
#include <thread>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "Eigen/Eigenvalues"

Algorithm::Algorithm(MNISTData *data) {
    input_data = data;
}

Algorithm::Algorithm(ORLData *data) {
    input_data = data;
}

Algorithm::~Algorithm() {
    delete input_data;
}

void Algorithm::generateCSV(std::string fileName, std::vector<std::vector<double> > rows) {
    std::ofstream csvFile;
    csvFile.open(fileName);

    for (auto const &row : rows) {
	for (auto const &value : row) {
	    csvFile << value << ",";
	}
	csvFile << "\n";
    }

    csvFile.close();
}

double Algorithm::calculateAccuracy() {
    double positives = 0;

    for (auto const &element : input_data->getTestingElements())
	if (element.label == element.given_class)
	    positives++;

    positives /= input_data->getTestingElements().size();

    return positives;
}

double Algorithm::nearestClassCentroid() {
    std::cout << "* Running nearest class centroid" << std::endl;
    clock_t begin = clock();
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

    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;

    return double(end - begin) / CLOCKS_PER_SEC;
}

double Algorithm::nearestSubClassCentroid(int nbSubClasses) {
    std::cout << "* Running nearest sub-class centroid" << std::endl;
    clock_t begin = clock();
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
    
    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;
    
    return double(end - begin) / CLOCKS_PER_SEC;
}

double Algorithm::threadedNearestNeighbour() {
    std::cout << "* Running threaded nearest neighbour..." << std::endl;
    clock_t begin = clock();

    std::vector<std::thread> workers;
    int from, to;
    for (int i = 0; i < 4; i++) {
    from = input_data->getTestingElements().size() / 4 * i;
    to = from + input_data->getTestingElements().size() / 4;
    workers.push_back(std::thread([this, from, to]() {
	for (int i = from; i < to; i++) {
	    DataInput::Element &testing_element = input_data->getTestingElements().at(i);
	    double lowestDistance = -1;
	    for (auto const& training_class : input_data->getTrainingElements()) {
		for (auto  const& training_element : training_class.second) {
		    double distance = pow(Eigen::VectorXd(testing_element.data - training_element.data).norm(), 2);

		    if (distance < lowestDistance || lowestDistance == -1) {
			lowestDistance = distance;
			testing_element.given_class = training_class.first;
		    }
		}
	    }
	}
    }));
    }

    std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
    {
        t.join();
    });
    
    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;
    
    return double(end - begin) / CLOCKS_PER_SEC;
}


double Algorithm::nearestNeighbour() {
    std::cout << "* Running nearest neighbour..." << std::endl;
    clock_t begin = clock();
    long n = 0;

    for (auto &testing_element : input_data->getTestingElements()) {
	double lowestDistance = -1;
	for (auto const& training_class : input_data->getTrainingElements()) {
	    for (auto  const& training_element : training_class.second) {
		double distance = pow(Eigen::VectorXd(testing_element.data - training_element.data).norm(), 2);

		if (distance < lowestDistance || lowestDistance == -1) {
		    lowestDistance = distance;
		    testing_element.given_class = training_class.first;
		}
	    }
	}
	n++;
    }

    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;
    
    return double(end - begin) / CLOCKS_PER_SEC;
}


void Algorithm::train_perceptrons_MSE(Eigen::MatrixXd &weights) {
    std::cout << "\t -> Training perceptrons..." << std::endl;
  
    /* Initialize output vectors */
    Eigen::MatrixXd outputVectors(input_data->getNbClasses(), input_data->getNbTrainingElements());
    outputVectors.setOnes();
    
    for (int i = 0; i < outputVectors.cols(); i++)
	outputVectors.col(i) *= -1;

    /* Train the perceptrons */
    int n = 0, c = 0;
    for (auto const& training_class : input_data->getTrainingElements()) {
        for (auto const& training_element : training_class.second)
            outputVectors(c, n++) = 1;

        c++;
    }

    /* Build the training elements matrix */
    int i = 0;
    Eigen::MatrixXd training_elements_matrix(input_data->getVectorSize(), input_data->getNbTrainingElements());
    for (auto const& training_class : input_data->getTrainingElements())
	for (auto const& training_element : training_class.second)
	    training_elements_matrix.col(i++) = training_element.data;

    /* Build the identity matrix of the train elements matrix's size */
    Eigen::MatrixXd identity(training_elements_matrix.rows(), training_elements_matrix.rows());
    identity.setIdentity();

    /* Get the pseudo-inverse of the transposed training data and generate weights matrix */
    Eigen::MatrixXd m(training_elements_matrix * training_elements_matrix.transpose()
                     + 0.001 * identity); //Make sure the matrix will be invertible
    weights = Eigen::MatrixXd(m.inverse() * training_elements_matrix) * outputVectors.transpose();
}


void Algorithm::classify_perceptrons_MSE(Eigen::MatrixXd weights) {
    std::cout << "\t -> Classifying..." << std::endl;

    /* Build the testing elements matrix */
    int n = 0;
    Eigen::MatrixXd testing_elements_matrix(input_data->getVectorSize(), input_data->getTestingElements().size());
    for (auto const &testing_element : input_data->getTestingElements()) {
	testing_elements_matrix.col(n) = testing_element.data;
	n++;
    }

    Eigen::MatrixXd computed_elements(weights.transpose() * testing_elements_matrix);
    n = 0;
    for (auto const &training_class : input_data->getTrainingElements()) {
	for (int i = 0; i < computed_elements.cols(); i++) {
	    if (computed_elements.row(n)(i) > 0)
		input_data->getTestingElements().at(i).given_class = training_class.first;

	}
	n++;
    }
}

/* Taken from https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c */
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Algorithm::train_perceptrons_BPG(Eigen::MatrixXd &weights) {
    std::cout << "\t -> Training perceptrons..." << std::endl;

    /* Build the training elements matrix */
    int i = 0;
    Eigen::MatrixXd training_elements_matrix(input_data->getVectorSize(), input_data->getNbTrainingElements());
    for (auto const& training_class : input_data->getTrainingElements())
	for (auto const& training_element : training_class.second)
	    training_elements_matrix.col(i++) = training_element.data;

    /* Augment the data */
    Eigen::MatrixXd augmented_data(training_elements_matrix);
    augmented_data.conservativeResize(augmented_data.rows() + 1, Eigen::NoChange);
    augmented_data.row(augmented_data.rows() - 1).setOnes();

    /* Initialize the weights */
    weights.resize(input_data->getVectorSize() + 1, input_data->getNbClasses());
    weights.setOnes();
    weights.row(weights.rows() - 1).setZero(); //Augment the weights
    weights *= fRand(-0.1, 0.1); //Randomly initialize

    /* Initialize output vectors */
    Eigen::MatrixXd outputVectors(input_data->getNbClasses(), input_data->getNbTrainingElements());
    outputVectors.setOnes();
     
    for (int i = 0; i < outputVectors.cols(); i++)
	outputVectors.col(i) *= -1;
    
    /* Set the right values */
    int n = 0, c = 0;
    for (auto const& training_class : input_data->getTrainingElements()) {
        for (auto const& training_element : training_class.second)
            outputVectors(c, n++) = 1;

        c++;
    }

    std::vector<int> misclassified_elements; //Row indexes of the criterion function
    misclassified_elements.push_back(1); //Add a value to start the loop
    Eigen::MatrixXd criterion_function(input_data->getNbClasses(), input_data->getNbTrainingElements());
    criterion_function.setZero();

    c = 200; //Safety counter: stop if still misclassified elements anyway
    /* Iterate while there are misclassified elements and counter not equal to zero */
    while (!misclassified_elements.empty() && c--) {
	/* Update the criterion function */
	for (int i = 0; i < input_data->getNbTrainingElements(); i++)
	    criterion_function.col(i) = outputVectors.col(i).cwiseProduct(weights.transpose() * augmented_data.col(i));

	int n = 0;
	for (int i = 0; i < input_data->getNbClasses(); i++) {
	    /* Empty the misclassified elements */
	    misclassified_elements.clear();

	    /* Find all misclassified elements */
	    for (int k = 0; k < criterion_function.cols(); k++)
		if (criterion_function(n, k) < 0) //Misclassified !
		    misclassified_elements.push_back(k); //Add the col index to the list

	    /* Calculate the gradient and update the weights */
	    Eigen::VectorXd gradient(weights.rows());
	    gradient.setZero();

	    for (auto const &misclassified_element : misclassified_elements)
		gradient += augmented_data.col(misclassified_element) * outputVectors(n, misclassified_element);

	    gradient *= LEARNING_RATE;

	    /* Update the weights */
	    weights.col(n) += gradient;

	    n++; //Next class index (don't use i because of the offset of ORL
	}
    }
}

void Algorithm::classify_perceptrons_BPG(Eigen::MatrixXd weights) {
    std::cout << "\t -> Classifying..." << std::endl;

    /* Build the testing elements matrix */
    int n = 0;
    Eigen::MatrixXd testing_elements_matrix(input_data->getVectorSize(), input_data->getTestingElements().size());
    for (auto const &testing_element : input_data->getTestingElements()) {
	testing_elements_matrix.col(n) = testing_element.data;
	n++;
    }

    /* Augment the data */
    Eigen::MatrixXd augmented_test_elements(testing_elements_matrix);
    augmented_test_elements.conservativeResize(augmented_test_elements.rows() + 1, Eigen::NoChange);
    augmented_test_elements.row(augmented_test_elements.rows() - 1).setZero();

    /* Compute classification */
    Eigen::MatrixXd computed_elements(weights.transpose() * augmented_test_elements);
    n = 0;
    for (auto const &training_class : input_data->getTrainingElements()) {
	for (int i = 0; i < computed_elements.cols(); i++) {
	    if (computed_elements.row(n)(i) > 0)
		input_data->getTestingElements().at(i).given_class = training_class.first;

	}
	n++;
    }
}

double Algorithm::perceptronBPG() {
    std::cout << "* Running a neural network of perceptrons using Back-Propagation..." << std::endl;
    clock_t begin = clock();

    Eigen::MatrixXd weights;
    train_perceptrons_BPG(weights);
    classify_perceptrons_BPG(weights);

    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;
    
    return double(end - begin) / CLOCKS_PER_SEC;
}


double Algorithm::perceptronMSE() {
    std::cout << "* Running a neural network of perceptrons using Minimal Square Error..." << std::endl;
    clock_t begin = clock();

    Eigen::MatrixXd weights;
    train_perceptrons_MSE(weights);
    classify_perceptrons_MSE(weights);

    clock_t end = clock();
    std::cout << std::endl << "* Done ! => Accuracy: " << calculateAccuracy() * 100 << "%" << std::endl << std::endl;
    
    return double(end - begin) / CLOCKS_PER_SEC;
}

void Algorithm::applyPCA() {
    std::cout << "* Applying PCA..." << std::endl;

    Eigen::MatrixXd D;
    D.resize(input_data->getVectorSize(), 0);
    int i = 0;

    /* Join all training samples to one matrix */
    for (auto const& training_class : input_data->getTrainingElements()) {
	for (auto const &element : training_class.second) {
	    D.conservativeResize(Eigen::NoChange, D.cols() + 1);
	    D.col(D.cols() - 1) = element.data;
	}
    }

    // 1. Compute the mean image
    training_data_mean_vector = D.rowwise().mean().transpose();

    // 2. Subtract mean image from the data set to get mean centered data vector
    Eigen::MatrixXd centered(D.colwise() - training_data_mean_vector);

    // 3. Compute the covariance matrix from the mean centered data matrix
    Eigen::MatrixXd covariance = centered * centered.transpose();

    // 4. Calculate the eigenvalues and eigen vectors for the covariance matrix
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(covariance);
    Eigen::MatrixXd eigenVectors = eig.eigenvectors();
    Eigen::VectorXd eigenValues = eig.eigenvalues();

    /* Make a matrix of the two last (sorted) eigen vectors */
    Eigen::MatrixXd pca_matrix(eigenVectors.row(eigenValues.size() - 1).transpose().rows(), 2);
    pca_matrix.col(0) = eigenVectors.row(eigenValues.size() - 1).transpose();
    pca_matrix.col(1) = eigenVectors.row(eigenValues.size() - 2).transpose();
    
    training_data_eigen_vectors = pca_matrix;

    /* Apply PCA */
    for (auto &training_class : input_data->getTrainingElementsRef())
	for (auto &training_element : training_class.second)
	    training_element.data = pca_matrix.transpose() * training_element.data;

    /* Normalize testing data */
    for (auto &testing_element : input_data->getTestingElements()) {
	testing_element.data = testing_element.data - training_data_mean_vector;
	testing_element.data = pca_matrix.transpose() * testing_element.data;
    }

    input_data->setWidth(1);
    input_data->setHeight(2);

    std::cout << "* PCA applied !" << std::endl << std::endl;
}
