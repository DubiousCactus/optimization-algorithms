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
		HandWrittenNumbers(int width, int height) : DataInput(width, height) {}
};

#endif /* !HANDWRITTENNUMBERS_H */
