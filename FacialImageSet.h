/*
 * FacialImageSet.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef FACIALIMAGESET_H
#define FACIALIMAGESET_H

#include <iostream>
#include "DataInput.h"

class FacialImageSet : public DataInput {

	public:
		FacialImageSet(int nbClasses, int width, int height)
			: DataInput(nbClasses, width, height) {}
};

#endif /* !FACIALIMAGESET_H */
