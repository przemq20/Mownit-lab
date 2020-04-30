#pragma once

#include <iostream>
#include <vector>

class AGHMatrix {
private:
	std::vector<std::vector<double>> matrix;
	unsigned rows;
	unsigned cols;

public:
	AGHMatrix(const std::vector<std::vector<double>>& matrix);
	AGHMatrix(const AGHMatrix& rhs);
	AGHMatrix(unsigned _rows, unsigned _cols, const double& _initial);
	virtual ~AGHMatrix() = default;

	// Operator overloading, for "standard" mathematical matrix operations
	AGHMatrix& operator=(const AGHMatrix& rhs);

	// Matrix mathematical operations
	AGHMatrix operator+(const AGHMatrix& rhs);
	AGHMatrix operator*(const AGHMatrix& rhs);

	// Access the individual elements
	double& operator()(const unsigned& row, const unsigned& col);
	const double& operator()(const unsigned& row, const unsigned& col) const;

	// Printing matrix
	std::ostream& operator<<(const AGHMatrix& matrix);

	// Access the row and column sizes
	unsigned get_rows() const;
	unsigned get_cols() const;
	void set(int i, int j, double val);

	bool isSymmetrical();
	double determinant();
	AGHMatrix transpose();
	AGHMatrix inverse();

};
