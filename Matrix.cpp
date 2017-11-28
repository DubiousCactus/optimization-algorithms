/*
 * Matrix.cpp
 * Copyright (C) 2017 transpalette <transpalette@arch-cactus>
 *
 * Distributed under terms of the MIT license.
 */

#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t columns) {
	this.rows(rows);
	this.columns(columns);
	data(rows * columns);
}

Matrix::~Matrix() {
	delete data;
}

double& Matrix::operator()(size_t i, size_t j) {
    return mData[i * mCols + j];
}

double Matrix::operator()(size_t i, size_t j) const {
    return mData[i * mCols + j];
}
