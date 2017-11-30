/*
 * ORLData.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "ORLData.h"
#include <iostream>
#include <fstream>
#include <string>


/* Load double values to build image vectors from text files */
void ORLData::loadDirectory(std::string path) {
	std::ifstream ocl_data_file, ocl_labels_file;
	ocl_data_file.open(path + "/orl_data.txt", std::ios::in);
	ocl_labels_file.open(path + "/orl_lbls.txt", std::ios::in);

	if (ocl_data_file.is_open() && ocl_labels_file.is_open()) {
		/* Looks like the file contains values of 8 characters, separated by tabs */
		char character;
		int n = 0;
		std::string value;
		std::vector<Eigen::VectorXd> face_vectors(400); //400 pictures

		while (!ocl_data_file.eof()) {
			face_vectors.at(n).resize(getVectorSize());
			face_vectors.at(n).setZero();

			for (int i = 0; i < getVectorSize(); i++) {
				value = "";
				/* Read characters until tab encountered: one double value */
				do {
					ocl_data_file.get(character);
					value += character;
				} while (character != '\t' && !ocl_data_file.eof());
				
				face_vectors.at(n)(i) = std::stod(value); //Adding to vector
			}

			/* Go to next vector */
			n++;
		}
	} else {
		std::cout << "/!\\ COULD NOT OPEN FILES /!\\";
		exit(1);
	}

	ocl_labels_file.close();
	ocl_data_file.close();
}
