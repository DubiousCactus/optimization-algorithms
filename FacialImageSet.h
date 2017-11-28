/*
 * FacialImageSet.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FACIALIMAGESET_H
#define FACIALIMAGESET_H

#include "DataInput.h"

class FacialImageSet : public DataInput {

	public:
		FacialImageSet(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
		
		virtual bool loadDirectory(std::string path) = 0;
		virtual std::vector<DataInput::Element> getTrainingElements() = 0;
		virtual std::vector<DataInput::Element> getTestingElements() = 0;
		virtual int getNbClasses() = 0;
		virtual int getClass(int index) = 0;

};

#endif /* !FACIALIMAGESET_H */
