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

#include <vector>
#include "Eigen/Core"


class DataInput {

	public:
		typedef struct {
			Eigen::VectorXf data;
			int label;
		} Element;

	protected:
		/* Might hold a vector of matrices or smthng */
		std::vector<Element> mTrainingElements;
		std::vector<Element> mTestingElements;
		int mWidth;
		int mHeight;
		int mNbElements;
		int mNbClasses;
		std::string mPath;

	public:
		explicit DataInput(int nbClasses, int width, int height)
			: mNbClasses(nbClasses), mWidth(width), mHeight(height) {
		}

		virtual ~DataInput() {
		}

		/* Load the files in the given directory */
		virtual bool loadDirectory(std::string path) = 0;
		virtual std::vector<Element> getTrainingElements() = 0;
		virtual std::vector<Element> getTestingElements() = 0;
		virtual int getNbClasses() = 0;
		/* Return the value of the class for the given class number */
		virtual int getClass(int index) = 0;
};

#endif
