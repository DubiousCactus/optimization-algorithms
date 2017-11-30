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

	public:
		ORLData(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
		
		void loadDirectory(std::string path);
};

#endif /* !FACIALIMAGESET_H */
