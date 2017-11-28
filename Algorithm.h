#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include "DataInput.h"

class Algorithm {

private:

	DataInput *input_data;

public:

	Algorithm();
	~Algorithm();

	void nearestClassCentroid();
	void subClassCentroid();
	void nearestNeighbor();
};

#endif
