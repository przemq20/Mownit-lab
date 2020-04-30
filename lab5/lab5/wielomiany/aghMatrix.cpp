#include "aghMatrix.h"
#include <math.h>
#include <iomanip>
#include <iostream>

// Parameter Constructor

AGHMatrix::AGHMatrix(const std::vector<std::vector<double>>& mat) {
	matrix.resize(mat.size());
	for (unsigned i = 0; i < mat.size(); i++) {
		matrix[i].resize(mat[i].size());
		for (unsigned j = 0; j < mat[i].size(); j++) {
			matrix[i][j] = mat[i][j];
		}
	}
	rows = matrix.size();
	cols = matrix[1].size();
}

// Parameter Constructor

AGHMatrix::AGHMatrix(unsigned _rows, unsigned _cols, const double& _initial) {
	matrix.resize(_rows);
	for (unsigned i = 0; i < matrix.size(); i++) {
		matrix[i].resize(_cols, _initial);
	}
	rows = _rows;
	cols = _cols;
}

// Copy Constructor

AGHMatrix::AGHMatrix(const AGHMatrix& rhs) {
	matrix = rhs.matrix;
	rows = rhs.get_rows();
	cols = rhs.get_cols();
}

// Get the number of rows of the matrix

unsigned AGHMatrix::get_rows() const {
	return this->rows;
}

// Get the number of columns of the matrix

unsigned AGHMatrix::get_cols() const {
	return this->cols;
}


void AGHMatrix::set(int i, int j, double val) {
	this->matrix[i][j] = val;
}

// Assignment Operator

AGHMatrix& AGHMatrix::operator=(const AGHMatrix& rhs) {
	if (&rhs == this)
		return *this;

	unsigned new_rows = rhs.get_rows();
	unsigned new_cols = rhs.get_cols();

	matrix.resize(new_rows);
	for (unsigned i = 0; i < matrix.size(); i++) {
		matrix[i].resize(new_cols);
	}

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++) {
			matrix[i][j] = rhs(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;

	return *this;
}

// Access the individual elements

double& AGHMatrix::operator()(const unsigned& row, const unsigned& col) {
	return this->matrix[row][col];
}

// Access the individual elements (const)

const double& AGHMatrix::operator()(const unsigned& row,
	const unsigned& col) const {
	return this->matrix[row][col];
}

// Addition of two matrices

AGHMatrix AGHMatrix::operator+(const AGHMatrix& rhs) {
	if (this->get_cols() == rhs.get_cols() &&
		this->get_rows() == rhs.get_rows()) {
		AGHMatrix res(this->get_rows(), this->get_cols(), 0);
		for (int i = 0; i < this->get_rows(); i++) {
			for (int j = 0; j < this->get_cols(); j++) {
				res.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
			}
		}
		return res;
	}
	else {
		throw std::invalid_argument(
			"Matrixes does not have equal number of columns or rows");
	}
}

// Left multiplication of this matrix and another

AGHMatrix AGHMatrix::operator*(const AGHMatrix& rhs) {
	if (this->get_cols() == rhs.get_rows()) {
		AGHMatrix res(this->get_rows(), rhs.get_cols(), 0);
		for (int i = 0; i < this->get_rows(); i++) {
			for (int j = 0; j < rhs.get_cols(); j++) {
				for (int k = 0; k < this->get_cols(); k++) {
					res.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
				}
			}
		}
		return res;
	}
	else {
		throw std::invalid_argument(
			"Number of columns of first matrix is not equal to number of rows of "
			"second matrix");
	}
}

// Printing matrix

std::ostream& operator<<(std::ostream& stream, const AGHMatrix& matrix) {
	for (int i = 0; i < matrix.get_rows(); i++) {
		for (int j = 0; j < matrix.get_cols(); j++) {
			stream << matrix(i, j) << ", ";
		}
		stream << std::endl;
	}
	stream << std::endl;

	return stream;
}


bool AGHMatrix::isSymmetrical() {
	if (this->get_rows() != this->get_cols()) {
		return false;
	}

	for (int i = 0; i < this->get_rows(); i++) {
		for (int j = 0; j < this->get_cols(); j++) {
			if (this->matrix[i][j] != this->matrix[j][i]) {
				return false;
			}
		}
	}
	return true;
}


double determinantOfMatrix(int n, std::vector<std::vector<double>>d) {
	std::vector<std::vector<double>> next(n, std::vector<double>(n, 0));
	double det = 0;

	if (n == 1) {
		return d[0][0];
	}
	else {
		for (int c = 0; c < n; c++) {
			int y = 0, x = 0;
			for (int i = 1; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j != c) {
						next[y][x] = d[i][j];
						x++;
					}
				}
				y++;
				x = 0;
			}
			if (c % 2 == 0) {
				det += d[0][c] * determinantOfMatrix(n - 1, next);
			}
			else {
				det -= d[0][c] * determinantOfMatrix(n - 1, next);
			}
		}
	}
	return det;
}


double AGHMatrix::determinant() {
	if (this->get_rows() != this->get_cols()) {
		throw std::invalid_argument(
			"Matrix does not have equal number of columns and rows");
	}
	else {
		return determinantOfMatrix(this->get_rows(), this->matrix);
	}
}


AGHMatrix AGHMatrix::transpose() {
	if (this->isSymmetrical()) {
		return *this;
	}
	else {
		std::vector<std::vector<double>> matrix;
		matrix.resize(this->get_cols());
		for (unsigned i = 0; i < this->get_cols(); i++) {
			matrix[i].resize(this->get_rows(), 0);
		}

		for (int i = 0; i < this->get_cols(); i++) {
			for (int j = 0; j < this->get_rows(); j++) {
				matrix[i][j] = this->matrix[j][i];
			}
		}
		AGHMatrix transposed(matrix);
		return transposed;
	}
}

AGHMatrix AGHMatrix::inverse() {

}


