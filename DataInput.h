/*
 * DataInput.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 *
 * This class holds a bunch of images
 */

#ifndef DATA_INPUT_H
#define DATA_INPUT_H

#include <stdio>
#include <stdlib>


class DataInput {

private:

	/* A set of vectors ? */ data_set;

public:

	DataInput();
	~DataInput();

	bool loadDirectory(std::string dir); /* Load the files in the given directory */
}

#endif
