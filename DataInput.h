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
			Eigen::VectorXd data; //Vector of doubles
			int label;
			int given_class;
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
		virtual void loadDirectory(std::string path) = 0;
		
		std::vector<Element> getTrainingElements() { return mTrainingElements; }
		std::vector<Element> getTestingElements() { return mTestingElements; }
		int getNbClasses() { return mNbClasses; }
		/* Return the value of the class for the given class number */
		int getClass(int index) { return index; }
		int getVectorSize() { return mWidth * mHeight; }
		int getWidth() { return mWidth; }
		int getHeight() { return mHeight; }
};

#endif
