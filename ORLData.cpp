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
/*#include "CImg.h"

using namespace cimg_library;*/

/* Recompose an image matrix from a given vector, and display it on screen.
 * NB: halts the program execution until exited
 */
void ORLData::visualiseImageVector(Eigen::VectorXd image_vector) {
    /* Build the matrix from the vector */
    /*double image_matrix[mWidth][mHeight];

    for (int i = 0; i < mWidth; i++) {
        for (int j = 0; j < mWidth; j++) {
            image_matrix[i][j] = image_vector(j + (mHeight * i));
	    std::cout  << "Matrix[" << i << "][" << j << "] = image_vector[" << j + (mHeight * i) << "]" << std::endl;
	}
    }

    CImg<double> image((const double*) image_matrix, mWidth, mHeight, 1, 1, true);
    image.display("Image");*/
}


/* Randomly split the given data in two sets: 70% in training set and 30% in the testing set */
void ORLData::randomlySplitData(std::vector<DataInput::Element> data) {
    int index = 0;
    int from, to; 
    int nbTraingingElementsInClass;

    for (int i = 0; i < mNbClasses; i++) {
	nbTraingingElementsInClass = 0.7 * (mNbElements / mNbClasses);
	from = i * (mNbElements / mNbClasses);
	to = from + (mNbElements / mNbClasses) - 1;

	while (nbTraingingElementsInClass > 0) {
	    index = rand() % (to - from + 1) + from;
	    if (data.at(index).label != -1) {
		mTrainingElements[data.at(index).label].push_back(data.at(index));
		nbTraingingElementsInClass--;
		data.at(index).label = -1;
	    }
	}
	
	/* Assing the remaining to test elements */
	for (int j = from; j < to; j++)
	    if (data.at(j).label != -1)
		mTestingElements.push_back(data.at(j));
    }
}

/* Load double values to build image vectors from text files */
void ORLData::loadDirectory(std::string path) {
    std::ifstream ocl_data_file, ocl_labels_file;
    ocl_data_file.open(path + "/orl_data.txt", std::ios::in);
    ocl_labels_file.open(path + "/orl_lbls.txt", std::ios::in);

    if (ocl_data_file.is_open() && ocl_labels_file.is_open()) {
	/* Looks like the file contains values of 8 characters, separated by tabs */
	char character;
	int n, line_number = 0;
	std::string line, label, value;
	std::vector<Eigen::VectorXd> face_vectors(mNbElements); //400 pictures
	std::vector<int> face_labels(mNbElements);
	size_t pos;
	std::string delimiter = "\t";

	while (!ocl_data_file.eof()) {
	    //* Read line by line. One line = 400 vectors/pictures /*
	    while (std::getline(ocl_data_file, line)) {
		/*Split line in values, separated by tabs,
		  and add those values to the corresponding vectors*/
		n = 0;
		if (std::getline(ocl_labels_file, label))
		    face_labels.at(line_number) = std::stod(label);

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

	std::vector<DataInput::Element> data;
	for (int i = 0; i < face_vectors.size(); i++) {
	    data.push_back({
		face_vectors.at(i),
		face_labels.at(i),
		-1
	    });
	}

	/*Eigen::IOFormat fmt(2, Eigen::DontAlignCols, "\t", " ", "", "", "", "");
	std::cout << "First vector (size = " << face_vectors.at(399).size() << ", label = " << face_labels.at(399) << "): " << face_vectors.at(399).format(fmt) << std::endl;
*/
	randomlySplitData(data);
	//visualiseImageVector(face_vectors.at(0));
    } else {
	std::cout << "/!\\ COULD NOT OPEN FILES /!\\" << std::endl;
	exit(1);
    }

    ocl_labels_file.close();
    ocl_data_file.close();
}
