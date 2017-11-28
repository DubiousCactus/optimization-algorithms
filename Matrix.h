/*
 * Matrix.h
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


class Matrix {

	private:
		size_t rows;
		size_t columns;
		std::vector<double> data;

	public:
		Matrix(size_t rows, size_t columns);
		~Matrix();
		double& operator()(size_t i, size_t j);
		double operator()(size_t i, size_t j) const;
};


#endif /* !MATRIX_H */
