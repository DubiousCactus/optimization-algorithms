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
	return mTrainingElements;
}

std::vector<DataInput::Element> FacialImageSet::getTestingElements() {
	return mTestingElements;
}

int FacialImageSet::getNbClasses() {
	return mNbClasses;
}

int FacialImageSet::getClass(int index) {
	return 0;
}
