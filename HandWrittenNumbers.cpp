/*
 * HandWrittenNumbers.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "HandWrittenNumbers.h"
#include "mnist-parser/mnist_reader.hpp"


bool HandWrittenNumbers::loadDirectory(std::string path) {
	bool success = true;
	auto data_set = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(mPath);
	mTrainingElements data_set.training_images;

		
	return success;
}

int HandWrittenNumbers::getNbClasses() {
	return mNbClasses;
}
