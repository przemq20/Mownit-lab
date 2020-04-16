#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string> 

class Point {
private:
	double x;
	double y;
public:
	Point() {};
	Point(double x1, double y1) : x(x1), y(y1) {}
	double getX() const { return x; }
	double getY() const { return y; }
	void setX(double newX) { x = newX; }
	void setY(double newY) { y = newY; }
};

double f1(double x) {
	return sin((10 * x) / M_PI) * pow(M_E, (-x) / M_PI);
}

double f1der(double x) {
	return (pow(M_E, (-x) / M_PI) * (10 * cos(10 * x / M_PI) - sin(10 * x / M_PI))) / M_PI;
}


std::string boolToString(bool c) {
	if (c == 1) {
		return "true";
	}
	return "false";
}


double hermiteInterpolation(double x, double x0, double x1, int k, bool chebyshew) {
	std::fstream plik;
	plik.open("wezly" + std::to_string(k) + boolToString(chebyshew) + ".txt", std::ios::out | std::ios::app);
	std::vector<double> nodes;
	if (!chebyshew) {
		for (int i = 0; i < k; i++) {
			nodes.push_back(x0 + i * (x1 - x0) / ((double)k - 1));
		}
	}
	else {
		for (int i = 1; i <= k; i++) {
			nodes.push_back((M_PI * cos((2 * (double)i - 1) * M_PI / (2 * (double)k))));
		}
	}
	int n = nodes.size();
	std::vector<double> z;
	for (int i = 0; i < n; i++) {
		z.push_back(nodes[i]);
		z.push_back(nodes[i]);
	}
	int n2 = n * 2;
	std::vector<std::vector<double>> matrix;
	matrix.resize(n2);
	for (int i = 0; i < n2; i++) {
		matrix[i].resize(n2, 0.0);
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < i + 1; j++) {
			if (j == 0) {
				matrix[i][j] = f1(z[i]);
			}
			else if (j == 1 && i % 2 == 1) {
				matrix[i][j] = f1der(z[i]);
			}
			else {
				matrix[i][j] = matrix[i][j - 1] - matrix[i - 1][j - 1];
				matrix[i][j] = matrix[i][j] / (z[i] - z[i - j]);
			}
		}
	}
	double result = 0;
	double helper = 1;
	for (int i = 0; i < n2; i++) {
		result = result + matrix[i][i] * helper;
		helper = helper * (x - z[i]);
	}
	return result;
}

double hermiteError(std::vector<double> points, int pointsNumber, bool chebyshew) {
	double error = 0.0;
	for (int i = 0; i < points.size(); i++) {
		error += abs(hermiteInterpolation(points[i], -M_PI, M_PI, pointsNumber, chebyshew) - f1(points[i]));
	}
	return error;
}


int main() {
	int amount = 1000;
	double x0 = -M_PI;
	double x1 = M_PI;
	std::vector<int> numbers;
	for (int i = 0; i <= amount; i++) {
		numbers.push_back(i);
	}
	std::vector<double> points;
	std::vector<double> values;

	for (int i = 0; i <= amount; i++) {
		points.push_back((x0 + i * (x1 - x0) / amount));
		values.push_back(f1(points[i]));
	}

	std::fstream plik;
	plik.open("errors.txt", std::ios::out | std::ios::app);
	for (int i = 2; i < 51; i++) {
		plik << i << "	" << hermiteError(points, i, 0)<<"	" << hermiteError(points, i, 1)<<std::endl;
	}

}


