#pragma once

#include <iostream>
#include <vector>

template <typename T>
class AGHMatrix {
private:
	std::vector<std::vector<T>> matrix;
	unsigned rows;
	unsigned cols;

public:
	AGHMatrix(const std::vector<std::vector<T>>& matrix);
	AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial);
	AGHMatrix(const AGHMatrix<T>& rhs);
	virtual ~AGHMatrix() = default;

	// Operator overloading, for "standard" mathematical matrix operations
	AGHMatrix<T>& operator=(const AGHMatrix<T>& rhs);

	// Matrix mathematical operations
	AGHMatrix<T> operator+(const AGHMatrix<T>& rhs);
	AGHMatrix<T> operator*(const AGHMatrix<T>& rhs);

	// Access the individual elements
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	// Printing matrix
	std::ostream& operator<<(const AGHMatrix<T>& matrix);

	// Access the row and column sizes
	unsigned get_rows() const;
	unsigned get_cols() const;
	void set(int i, int j, T val);

	bool isSymmetrical();
	T determinant();
	AGHMatrix<T> transpose();
	std::vector<AGHMatrix<T>> luDecomoposition();
	std::vector<AGHMatrix<T>> choleskyDecomoposition();
	AGHMatrix<T> gaussianElimination();
	std::vector<T> JacobiMethod();
};

#include "aghMatrix.cpp"
