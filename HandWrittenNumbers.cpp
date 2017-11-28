/*
 * HandWrittenNumbers.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "HandWrittenNumbers.h"
#include "mnist-parser/mnist_reader.hpp"

bool HandWrittenNumbers::loadTrainingImages() {
	//auto dataset = mnist::read_datase
}

bool HandWrittenNumbers::loadTestingImages() {

}

bool HandWrittenNumbers::loadDirectory(std::string path) {
	bool success = true;
	this.mPath = path;
	this.loadTrainingImages();
	this.loadTestingImages();

	return success;
}
