#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio>
#include <stdlib>

class Algorithm {

private:

	private DataInput input_data;

public:

	Algorithm();
	~Algorithm();

	void nearestClassCentroid();
	void subClassCentroid();
	void nearestNeighbor();
}

#endif
