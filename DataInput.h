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
#include <map>
#include "Eigen/Core"


class DataInput {

	public:
		typedef struct {
			Eigen::VectorXd data; //Vector of doubles
			int label;
			int given_class;
		} Element;

	protected:
		std::map<int, std::vector<Element>> mTrainingElements;
		std::vector<Element> mTestingElements;
		int mWidth;
		int mHeight;
		int mNbClasses;

	public:
		explicit DataInput(int nbClasses, int width, int height)
			: mNbClasses(nbClasses), mWidth(width), mHeight(height) {
		}

		explicit DataInput(const DataInput &obj) {
			mTrainingElements = obj.mTrainingElements;
			mTestingElements = obj.mTestingElements;
			mWidth = obj.mWidth;
			mHeight = obj.mHeight;
			mNbClasses = obj.mNbClasses;
		}

		virtual ~DataInput() {
		}

		/* Load the files in the given directory */
		virtual void loadDirectory(std::string path) = 0;
		
		std::map<int, std::vector<Element>> getTrainingElements() { return mTrainingElements; }
		std::map<int, std::vector<Element>> &getTrainingElementsRef() { return mTrainingElements; }
		std::vector<Element> &getTestingElements() { return mTestingElements; }
		int getNbClasses() { return mNbClasses; }
		int getVectorSize() { return mWidth * mHeight; }
		int getWidth() { return mWidth; }
		int getHeight() { return mHeight; }
};

#endif
