/*
 * Main.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Algorithm.h"

int main(int argc, char  **argv) {

	srand((unsigned) time(NULL));

	std::vector<double> orl_originalScores, orl_originalExeTimes, orl_pcaScores, orl_pcaExecTimes;
	std::vector<double> originalScores, originalExeTimes, pcaScores, pcaExeTimes;
	std::vector<std::vector<double> > firstCSV, secondCSV;

	std::cout << "--- Using ORL dataset: PCA version ---" << std::endl << std::endl;

	ORLData *facesForPCA = new ORLData(40, 30, 40, 400);
	facesForPCA->loadDirectory("/home/transpalette/Code/optimization-algorithms/ORL");
	
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
	orl_originalExeTimes.push_back(algoA.nearestClassCentroid());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.nearestSubClassCentroid(2));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.nearestSubClassCentroid(3));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.nearestSubClassCentroid(5));
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.threadedNearestNeighbour());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.perceptronBPG());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);
	orl_originalExeTimes.push_back(algoA.perceptronMSE());
	orl_originalScores.push_back(algoA.calculateAccuracy() * 100);

	firstCSV.push_back(orl_originalScores);
	firstCSV.push_back(orl_originalExeTimes);
	firstCSV.push_back(orl_pcaScores);
	firstCSV.push_back(orl_pcaExecTimes);

	Algorithm::generateCSV("scored_and_times_ORL.csv", firstCSV);

	int ch = std::cin.get();

	std::cout << "--- Using MNIST dataset: PCA ---" << std::endl << std::endl;
	
	MNISTData *digitsPCA = new MNISTData(10, 28, 28);
	digitsPCA->loadDirectory("/home/transpalette/Code/optimization-algorithms/MNIST"); //Use full path

	Algorithm algoBPCA(digitsPCA);
	algoBPCA.applyPCA();
	algoBPCA.nearestClassCentroid();
	algoBPCA.nearestSubClassCentroid(2);
	algoBPCA.nearestSubClassCentroid(3);
	algoBPCA.nearestSubClassCentroid(5);
	algoBPCA.threadedNearestNeighbour();
	algoBPCA.perceptronBPG();
	algoBPCA.perceptronMSE();

	std::cout << "--- Using MNIST dataset ---" << std::endl << std::endl;

	MNISTData *digits = new MNISTData(10, 28, 28);
	digits->loadDirectory("/home/transpalette/Code/optimization-algorithms/MNIST"); //Use full path

	Algorithm algoB(digits);
	algoB.nearestClassCentroid();
	algoB.nearestSubClassCentroid(2);
	algoB.nearestSubClassCentroid(3);
	algoB.nearestSubClassCentroid(5);
	algoB.threadedNearestNeighbour();
	algoB.perceptronBPG();
	algoB.perceptronMSE();


	return 0;
}



