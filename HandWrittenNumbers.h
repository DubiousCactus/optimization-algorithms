/*
 * HandWrittenNumbers.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HANDWRITTENNUMBERS_H
#define HANDWRITTENNUMBERS_H

#include <iostream>
#include <cstdint>
#include "DataInput.h"


class HandWrittenNumbers : public DataInput {

	private:
		Eigen::VectorXf vectorise(std::vector<int8_t> pixels);

	public:
		HandWrittenNumbers(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
		
		bool loadDirectory(std::string path);
		std::vector<Element> getTrainingElements();
		std::vector<Element> getTestingElements();
		int getNbClasses();
		int getClass(int index);

};

#endif /* !HANDWRITTENNUMBERS_H */
