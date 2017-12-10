/*
 * Main.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"

int main(int argc, char  **argv) {

	srand((unsigned) time(NULL));

	std::cout << "--- Using ORL dataset ---" << std::endl << std::endl;

	ORLData *faces = new ORLData(40, 30, 40, 400);
	faces->loadDirectory("/home/transpalette/Code/Optimization_Project/ORL");
	Algorithm algoA(faces);
	algoA.applyPCA();
	algoA.threadedNearestNeighbour(true);
	/*algoA.nearestClassCentroid();
	algoA.nearestSubClassCentroid(2);
	algoA.nearestSubClassCentroid(3);
	algoA.nearestSubClassCentroid(5);
	algoA.threadedNearestNeighbour(false);
*/
	int ch = std::cin.get();

	std::cout << "--- Using MNIST dataset ---" << std::endl << std::endl;
	
	MNISTData *digits = new MNISTData(10, 28, 28);
	digits->loadDirectory("/home/transpalette/Code/Optimization_Project/MNIST"); //Use full path

	Algorithm algo(digits);
	/*algo.nearestClassCentroid();
	algo.nearestSubClassCentroid(2);
	algo.nearestSubClassCentroid(3);
	algo.nearestSubClassCentroid(5);
	algo.nearestNeighbour(false);
*/
	return 0;
}



