#define _USE_MATH_DEFINES
#include <iostream> 
#include <cmath>
#include "Lorenz.h"

double func(double x, double y) {
	return (4 * sin(x) * cos(x) + 2 * y * sin(x));
}

void euler(int iterations) {
	double x0, y;
	x0 = 0;
	y = pow(M_E, -2) - 1;
	double step = (double)2.0 / (double)iterations;
	std::ofstream myfile;
	myfile.open("euler2.txt");
	for (int i = 0; i < iterations; i++) {
		y = y + step * func(x0, y);
		x0 = x0 + step;
		myfile << x0 << std::endl;
		myfile << y << std::endl;
	}
	myfile.close();
}


void rungeKutta(int iterations) {
	double x0, y;
	x0 = 0;
	y = pow(M_E, -2) - 1;
	double step = (double)2.0 / (double)iterations;
	std::ofstream myfile;
	myfile.open("rungekutta2.txt");
	for (int i = 0; i < iterations; i++) {
		double k1 = step * func(x0, y);
		y = y + step * func(x0+step/2, y+k1/2);
		x0 = x0 + step;
		myfile << x0 << std::endl;
		myfile << y << std::endl;
	}
	myfile.close();
}

int main()
{
	Lorenz lorenz(1000);
	//lorenz.euler();
	//lorenz.backwardEuler();
	//lorenz.rungeKutta();
	//lorenz.rk4();
	euler(5);
	rungeKutta(5);
}

