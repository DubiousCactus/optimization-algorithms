/*
 * HandWrittenNumbers.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "HandWrittenNumbers.h"



HandWrittenNumbers::HandWrittenNumbers(size_t width, size_t height) {
	this.width(width);
	this.height(height);
	data(width * height);
}

HandWrittenNumbers::~HandWrittenNumbers() {
	delete data;
}

bool HandWrittenNumbers::loadDirectory(std::string path) {
	bool success = true;

	return success;
}
