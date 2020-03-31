#define _USE_MATH_DEFINES
#define EPSILON 10e-6

#include <cmath>
#include <iostream>
#include <iomanip> 

struct solution {
	double result;
	double iterations;
};

double f1_x0 = (3.0 / 2.0) * M_PI;
double f1_x1 = 2.0 * M_PI;

double f1(double x) {
	return cos(x) * cosh(x) - 1;
}

double f2_x0 = 0.0;
double f2_x1 = M_PI_2;

double f2(double x) {
	return (1 / x) - tan(x);
}

double f3_x0 = 1.0;
double f3_x1 = 3.0;

double f3(double x) {
	return pow(2, -x) + pow(M_E, x) + 2 * cos(x) - 6;
}

solution bisection(double p, double q, double (fun)(double), double precision) {
	if (fun(p) * fun(q) >= 0) {
		throw std::invalid_argument("Wrong interval");
	}
	int iterations = 0;
	double m = p;
	while ((q - p) >= precision) {
		m = (p + q) / 2;

		if (fun(m) == 0.0) {
			break;
		}

		else if (fun(m) * fun(p) < 0) {
			q = m;
		}
		else {
			p = m;
		}
		iterations++;
	}
	solution s;
	s.result = m;
	s.iterations = iterations;
	return s;
}

double derivFunc(double fun(double), double x)
{
	if (fun == f1) {
		return cos(x) * sinh(x) - sin(x) * cosh(x);
	}
	else if (fun == f2) {
		return ((-(1 / (x * x))) - (1 / cos(x)) * (1 / cos(x)));
	}
	else if (fun == f3) {
		return pow(M_E, x) - pow(2, -x) * log(2) - 2 * sin(x);
	}
	throw std::invalid_argument("Wrong interval");
}

solution newtonMethod(double x, double fun(double), double epsilon, int maxiterations)
{
	double h = fun(x) / derivFunc(fun, x);
	double oldX = x;
	int iterations = 0;
	do
	{
		oldX = x;
		x = x - fun(x) / derivFunc(fun, x);
		iterations++;
	} while (abs(x - oldX) >= epsilon && iterations < maxiterations);

	solution s;
	s.result = x;
	s.iterations = iterations;
	return s;
}

solution secantMethod(double x1, double x2, double fun(double), double precision, int maxiterations) {
	if (fun(x1) * fun(x2) > 0.0f)
	{
		throw std::invalid_argument("Wrong interval");
	}

	double x = x1;
	double xn1 = x1;
	double xn = x2;
	int iterations = 0;
	double oldX;
	do {
		oldX = x;
		x = xn - ((fun(xn) * (xn - xn1)) / (fun(xn) - fun(xn1)));
		xn1 = xn;
		xn = x;
		iterations++;
	} while (abs(x - oldX) > precision&& iterations < maxiterations);
	solution s;
	s.iterations = iterations;
	s.result = x;
	return s;
}

int main() {
	std::cout.precision(7);

	std::cout << newtonMethod(f1_x1, f1, 10e-15, 1000).iterations << std::endl;
	std::cout << newtonMethod(f2_x0+10e-6, f2, 10e-15, 1000).result << std::endl;
	std::cout << newtonMethod(f3_x1, f3, 10e-15, 1000).iterations << std::endl;
}
