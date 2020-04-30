#define _USE_MATH_DEFINES
#include <iostream>
#include<cmath>
#include<string>
#include<vector>
#include"NumCpp.hpp"
#include <fstream>

double f1(double x) {
	return x * x - cos(3 * M_PI * x);
}

double f2(double x) {
	return pow(M_E, cos(4 * x));
}

std::vector<double> equadistant(double x0, double x1, int n) {
	std::vector<double>result;
	for (int i = 0; i < n; i++) {
		result.push_back(x0 + i * (x1 - x0) / ((double)n - 1));
	}
	return result;
}

nc::NdArray<double> regress(double f(double x), std::vector<double> nodes, int degree) {
	int n = nodes.size();
	nc::NdArray<double> values = nc::zeros<double>(n, 1);
	for (int i = 0; i < n; i++) {
		values[i] = f(nodes[i]);
	}
	nc::NdArray<double> matrix = nc::zeros<double>(n, degree + 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < degree + 1; j++) {
			matrix(i, j) += pow(nodes[i], j);
		}
	}

	return nc::linalg::inv(nc::transpose(matrix).dot(matrix)).dot(nc::transpose(matrix)).dot(values);
}

double poly(nc::NdArray<double> vec, double x) {
	double result = 0;
	for (int i = 0; i < vec.size(); i++) {
		result += vec[i] * pow(x, i);
	}
	return result;
}

double error(std::vector<double> x, std::vector<double> y) {
	double error = 0;
	for (int i = 0; i < x.size(); i++) {
		error += ((x[i] - y[i]) * (x[i] - y[i]));
	}
	error = error / x.size();
	return sqrt(error);
}

double approximate(int degree, std::vector <double> nodes, std::vector <double> yNodes, double f(double x), double x) {
	int n = yNodes.size();

	double a0 = 0.0;
	for (int i = 0; i < n; i++) {
		a0 += yNodes[i];
	}
	a0 /= n;

	std::vector <double> a_coefficients;
	std::vector <double> b_coefficients;
	double t = 2 * M_PI / (n - 1);
	for (int j = 1; j < degree + 1; j++) {
		double a = 0.0;
		double b = 0.0;

		for (int i = 0; i < n; i++) {
			a += yNodes[i] * cos(t * (double)j * (double)i);
			b += yNodes[i] * sin(t * (double)j * (double)i);
		}
		a = a * (2 / (double)n);
		b = b * (2 / (double)n);

		a_coefficients.push_back(a);
		b_coefficients.push_back(b);
	}
	double length = 4.0;
	double mapping_a = 2 * M_PI / length;
	double mapping_b = 0;

	x = mapping_a * x + M_PI;
	double result = a0;
	for (int k = 0; k < a_coefficients.size(); k++) {
		result += a_coefficients[k] * cos((k + 1) * x) + b_coefficients[k] * sin((k + 1) * x);
	}
	return result;
}

int main() {
	int num[] = { 3,5,8,10,15,20,25,50,100,200 };
	for (int n : num) {
		int degrees[] = { 2,3,4,5,8,10,12,15,20 };
		for (int degree : degrees) {

			if (n <= degree) {
				continue;
			}
			std::string name = std::to_string(n) + " " + std::to_string(degree) + ".txt";
			int amount = 1000;
			double x0 = -2;
			double x1 = 2;

			std::vector<double> points = equadistant(x0, x1, 1000);

			std::vector<double> values1;
			std::vector<double> values2;
			for (int i = 0; i < amount; i++) {
				values1.push_back(f1(points[i]));
				values2.push_back(f2(points[i]));
			}
			std::vector<double> nodes = equadistant(x0, x1, n);
			std::fstream plik;
			plik.open(std::to_string(n) + "_" + std::to_string(degree) + "wezlytrig.txt", std::ios::out | std::ios::app);
			for (int i = 0; i < nodes.size(); i++) {
				plik << nodes[i] << " " << f1(nodes[i]) << " " << f2(nodes[i]) << std::endl;
			}
			plik.close();
			std::vector<double> ynodes1;
			std::vector<double> ynodes2;
			for (int i = 0; i < nodes.size(); i++) {
				ynodes1.push_back(f1(nodes[i]));
				ynodes2.push_back(f2(nodes[i]));
			}

			std::vector<double> regressed1;
			std::vector<double> regressed2;
			for (int i = 0; i < amount; i++) {
				//regressed1.push_back(poly(regress(f1, nodes, degree), points[i]));
				//regressed2.push_back(poly(regress(f2, nodes, degree), points[i]));
				regressed1.push_back(approximate(degree, nodes, ynodes1, f1, points[i]));
				regressed2.push_back(approximate(degree, nodes, ynodes2, f2, points[i]));
			}

			plik.open(std::to_string(n) + "_" + std::to_string(degree) + "trig.txt", std::ios::out | std::ios::app);
			int j = 0;

			for (int i = 0; i < amount; i++) {
				plik << points[i] << ":" << values1[i] << ":" << regressed1[i] << ":" << values2[i] << ":" << regressed2[i] << ":";
				plik << std::endl;
			}
			plik.close();
			plik.open("bledy.txt", std::ios::out | std::ios::app);
			plik << n << ":" << degree << ":" << error(regressed1, values1) << ":" << error(regressed2, values2) << std::endl;
			plik.close();
		}
	}
}