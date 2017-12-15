/*
 * MNISTData.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "MNISTData.h"
#include "../mnist-parser/mnist_reader.hpp"


/* 0 to 255 for pixels */
Eigen::VectorXd MNISTData::vectorize(std::vector<uint8_t> pixels) {
	Eigen::VectorXd image(pixels.size());

	for (unsigned long i = 0; i < pixels.size(); i++)
		image(i) = ((double) pixels.at(i)) / 255; //Rescale to [0,1]

	return image;
}

void MNISTData::loadDirectory(std::string path) {
	std::cout << "* Loading dataset..." << std::endl;
	auto data_set = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(path);
	/* data_set's fields:
 	 * - std::vector<Image> training_images 
	 * - std::vector<Image> test_images
	 * - std::vector<Label> training_labels
	 * - std::vector<Label> test_labels
	 *
	 *   Image -> uint8_t (a pixel)
	 *   Label -> uint8_t (a label number)
	 *   
	 *   this->mTrainingElements = data_set.training_images;
	 * Must reshape to #pixels x #examples and convert to double and rescale to [0, 1] */

	std::cout << "* Vectorizing training images..." << std::endl;
	for (int i = 0; i < data_set.training_images.size(); i++) {
		mTrainingElements[data_set.training_labels.at(i)].push_back({
			vectorize(data_set.training_images.at(i)),
			data_set.training_labels.at(i),
			-1	
		});
	}

	std::cout << "* Vectorizing testing images..." << std::endl;
	for (int i = 0; i < data_set.test_images.size(); i++) {
		mTestingElements.push_back({
				vectorize(data_set.test_images.at(i)),
				data_set.test_labels.at(i),
				-1
		});
	}
}

