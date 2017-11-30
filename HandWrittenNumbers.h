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
		Eigen::VectorXd vectorize(std::vector<uint8_t> pixels);

	public:
		HandWrittenNumbers(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
		
		void loadDirectory(std::string path);
};

#endif /* !HANDWRITTENNUMBERS_H */
