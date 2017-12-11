/*
 * Main.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"

int main(int argc, char  **argv) {

	srand((unsigned) time(NULL));


	std::cout << "--- Using ORL dataset: PCA version ---" << std::endl << std::endl;

	ORLData *facesForPCA = new ORLData(40, 30, 40, 400);
	facesForPCA->loadDirectory("/home/transpalette/Code/Optimization_Project/ORL");
	
	Algorithm algoAPCA(facesForPCA);
	algoAPCA.applyPCA();
	algoAPCA.nearestClassCentroid();
	algoAPCA.nearestSubClassCentroid(2);
	algoAPCA.nearestSubClassCentroid(3);
	algoAPCA.nearestSubClassCentroid(5);
	algoAPCA.threadedNearestNeighbour();

	std::cout << "--- Using ORL dataset ---" << std::endl << std::endl;

	ORLData *faces = new ORLData(40, 30, 40, 400);
	faces->loadDirectory("/home/transpalette/Code/Optimization_Project/ORL");

	Algorithm algoA(faces);
	algoA.nearestClassCentroid();
	algoA.nearestSubClassCentroid(2);
	algoA.nearestSubClassCentroid(3);
	algoA.nearestSubClassCentroid(5);
	algoA.threadedNearestNeighbour();

	int ch = std::cin.get();

	std::cout << "--- Using MNIST dataset: PCA ---" << std::endl << std::endl;
	
	MNISTData *digitsPCA = new MNISTData(10, 28, 28);
	digitsPCA->loadDirectory("/home/transpalette/Code/Optimization_Project/MNIST"); //Use full path

	Algorithm algoBPCA(digitsPCA);
	algoBPCA.nearestClassCentroid();
	algoBPCA.nearestSubClassCentroid(2);
	algoBPCA.nearestSubClassCentroid(3);
	algoBPCA.nearestSubClassCentroid(5);
	algoBPCA.threadedNearestNeighbour();



	std::cout << "--- Using MNIST dataset ---" << std::endl << std::endl;

	MNISTData *digits = new MNISTData(10, 28, 28);
	digits->loadDirectory("/home/transpalette/Code/Optimization_Project/MNIST"); //Use full path

	Algorithm algoB(digits);
	/*algoB.nearestClassCentroid();
	algoB.nearestSubClassCentroid(2);
	algoB.nearestSubClassCentroid(3);
	algoB.nearestSubClassCentroid(5);*/
	algoB.threadedNearestNeighbour();


	return 0;
}



