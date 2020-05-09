#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "matrix.h"
bool difference(std::vector<double> X,
                std::vector<double> solutions,
                double accuracy = 0.0001) {
  for (int i = 0; i < (int)X.size(); i++) {
    if (fabs(X[i] - solutions[i]) > accuracy) {
      return false;
    }
  }
  return true;
}

std::vector<double> jacobiMethod(Matrix matrix,
                                 int iterations,
                                 std::vector<double> solutions) {
  int size = matrix.getMatrix().size();
  std::vector<double> X;
  X.resize(size, 0.0);
  std::vector<double> tmp;
  tmp.resize(size, 0.0);
  Matrix LU = matrix.getLMatrix() + matrix.getUMatrix();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        LU.setMatrix(i, j, 0);
      } else {
        LU.setMatrix(i, j,
                     -(matrix.getMatrix()[i][j] / matrix.getMatrix()[i][i]));
      }
    }
  }
  int current_iteration = 0;

  while (current_iteration < iterations) {
    if (difference(X, solutions)) {
      break;
    }
    for (int i = 0; i < size; i++) {
      tmp[i] = (1 / matrix.getMatrix()[i][i]) * matrix.getMatrix()[i][size];
      for (int j = 0; j < size; j++) {
        tmp[i] += LU.getMatrix()[i][j] * X[j];
      }
    }
    for (int i = 0; i < size; i++) {
      X[i] = tmp[i];
    }
    current_iteration++;
  }
  //   std::cout << current_iteration << std::endl;
  return X;
}

std::vector<double> gaussSeidelMethod(Matrix matrix,
                                      int iterations,
                                      std::vector<double> solutions) {
  int size = matrix.getMatrix().size();
  std::vector<double> X;
  X.resize(size, 0.0);
  std::vector<double> tmp;
  tmp.resize(size, 0.0);
  Matrix LU = matrix.getLMatrix() + matrix.getUMatrix();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        LU.setMatrix(i, j, 0);
      } else {
        LU.setMatrix(i, j,
                     -(matrix.getMatrix()[i][j] / matrix.getMatrix()[i][i]));
      }
    }
  }
  int current_iteration = 0;

  while (current_iteration < iterations) {
    if (difference(X, solutions)) {
      break;
    }
    for (int i = 0; i < size; i++) {
      tmp[i] = (1 / matrix.getMatrix()[i][i]) * matrix.getMatrix()[i][size];
      for (int j = 0; j < size; j++) {
        if (j < i) {
          tmp[i] += LU.getMatrix()[i][j] * tmp[j];
        } else if (j > i) {
          tmp[i] += LU.getMatrix()[i][j] * X[j];
        }
      }
    }
    for (int i = 0; i < size; i++) {
      X[i] = tmp[i];
    }
    current_iteration++;
  }
  //   std::cout << current_iteration << std::endl;
  return X;
}

// int SORMethod(Matrix matrix,
std::pair<std::vector<double>, int> SORMethod(Matrix matrix,
                                              int iterations,
                                              double w,
                                              std::vector<double> solutions) {
  int size = matrix.getMatrix().size();
  std::vector<double> X;
  X.resize(size, 0.0);
  std::vector<double> tmp;
  tmp.resize(size, 0.0);
  Matrix LU = matrix.getLMatrix() + matrix.getUMatrix();

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        LU.setMatrix(i, j, 0);
      } else {
        LU.setMatrix(i, j,
                     -(matrix.getMatrix()[i][j] / matrix.getMatrix()[i][i]));
      }
    }
  }
  int current_iteration = 0;

  while (current_iteration < iterations) {
    if (difference(X, solutions)) {
      break;
    }
    for (int i = 0; i < size; i++) {
      tmp[i] = (1 / matrix.getMatrix()[i][i]) * matrix.getMatrix()[i][size];
      for (int j = 0; j < size; j++) {
        if (j < i) {
          tmp[i] += LU.getMatrix()[i][j] * tmp[j];
        } else if (j > i) {
          tmp[i] += LU.getMatrix()[i][j] * X[j];
        }
      }
    }
    for (int i = 0; i < size; i++) {
      X[i] = w * tmp[i] + (1 - w) * X[i];
    }
    current_iteration++;
  }
  //   std::cout << current_iteration << std::endl;
  //   return current_iteration;
  std::pair<std::vector<double>, int> res;
  res.first = X;
  res.second = current_iteration;
  return res;
}

double findOmega(std::vector<std::vector<double>> matrix,
                 std::vector<double> solutions) {
  int min = 10000;
  double omega = 0;
  double i = 0;
  while (i <= 2) {
    if (SORMethod(matrix, 1000, i, solutions).second < min) {
      min = SORMethod(matrix, 1000, i, solutions).second;
      omega = i;
    }
    i += 0.01;
  }
  return omega;
}

void findError(std::vector<std::vector<double>> matrix,
               std::vector<double> solutions,
               double relax,
               int num) {
  std::ofstream plik;
  std::string name = "zbieznosc" + std::to_string(num) + ".txt";
  plik.open(name);
  for (int i = 1; i < 50; i++) {
    std::vector<double> jac = jacobiMethod(matrix, i, solutions);
    std::vector<double> gau = gaussSeidelMethod(matrix, i, solutions);
    std::vector<double> sor = SORMethod(matrix, i, relax, solutions).first;

    double err_jac = 0;
    double err_gau = 0;
    double err_sor = 0;

    for (int j = 0; j < (int)jac.size(); j++) {
      err_jac += fabs(jac[j] - solutions[j]);
      err_gau += fabs(gau[j] - solutions[j]);
      err_sor += fabs(sor[j] - solutions[j]);
    }
    plik << i << ":" << err_jac << ":" << err_gau << ":" << err_sor
         << std::endl;
    err_jac = 0;
    err_gau = 0;
    err_sor = 0;
  }
}