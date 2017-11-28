/*
 * HandWrittenNumbers.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HANDWRITTENNUMBERS_H
#define HANDWRITTENNUMBERS_H

#include <iostream>
#include "DataInput.h"


class HandWrittenNumbers : public DataInput {

	public:
		HandWrittenNumbers(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
		
		virtual bool loadDirectory(std::string path) = 0;
		virtual std::vector<Element> getTrainingElements() = 0;
		virtual std::vector<Element> getTestingElements() = 0;
		virtual int getNbClasses() = 0;
		virtual int getClass(int index) = 0;

};

#endif /* !HANDWRITTENNUMBERS_H */
