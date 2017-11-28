/*
 * HandWrittenNumbers.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "HandWrittenNumbers.h"
#include "mnist-parser/mnist_reader.hpp"


/*0 to 255 for pixels */
Eigen::VectorXf HandWrittenNumbers::vectorise(std::vector<int8_t> pixels) {

}

bool HandWrittenNumbers::loadDirectory(std::string path) {
	bool success = true;
	auto data_set = mnist::read_dataset<std::vector, std::vector, int8_t, uint8_t>(this->mPath);
	/* data_set's fields:
 	 * - std::vector<Image> training_images 
	 * - std::vector<Image> testing_images
	 * - std::vector<Label> training_labels
	 * - std::vector<Label> test_labels
	 *
	 *   Image -> uint8_t (a pixel)
	 *   Label -> uint8_t (a label number)
	 *   
	 *   this->mTrainingElements = data_set.training_images;
	 * Must reshape to #pixels x #examples and convert to double and rescale to [0, 1] */

	for (auto const& it : data_set.training_images) {
		DataInput::Element element;
		element.data = vectorise(it);
		element.label = data_set.training_labels.at(&it - &data_set.training_images[0]); //Assuming that the two vectors are the same size !!
		this->mTrainingElements.push_back(element);
	}

	for (auto const& it : data_set.test_images) {
		DataInput::Element element;
		element.data = vectorise(it);
		element.label = NULL;
		this->mTestingElements.push_back(element);
	}
		
	return success;
}

int HandWrittenNumbers::getNbClasses() {
	return this->mNbClasses;
}
