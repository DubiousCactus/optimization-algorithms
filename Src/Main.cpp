/*
 * Main.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Logic/Algorithm.h"

int main(int argc, char  **argv) {

	srand((unsigned) time(NULL));

	std::vector<double> orl_originalScores, orl_originalExecTimes, orl_pcaScores, orl_pcaExecTimes;
	std::vector<double> mnist_originalScores, mnist_originalExecTimes, mnist_pcaScores, mnist_pcaExecTimes;
	std::vector<std::vector<double> > firstCSV, secondCSV;

	std::cout << "--- Using ORL dataset: PCA version ---" << std::endl << std::endl;

	ORLData *facesForPCA = new ORLData(40, 30, 40, 400);
	facesForPCA->loadDirectory("/home/transpalette/Code/Optimization_Project/ORL");
	
	Algorithm algoAPCA(facesForPCA);
	algoAPCA.applyPCA();

	orl_pcaExecTimes.push_back(algoAPCA.nearestClassCentroid());
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.nearestSubClassCentroid(2));
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.nearestSubClassCentroid(3));
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.nearestSubClassCentroid(5));
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.threadedNearestNeighbour());
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.perceptronBPG());
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);
	orl_pcaExecTimes.push_back(algoAPCA.perceptronMSE());
	orl_pcaScores.push_back(algoAPCA.calculateAccuracy() * 100);

	std::cout << "--- Using ORL dataset ---" << std::endl << std::endl;

	ORLData *faces = new ORLData(40, 30, 40, 400);
	faces->loadDirectory("/home/transpalette/Code/optimization-algorithms/ORL");

	Algorithm algoA(faces);
	orl_originalExecTimes.push_back(algoA.nearestClassCentroid());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.nearestSubClassCentroid(2));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.nearestSubClassCentroid(3));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.nearestSubClassCentroid(5));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.threadedNearestNeighbour());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.perceptronBPG());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExecTimes.push_back(algoA.perceptronMSE());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);

	firstCSV.push_back(orl_originalScores);
	firstCSV.push_back(orl_originalExecTimes);
	firstCSV.push_back(orl_pcaScores);
	firstCSV.push_back(orl_pcaExecTimes);

	Algorithm::generateCSV("scores_and_times_ORL.csv", firstCSV);

	std::cout << "--- Using MNIST dataset: PCA ---" << std::endl << std::endl;
	
	int ch = std::cin.get();
	MNISTData *digitsPCA = new MNISTData(10, 28, 28);
	digitsPCA->loadDirectory("/home/transpalette/Code/Optimization_Project/MNIST"); //Use full path

	Algorithm algoBPCA(digitsPCA);
	algoBPCA.applyPCA();
	mnist_pcaExecTimes.push_back(algoBPCA.nearestClassCentroid());
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.nearestSubClassCentroid(2));
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.nearestSubClassCentroid(3));
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.nearestSubClassCentroid(5));
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.threadedNearestNeighbour());
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.perceptronBPG());
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);
	mnist_pcaExecTimes.push_back(algoBPCA.perceptronMSE());
	mnist_pcaScores.push_back(algoBPCA.calculateAccuracy() * 100);

	std::cout << "--- Using MNIST dataset ---" << std::endl << std::endl;

	MNISTData *digits = new MNISTData(10, 28, 28);
	digits->loadDirectory("/home/transpalette/Code/optimization-algorithms/MNIST"); //Use full path

	Algorithm algoB(digits);
	mnist_originalExecTimes.push_back(algoB.nearestClassCentroid());
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.nearestSubClassCentroid(2));
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.nearestSubClassCentroid(3));
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.nearestSubClassCentroid(5));
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.threadedNearestNeighbour());
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.perceptronBPG());
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);
	mnist_originalExecTimes.push_back(algoB.perceptronMSE());
	mnist_originalScores.push_back(algoB.calculateAccuracy() * 100);

	secondCSV.push_back(mnist_originalScores);
	secondCSV.push_back(mnist_originalExecTimes);
	secondCSV.push_back(mnist_pcaScores);
	secondCSV.push_back(mnist_pcaExecTimes);

	Algorithm::generateCSV("scores_and_times_MNIST.csv", firstCSV);

	return 0;
}



