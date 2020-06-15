#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "MonteCarlo.h"
#include "integration.h"

double f1(double x) {
  return (3 * pow(log(x), 2)) / x;
}
const double f1x0 = 1;
const double f1x1 = M_E;
const double res1 = 1;

double f2(double x) {
  return sin(x) + cos(x);
}

const double f2x0 = 0;
const double f2x1 = M_PI;
const double res2 = 2;

double f3(double x) {
  return cos(x) * pow(M_E, x);
}

const double f3x0 = 0;
const double f3x1 = M_PI / 2;
const double res3 = (pow(M_E, M_PI / 2) - 1) / 2;

int main() {
  // integration

  // std::fstream plik;
  // plik.open("integration3.txt", std::ios::out | std::ios::app);
  // for (int i = 1; i < 100; i++) {
  //   setCount(i);
  //   plik << i << ":" << std::abs(res3 - rectangle(f3, f3x0, f3x1)) << ":"
  //        << std::abs(res3 - trapezoidal(f3, f3x0, f3x1)) << ":"
  //        << std::abs(res3 - simpson(f3, f3x0, f3x1)) << std::endl;
  // }
  // plik.close();

  // pi using Monte Carlo

  // std::fstream plik;
  // plik.open("pi.txt", std::ios::out | std::ios::app);
  // for (long long i = 100; i < 100000; i += 100) {
  //   plik << std::setprecision(7) << i << ":" << monteCarlo(i) << std::endl;
  // }
  // plik.close();
  // for (int i = 0; i < 3; i++) {
  //   std::cout << std::setprecision(10) << monteCarlo(10000000000) <<
  //   std::endl;
  // }

  // Monte Carlo Integration

  // std::fstream plik;
  // plik.open("integration4.txt", std::ios::out | std::ios::app);
  // for (int i = 1; i < 100; i++) {
  //   plik << i << ":" << std::abs(res1 - integrationMC(f1, f1x0, f1x1, i)) <<
  //   ":"
  //        << std::abs(res2 - integrationMC(f2, f2x0, f2x1, i)) << ":"
  //        << std::abs(res3 - integrationMC(f3, f3x0, f3x1, i)) << std::endl;
  // }
  // plik.close();
  for (int i = 0; i < 3; i++) {
    std::cout << std::setprecision(10)
              << std::abs(res1 - integrationMC(f1, f1x0, f1x1, 100000000))
              << std::endl;
  }
  for (int i = 0; i < 3; i++) {
    std::cout << std::setprecision(10)
              << std::abs(res2 - integrationMC(f2, f2x0, f2x1, 100000000))
              << std::endl;
  }
  for (int i = 0; i < 3; i++) {
    std::cout << std::setprecision(10)
              << std::abs(res3 - integrationMC(f3, f3x0, f3x1, 100000000))
              << std::endl;
  }
}