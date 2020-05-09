#include <vector>

class Matrix {
 private:
  std::vector<std::vector<double>> matrix;
  int x;
  int y;

 public:
  Matrix(int size);
  Matrix(std::vector<std::vector<double>> equation);
  int getx() const { return x; }
  int gety() const { return y; }
  std::vector<std::vector<double>> getMatrix() { return matrix; }
  void setMatrix(int i, int j, double val) { this->matrix[i][j] = val; }
  Matrix getLMatrix();
  Matrix getUMatrix();
  Matrix operator+(Matrix rhs);
};
