/*
 * DataInput.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 *
 * This abstract class holds a bunch of images, and is to be
 * implemented by specific data types such as MNIST or ORL.
 */

#ifndef DATA_INPUT_H
#define DATA_INPUT_H

#include <iostream>
#include "Matrix.h"


class DataInput {

	public:
		typedef struct {
			Matrix data;
			std::string label;
		} Element;

	private:
		/* Might hold a vector of matrices or smthng */
		std::vector<Element> elements;
		int width;
		int height;

	public:
		/* Load the files in the given directory */
		virtual bool loadDirectory(std::string path) = 0;
		virtual std::vector getElements() = 0;
};

#endif
