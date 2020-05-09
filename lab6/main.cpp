
#include <iostream>
#include <vector>

#include "equations.h"
#include "methods.h"

int main() {
  //   std::vector<double> x1 = jacobiMethod(r1, 1000, sol1);
  //   std::vector<double> x2 = jacobiMethod(r2, 1000, sol2);
  //   std::vector<double> x3 = jacobiMethod(r3, 1000, sol3);
  //   std::vector<double> x4 = jacobiMethod(r4, 1000, sol4);
  //   std::vector<double> x5 = jacobiMethod(r5, 1000, sol5);
  //   std::vector<double> x6 = gaussSeidelMethod(r1, 1000, sol1);
  //   std::vector<double> x7 = gaussSeidelMethod(r2, 1000, sol2);
  //   std::vector<double> x8 = gaussSeidelMethod(r3, 1000, sol3);
  //   std::vector<double> x9 = gaussSeidelMethod(r4, 1000, sol4);
  //   std::vector<double> x10 = gaussSeidelMethod(r5, 1000, sol5);
  //   std::vector<double> x6 = SORMethod(r1, 1000, 0.75, sol1).first;
  //   std::vector<double> x7 = SORMethod(r2, 1000, 0.75, sol2).first;
  //   std::vector<double> x8 = SORMethod(r3, 1000, 0.75, sol3).first;
  //   std::vector<double> x9 = SORMethod(r4, 1000, 0.75, sol4).first;
  //   std::vector<double> x10 = SORMethod(r5, 1000, 0.75, sol5).first;

  double w1 = findOmega(r1, sol1);
  double w2 = findOmega(r2, sol2);
  double w3 = findOmega(r3, sol3);
  double w4 = findOmega(r4, sol4);
  double w5 = findOmega(r5, sol5);
  std::cout << SORMethod(r1, 1000, w1, sol1).second << std::endl;
  std::cout << SORMethod(r2, 1000, w2, sol2).second << std::endl;
  std::cout << SORMethod(r3, 1000, w3, sol3).second << std::endl;
  std::cout << SORMethod(r4, 1000, w4, sol4).second << std::endl;
  std::cout << SORMethod(r5, 1000, w5, sol5).second << std::endl;

  //   findError(r1, sol1, w1, 1);
  //   findError(r2, sol2, w2, 2);
  //   findError(r3, sol3, w3, 3);
  //   findError(r4, sol4, w4, 4);
  //   findError(r5, sol5, w5, 5);
}