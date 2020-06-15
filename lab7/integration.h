#include <iostream>
#include <vector>
int count = 10;

void setCount(int x) {
  count = x;
}

double rectangle(double f(double x), double x0, double x1) {
  double result = 0;
  double step = (x1 - x0) / count;
  for (int i = 1; i <= count; i++) {
    result += step * f(x0 + i * step);
  }
  return result;
}

double trapezoidal(double f(double x), double x0, double x1) {
  double result = 0;
  double step = (x1 - x0) / count;
  for (int i = 1; i <= count; i++) {
    result += ((f(x0 + (i - 1) * step) + f(x0 + i * step)) * step) / 2;
  }
  return result;
}

double simpson(double f(double x), double x0, double x1) {
  double s = 0;
  double st = 0;
  double h = (x1 - x0) / count;
  double x;
  for (int i = 1; i <= count; i++) {
    st += f(x0 + i * h - h / 2);
    if (i < count) {
      s += f(x0 + i * h);
    }
  }
  s = h / 6 * (f(x0) + f(x1) + 2 * s + 4 * st);
  return s;
}