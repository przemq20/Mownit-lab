#include "aghMatrix.h"
#include <math.h>
#include <iomanip>
#include <iostream>

// Parameter Constructor
template <typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) {
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
template <typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) {
	matrix.resize(_rows);
	for (unsigned i = 0; i < matrix.size(); i++) {
		matrix[i].resize(_cols, _initial);
	}
	rows = _rows;
	cols = _cols;
}

// Copy Constructor
template <typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) {
	matrix = rhs.matrix;
	rows = rhs.get_rows();
	cols = rhs.get_cols();
}

// Get the number of rows of the matrix
template <typename T>
unsigned AGHMatrix<T>::get_rows() const {
	return this->rows;
}

// Get the number of columns of the matrix
template <typename T>
unsigned AGHMatrix<T>::get_cols() const {
	return this->cols;
}

template <typename T>
void AGHMatrix<T>::set(int i, int j, T val) {
	this->matrix[i][j] = val;
}

// Assignment Operator
template <typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) {
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
template <typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) {
	return this->matrix[row][col];
}

// Access the individual elements (const)
template <typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row,
	const unsigned& col) const {
	return this->matrix[row][col];
}

// Addition of two matrices
template <typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) {
	if (this->get_cols() == rhs.get_cols() &&
		this->get_rows() == rhs.get_rows()) {
		AGHMatrix<T> res(this->get_rows(), this->get_cols(), 0);
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
template <typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) {
	if (this->get_cols() == rhs.get_rows()) {
		AGHMatrix<T> res(this->get_rows(), rhs.get_cols(), 0);
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
template <typename T>
std::ostream& operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) {
	for (int i = 0; i < matrix.get_rows(); i++) {
		for (int j = 0; j < matrix.get_cols(); j++) {
			stream << matrix(i, j) << ", ";
		}
		stream << std::endl;
	}
	stream << std::endl;

	return stream;
}

template <typename T>
bool AGHMatrix<T>::isSymmetrical() {
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

template <typename T>
T determinantOfMatrix(int n, std::vector<std::vector<T>> d) {
	std::vector<std::vector<T>> next(n, std::vector<T>(n, 0));
	T det = 0;

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

template <typename T>
T AGHMatrix<T>::determinant() {
	if (this->get_rows() != this->get_cols()) {
		throw std::invalid_argument(
			"Matrix does not have equal number of columns and rows");
	}
	else {
		return determinantOfMatrix(this->get_rows(), this->matrix);
	}
}

template <typename T>
AGHMatrix<T> AGHMatrix<T>::transpose() {
	if (this->isSymmetrical()) {
		return *this;
	}
	else {
		std::vector<std::vector<T>> matrix;
		matrix.resize(this->get_cols());
		for (unsigned i = 0; i < this->get_cols(); i++) {
			matrix[i].resize(this->get_rows(), 0);
		}

		for (int i = 0; i < this->get_cols(); i++) {
			for (int j = 0; j < this->get_rows(); j++) {
				matrix[i][j] = this->matrix[j][i];
			}
		}
		AGHMatrix<T> transposed(matrix);
		return transposed;
	}
}

template <typename T>
std::vector<AGHMatrix<T>> AGHMatrix<T>::luDecomoposition() {
	if (this->get_cols() == this->get_rows()) {
		std::vector<AGHMatrix<T>> LU;

		std::vector<std::vector<T>> L;
		L.resize(this->get_cols());
		for (unsigned i = 0; i < this->get_cols(); i++) {
			L[i].resize(this->get_rows(), 0);
		}
		std::vector<std::vector<T>> U;
		U.resize(this->get_cols());
		for (unsigned i = 0; i < this->get_cols(); i++) {
			U[i].resize(this->get_rows(), 0);
		}
		int n = this->get_cols();
		T sum = 0;
		for (int j = 0; j < n; j++) {
			U[0][j] = this->matrix[0][j];
		}
		for (int i = 0; i < n; i++) {
			L[i][i] = 1;
		}
		for (int i = 1; i < n; i++) {
			L[i][0] = this->matrix[i][0] / U[0][0];
		}
		for (int j = 1; j < n; j++) {
			for (int i = 1; i <= j; i++) {
				for (int k = 0; k <= i - 1; k++) {
					sum = sum + (L[i][k] * U[k][j]);
				}
				U[i][j] = this->matrix[i][j] - sum;
				sum = 0;
			}
			for (int i = j + 1; i < n; i++) {
				for (int k = 0; k <= j - 1; k++) {
					sum = sum + (L[i][k] * U[k][j]);
				}
				L[i][j] = (this->matrix[i][j] - sum) / U[j][j];
				sum = 0;
			}
		}

		AGHMatrix<T> Lmatrix(L);
		AGHMatrix<T> Umatrix(U);
		LU.push_back(Lmatrix);
		LU.push_back(Umatrix);
		return LU;
	}
	else {
		throw std::invalid_argument(
			"Matrix does not have equal number of columns and rows");
	}
}

template <typename T>
std::vector<AGHMatrix<T>> AGHMatrix<T>::choleskyDecomoposition() {
	if (this->isSymmetrical()) {
		std::vector<AGHMatrix<T>> result;

		std::vector<std::vector<T>> cholesky;
		cholesky.resize(this->get_cols());
		for (unsigned i = 0; i < this->get_cols(); i++) {
			cholesky[i].resize(this->get_rows(), 0);
		}

		int n = this->get_cols();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++) {
				T sum = 0;

				if (j == i) {
					for (int k = 0; k < j; k++) {
						sum += pow(cholesky[j][k], 2);
					}
					cholesky[j][j] = sqrt(this->matrix[j][j] - sum);
				}
				else {
					for (int k = 0; k < j; k++) {
						sum += (cholesky[i][k] * cholesky[j][k]);
					}
					cholesky[i][j] = (this->matrix[i][j] - sum) / cholesky[j][j];
				}
			}
		}

		AGHMatrix<T> choleskymatrix(cholesky);
		result.push_back(choleskymatrix);
		result.push_back(choleskymatrix.transpose());
		return result;
	}
	else {
		throw std::invalid_argument(
			"Matrix does not have equal number of columns and rows or is not "
			"symmetrical");
	}
}

template <typename T>
AGHMatrix<T> AGHMatrix<T>::gaussianElimination() {
	if (this->get_rows() + 1 == this->get_cols()) {
		std::vector<std::vector<T>> a = this->matrix;
		std::vector<T> results;
		int n = this->get_rows();
		T x[n];
		for (int i = 0; i < n; i++)
			for (int k = i + 1; k < n; k++)
				if (abs(a[i][i]) < abs(a[k][i]))
					for (int j = 0; j <= n; j++) {
						T temp = a[i][j];
						a[i][j] = a[k][j];
						a[k][j] = temp;
					}

		for (int i = 0; i < n - 1; i++)
			for (int k = i + 1; k < n; k++) {
				T t = a[k][i] / a[i][i];
				for (int j = 0; j <= n; j++) {
					a[k][j] = a[k][j] - t * a[i][j];
				}
			}

		AGHMatrix<T> res(a);
		return res;
	}
	else {
		throw std::invalid_argument(
			"Matrix does not represent system of equations");
	}
}

template <typename T>
std::vector<T> AGHMatrix<T>::JacobiMethod() {
	int iterations = 10000;
	if (this->get_rows() + 1 == this->get_cols()) {
		int n = this->get_rows();
		std::vector<double> x, c, old;
		x.resize(n, 0);
		c.resize(n, 0);
		old.resize(n, 0);
		bool check = true;
		int m = 0;
		do {
			for (int i = 0; i < n; i++) {
				old[i] = x[i];
			}
			for (int i = 0; i < n; i++) {
				c[i] = this->matrix[i][n];
				for (int j = 0; j < n; j++) {
					if (i != j) {
						c[i] = c[i] - this->matrix[i][j] * x[j];
					}
				}
			}
			for (int i = 0; i < n; i++) {
				x[i] = c[i] / this->matrix[i][i];
			}
			m++;
			int calc = 0;
			for (int i = 0; i < n; i++) {
				if (old[i] == x[i]) {
					calc++;
				}
			}
			if (calc == n) {
				check = false;
			}
		} while (m < iterations && check);
		std::vector<T> results;
		for (int i = 0; i < n; i++) {
			results.push_back(x[i]);
		}
		std::cout << "Iterations: " << m << std::endl;
		return results;
	}
	else {
		throw std::invalid_argument(
			"Matrix does not represent system of equations");
	}
}