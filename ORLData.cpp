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
#include "CImg.h"

using namespace cimg_library;

/* Recompose an image matrix from a given vector, and display it on screen.
 * NB: halts the program execution until exited
 */
void ORLData::visualiseImageVector(Eigen::VectorXd image_vector) {
    /* Build the matrix from the vector */
    double image_matrix[mWidth][mHeight];

    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mHeight; j++) {
            image_matrix[i][j] = image_vector(j + (mHeight * i));
	    std::cout  << "Matrix[" << i << "][" << j << "] = image_vector[" << j + (mHeight * i) << "]" << std::endl;
	}
    }

    CImg<double> image((const double*) image_matrix, mWidth, mHeight, 1, 1, true);
    image.display("Image");
}

/* Load double values to build image vectors from text files */
void ORLData::loadDirectory(std::string path) {
	std::ifstream ocl_data_file, ocl_labels_file;
	ocl_data_file.open(path + "/orl_data.txt", std::ios::in);
	ocl_labels_file.open(path + "/train_labels_ORL.dat", std::ios::in);

	if (ocl_data_file.is_open() && ocl_labels_file.is_open()) {
		/* Looks like the file contains values of 8 characters, separated by tabs */
		char character;
		int n, line_number = 0;
		std::string value;
		std::string line;
		std::vector<Eigen::VectorXd> face_vectors(400); //400 pictures
		size_t pos;
		std::string delimiter = "\t";

		while (!ocl_data_file.eof()) {
			//* Read line by line. One line = 400 vectors/pictures /*
			while (std::getline(ocl_data_file, line)) {
				 /*Split line in values, separated by tabs,
				  and add those values to the corresponding vectors*/
				n = 0;
				while ((pos = line.find(delimiter)) != std::string::npos) {
					if (face_vectors.at(n).size() != getVectorSize())
						face_vectors.at(n).resize(getVectorSize());

					value = line.substr(0, pos); //Get double value, as string
					line.erase(0, pos + delimiter.length());
					face_vectors.at(n)(line_number) = std::stod(value);
					n++;
				}
				line_number++;
			}
		}

		Eigen::IOFormat fmt(2, Eigen::DontAlignCols, "\t", " ", "", "", "", "");
		std::cout << "First vector (size = " << face_vectors.at(0).size() << "): " << face_vectors.at(0).format(fmt) << std::endl;
		int c = std::cin.get();
		visualiseImageVector(face_vectors.at(0));

		/*ocl_data_file.seekg(0);
		n = 0;
		while (!ocl_data_file.eof()) {
			face_vectors.at(n).resize(getVectorSize());
			face_vectors.at(n).setZero();

			[> Read vector by vector <]
			for (int i = 0; i < getVectorSize(); i++) {
				value = "";
				[> Read characters until tab encountered: one double value <]
				do {
					ocl_data_file.get(character);
					value += character;
				} while (character != '\t' && !ocl_data_file.eof());
				
				face_vectors.at(n)(i) = std::stod(value); //Adding to vector
			}

			std::cout << face_vectors.at(0).format(fmt) << std::endl;
			visualiseImageVector(face_vectors.at(0));
			[> Go to next vector <]
			n++;

		}*/
	} else {
		std::cout << "/!\\ COULD NOT OPEN FILES /!\\" << std::endl;
		exit(1);
	}

	ocl_labels_file.close();
	ocl_data_file.close();
}
