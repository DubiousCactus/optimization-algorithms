/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"


Algorithm::Algorithm(HandWrittenNumbers *data) {
	input_data = data;
}

Algorithm::Algorithm(FacialImageSet *data) {
	input_data = data;
}

Algorithm::~Algorithm() {
	/* Unload and destroy stuff */
	delete input_data;
}

void Algorithm::nearestClassCentroid() {
	/* Training part: construct the mean vector of each class */
	std::vector<double> mean_class_vectors(input_data->getNbClasses());

	for (int i = 0; i < input_data->getNbClasses(); i++) {
		/* Get class at index i: if class 0 is equal to "Blue", returns "Blue" */
		auto currentClass = input_data->getClassValue(i);
		std::vector<DataInput::Element>::iterator it;
		std::vector<DataInput::Element> training_data = input_data->getTrainingElements();

		for (auto const& it : training_data) {
			/* Make sure we're updating the proper mean class vector */
			if (it.label == currentClass) {
				//mean_class_vectors.at(i) += it.data; //To be fixed, maybe average the data matrix ?
			}
		}

		/* Calculate the average of the mean vector */
		mean_class_vectors.at(i) *= 1 / input_data->getNbClasses();
	}

}
