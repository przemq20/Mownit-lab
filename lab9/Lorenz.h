#pragma once
#include <fstream>
class Lorenz {
public:
	double sigma;
	double rho;
	double beta;
	double x;
	double y;
	double z;
	int IterationCount;
public:
	Lorenz(int iterationCount, double sigma = 10, double rho = 28, double beta = 8 / 3, double x = 0.1, double y = 0, double z = 0) {
		this->IterationCount = iterationCount;
		this->beta = beta;
		this->sigma = sigma;
		this->rho = rho;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void euler() {
		double step = 0.01;
		std::ofstream myfile;
		myfile.open("euler.txt");
		for (int i = 0; i < this->IterationCount; i++) {
			double xt = x + step * this->sigma * (y - x);
			double yt = y + step * (x * (this->rho - z) - y);
			double zt = z + step * (x * y - this->beta * z);
			x = xt;
			y = yt;
			z = zt;
			myfile << x <<  std::endl;
			myfile << y <<  std::endl;
			myfile << z <<  std::endl;
		}
		myfile.close();
	}

	void backwardEuler() {
		double step = 0.01;
		std::ofstream myfile;
		myfile.open("backwardEuler.txt");
		for (int i = 0; i < this->IterationCount; i++) {
			double xt = x + step * this->sigma * (y - x);
			double yt = y + step * (xt * (this->rho - z) - y);
			double zt = z + step * (xt * yt - this->beta * z);
			x = xt;
			y = yt;
			z = zt;
			myfile << x << std::endl;
			myfile << y << std::endl;
			myfile << z << std::endl;
		}
		myfile.close();
	}

	void rungeKutta() {
		double step = 0.01;
		std::ofstream myfile;
		system("rm rungekutta.txt");
		myfile.open("rungekutta.txt");
		x = 1;
		y = 1;
		z = 1;
		for (int i = 1; i < this->IterationCount + 1; i++) {
			double k1 = sigma * (y - x);
			double l1 = x * rho - x * z - y;
			double m1 = x * y - beta * z;

			double k2 = sigma * ((y + (0.5 * l1 * step)) - (x + 0.5 * k1 * step));
			double l2 = (x + 0.5 * k1 * step) * rho - (x + 0.5 * k1 * step) * (z + (0.5 * m1 * step)) - (y + (0.5 * l1 * step));
			double m2 = (x + 0.5 * k1 * step) * (y + (0.5 * l1 * step)) - beta * (z + (0.5 * m1 * step));

			x = x + step * k2;
			y = y + step * l2;
			z = z + step * m2;

			myfile << x << std::endl;
			myfile << y << std::endl;
			myfile << z << std::endl;
		}
		myfile.close();
	}

	void rk4() {
		double step = 0.01;
		std::ofstream myfile;
		myfile.open("rk4.txt");
		x = 1;
		y = 1;
		z = 1;
		for (int i = 1; i < this->IterationCount+1; i++) {
			double k1 = sigma * (y - x);
			double l1 = x * rho - x*z - y;
			double m1 = x*y - beta * z;

			double k2 = sigma * ((y + (0.5 * l1 * step)) - (x + 0.5 * k1 * step));
			double l2 = (x + 0.5 * k1 * step) * rho - (x + 0.5 * k1 * step) * (z + (0.5 * m1 * step)) - (y + (0.5 * l1 * step));
			double m2 = (x + 0.5 * k1 * step) * (y + (0.5 * l1 * step)) - beta * (z + (0.5 * m1 * step));

			double k3 = sigma * ((y + (0.5 * l1 * step)) - (x + 0.5 * k1 * step));
			double l3 = (x + 0.5 * k1 * step) * rho - (x + 0.5 * k1 * step) * (z + (0.5 * m1 * step)) - (y + (0.5 * l1 * step));
			double m3 = (x + 0.5 * k1 * step) * (y + (0.5 * l1 * step)) - beta * (z + (0.5 * m1 * step));

			double k4 = sigma * ((y + l3 * step) - (x + k3 * step));
			double l4 = (x + k3 * step) * rho - (x + k3 * step) * (z + m3 * step) - (y + l3 * step);
			double m4 = (x + k3 * step) * (y + l3 * step) - beta * (z + m3 * step);

			x = x + step * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
			y = y + step * (l1 + 2 * l2 + 2 * l3 + l4) / 6;
			z = z + step * (m1 + 2 * m2 + 2 * m3 + m4) / 6;

			myfile << x << std::endl;
			myfile << y << std::endl;
			myfile << z << std::endl;
		}
		myfile.close();
	}
};

