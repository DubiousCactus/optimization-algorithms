/*
 * Main.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"

int main(int argc, char  **argv) {

	std::cout << "--- Using ORL dataset ---" << std::endl << std::endl;

	ORLData *faces = new ORLData(40, 30, 40);
	faces->loadDirectory("/home/transpalette/Code/optimization-algorithms/ORL");

	int ch = std::cin.get();

	std::cout << "--- Using MNIST dataset ---" << std::endl << std::endl;
	
	MNISTData *digits = new MNISTData(10, 28, 28);
	digits->loadDirectory("/home/transpalette/Code/optimization-algorithms/MNIST"); //Use full path

	std::cout << std::endl << "* Running Nearest Class Centroid..." << std::endl;
	
	Algorithm algo(digits);
	algo.nearestClassCentroid();

	std::cout << std::endl << "* Done ! => Accuracy: " << algo.calculateAccuracy() * 100 << "%" << std::endl;

	return 0;
}



