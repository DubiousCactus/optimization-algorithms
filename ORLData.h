/*
 * ORLData.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FACIALIMAGESET_H
#define FACIALIMAGESET_H

#include "DataInput.h"

class ORLData : public DataInput {

	private:
		int mNbElements;

		void visualiseImageVector(Eigen::VectorXd image_vector);
		void randomlySplitData(std::vector<DataInput::Element> data);

	public:
		ORLData(int nbClasses, int width, int height, int nbElements)
			: DataInput(nbClasses, width, height) {
			mNbElements = nbElements;	
		}
		
		void loadDirectory(std::string path);
};

#endif /* !FACIALIMAGESET_H */
