#include <random>

double monteCarlo(long long num) {
  srand(time(NULL));
  long long inside = 0;
  for (long long i = 0; i < num; i++) {
    double x = (double)rand() * 2 / (double)RAND_MAX - 1;
    double y = (double)rand() * 2 / (double)RAND_MAX - 1;
    if (x * x + y * y <= 1) {
      inside += 1;
    }
  }
  return (double)(4.0 * (double)inside) / num;
}

double integrationMC(double f(double x),
                     double x0,
                     double x1,
                     long long count) {
  srand(time(NULL));
  double result = 0;
  for (int i = 0; i < count; i++) {
    double x = (double)rand() * (x1 - x0) / (double)RAND_MAX + x0;
    result += (f(x) * (x1 - x0)) / count;
  }
  return result;
}