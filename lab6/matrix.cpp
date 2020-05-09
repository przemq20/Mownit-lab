#include "matrix.h"

Matrix::Matrix(int size) {
  std::vector<double> row;
  row.resize(size + 1, 0.0);
  std::vector<std::vector<double>> matrix;
  matrix.resize(size, row);
  this->matrix = matrix;
  this->x = size + 1;
  this->y = size;
}

Matrix::Matrix(std::vector<std::vector<double>> equation) {
  this->matrix = equation;
  this->x = equation.size();
  this->y = equation[0].size();
}

Matrix Matrix::getLMatrix() {
  int size = this->getMatrix().size();
  Matrix L(size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < i; j++) {
      L.setMatrix(i, j, this->getMatrix()[i][j]);
    }
  }
  return L;
}

Matrix Matrix::getUMatrix() {
  int size = this->getMatrix().size();
  Matrix U(size);
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      U.setMatrix(i, j, this->getMatrix()[i][j]);
    }
  }
  return U;
}

Matrix Matrix::operator+(Matrix rhs) {
  int size = this->getMatrix().size();
  Matrix result(size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result.setMatrix(i, j, this->getMatrix()[i][j] + rhs.getMatrix()[i][j]);
    }
  }
  return result;
}
