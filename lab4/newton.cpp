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

std::string boolToString(bool c) {
	if (c == 1) {
		return "true";
	}
	return "false";
}

std::vector<Point> NewtonInterpolation(int pointsNumber, bool chebyshew) {
	std::vector<Point> results;
	std::vector<Point> values;
	std::string str = "Newtonwezly" + std::to_string(pointsNumber) + boolToString(chebyshew);
	std::fstream plik;
	plik.open(str + ".txt", std::ios::out | std::ios::app);
	if (chebyshew) {
		for (int i = pointsNumber - 1; i >= 0; i--) {
			Point p;
			p.setX(M_PI * cos((M_PI * (2 * (double)i + 1)) / (2 * ((double)pointsNumber))));
			p.setY(f1(p.getX()));
			values.push_back(p);
			plik << p.getX() << " " << p.getY() << std::endl;
		}
	}
	else {
		double interval = 2 * M_PI / (((double)pointsNumber) - 1);
		for (int i = 0; i < pointsNumber; i++) {
			Point p;
			p.setX(-M_PI + interval * i);
			p.setY(f1(p.getX()));
			values.push_back(p);
			plik << p.getX() << " " << p.getY() << std::endl;
		}
	}
	plik.close();
	double interval = 2 * M_PI / (1000);
	for (int i = 0; i < 1001; i++) {
		Point p;
		p.setX(interval * i - M_PI);
		std::vector<std::vector<double>> result;
		std::vector<double> empty_vec;
		empty_vec.resize(pointsNumber, -1.0);
		result.resize(pointsNumber, empty_vec);

		for (int j = 0; j < pointsNumber; j++) {
			result[j][0] = values[j].getY();
		}

		for (int j = 1; j < pointsNumber; j++) {
			for (int k = 0; k < pointsNumber - j; k++) {
				result[k][j] = 0.0;
				result[k][j] = (result[k][j - 1] - result[k + 1][j - 1]) /
					(values[k].getX() - values[j + k].getX());
			}
		}
		double sum = result[0][0];
		for (int j = 1; j < pointsNumber; j++) {
			double result1 = 1;
			for (int k = 0; k < j; k++) {
				result1 = result1 * (p.getX() - values[k].getX());
			}
			sum = sum + (result1 * result[0][j]);
		}
		p.setY(sum);
		results.push_back(p);
	}
	std::fstream plik2;
	std::string name = "Newton" + std::to_string(pointsNumber) + boolToString(chebyshew);
	plik2.open(name + ".txt", std::ios::out | std::ios::app);
	for (Point result : results) {
		plik2 << result.getX() << " " << result.getY() << std::endl;
	}
	plik2.close();
	return results;
}

double newtonError(int n, bool chebyshev) {
	double error = 0.0;
	std::vector<Point> results;
	results = NewtonInterpolation(n, chebyshev);
	for (int i = 0; i < 1001; i++) {
		error += std::abs(f1(i * ((2 * M_PI) / 1000) - M_PI) - results[i].getY());
	}
	return error;
}


int main()
{
	NewtonInterpolation(6, 0);
}