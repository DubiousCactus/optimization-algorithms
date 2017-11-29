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
	Eigen::VectorXf image(pixels.size());

	for (int i = 0; i < pixels.size(); i++)
		image(i) = ((float) pixels.at(i)) / 255;

	return image;
}

bool HandWrittenNumbers::loadDirectory(std::string path) {
	bool success = true;
	auto data_set = mnist::read_dataset<std::vector, std::vector, int8_t, uint8_t>(path);
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

	for (int i = 0; i < data_set.training_images.size(); i++) {
		mTrainingElements.push_back({
			vectorise(data_set.training_images.at(i)),
			data_set.training_labels.at(i)		
		});
	}

	for (auto const& it : data_set.test_images) {
		mTestingElements.push_back({
				vectorise(it),
				-1
		});
	}
		
	return success;
}

std::vector<DataInput::Element> HandWrittenNumbers::getTestingElements() {
	return mTestingElements;
}

std::vector<DataInput::Element> HandWrittenNumbers::getTrainingElements() {
	return mTrainingElements;
}

int HandWrittenNumbers::getNbClasses() {
	return mNbClasses;
}

int HandWrittenNumbers::getClass(int index) {
	return 0;
}
