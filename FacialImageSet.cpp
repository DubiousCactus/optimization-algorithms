/*
 * FacialImageSet.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "FacialImageSet.h"


FacialImageSet::FacialImageSet(int width, int height) {
	this.width = width;
	this.height = height;
	elements(
}

FacialImageSet::~FacialImageSet() {
	/*Destroy the stuff */
}

bool FacialImageSet::loadDirectory(std::string dir) {
	bool success = true;

	return success;
}

std::vector FacialImageSet::getElements() {
	return elements;
}
