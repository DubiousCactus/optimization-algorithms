/*
 * Algorithm.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"


Algorithm::Algorithm() {
	/* Load input data */
	input_data = new DataInput();
	/* Load GUI if doing visualization */
}

Algorithm::~Algorithm() {
	/* Unload and destroy stuff */
	delete input_data;
}

void Algorithm::nearestClassCentroid() {
	/* Act on the loaded data */

}
