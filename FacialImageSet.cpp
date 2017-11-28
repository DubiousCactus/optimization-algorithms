/*
 * FacialImageSet.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "FacialImageSet.h"


bool FacialImageSet::loadDirectory(std::string path) {
	bool success = true;

	/* Implement the matlab script here ... */

	return success;
}

std::vector<DataInput::Element> FacialImageSet::getTrainingElements() {
	return this->mTrainingElements;
}

std::vector<DataInput::Element> FacialImageSet::getTestingElements() {
	return this->mTestingElements;
}
