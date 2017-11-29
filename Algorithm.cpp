/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"
#include "Eigen/Core"
#include <math.h>


Algorithm::Algorithm(HandWrittenNumbers *data) {
	input_data = data;
}

Algorithm::Algorithm(FacialImageSet *data) {
	input_data = data;
}

Algorithm::~Algorithm() {
	delete input_data;
}

void Algorithm::nearestClassCentroid() {
	/* Training part: construct the mean vector of each class */
	std::vector<Eigen::VectorXf> mean_class_vectors(input_data->getNbClasses());

	for (int i = 0; i < input_data->getNbClasses(); i++) {
		/* Get class at index i: if class 0 is equal to "Blue", returns "Blue" */
		auto currentClass = input_data->getClass(i);
		mean_class_vectors.at(i).resize(input_data->getVectorSize()); //Set Eigen Vector size

		/* Iterate through the training data, it is an iterator representing a training Element (see struct) */
		for (auto const& element : input_data->getTrainingElements()) {
			/* Make sure we're updating the proper mean class vector */
			if (element.label == currentClass)
				mean_class_vectors.at(i) += element.data; //Add up this picture's vector
		}

		/* Calculate the average of the mean vector */
		mean_class_vectors.at(i) *= 1 / input_data->getNbClasses();
	}

	/* Classification part: classify the element to the smallest distance between
 	 * itself and each mean vector 
	 */
	for (auto &element : input_data->getTestingElements()) {
		/* Calculate the distance for each mean class vector */
		float distance, minDistance = 0;
		int optimumClass = 0;

		for (int i = 0; i < input_data->getNbClasses(); i++) {
			Eigen::VectorXf diffVector(element.data - mean_class_vectors.at(i));
			distance = pow(diffVector.norm(), 2.0f);

			if (distance < minDistance || !minDistance) {
				minDistance = distance;
				optimumClass = i;
			}
		}

		/* Classify the element by setting its label to the best match */
		element.label = input_data->getClass(optimumClass);
	}

}
