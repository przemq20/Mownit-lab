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

std::vector<Point> lagrange(int pointsNumber, int steps, bool chebyshew) {
	std::vector<Point> results;
	std::vector<Point> values;
	//std::string str = "lagrangewezly" + std::to_string(pointsNumber) + boolToString(chebyshew);
	//std::fstream plik;
	//plik.open(str + ".txt", std::ios::out | std::ios::app);
	if (chebyshew) {
		for (int k = pointsNumber - 1; k >= 0; k--) {
			Point p;
			p.setX(M_PI * cos((M_PI * (2 * (double)k + 1)) / (2 * ((double)pointsNumber))));
			p.setY(f1(p.getX()));
			values.push_back(p);
			//plik << p.getX() << " " << p.getY()<<std::endl;
		}
	}
	else {
		double interval = (2 * M_PI) / ((double)(pointsNumber - 1));
		for (int i = 0; i < pointsNumber; i++) {
			Point p;
			p.setX(-M_PI + interval * i);
			p.setY(f1(p.getX()));
			values.push_back(p);
			//plik << p.getX() << " " << p.getY() << std::endl;
		}
	}
	//std::cout << values.size();
	//plik.close();
	double interval = 2 * M_PI / ((double)(steps - 1));
	int n = values.size();
	for (int i = 0; i < steps; i++) {
		Point p;
		p.setX(interval * i - M_PI);
		double result = 0;
		for (int i = 0; i < n; i++) {
			double yi = values[i].getY();
			for (int j = 0; j < n; j++) {
				if (i != j) {
					yi = yi * (p.getX() - values[j].getX()) / (values[i].getX() - values[j].getX());
				}
			}
			result += yi;
		}
		p.setY(result);
		results.push_back(p);
	}
	return results;
}


double lagrangeError(int n, bool chebyshev) {
	std::vector < Point > lag = lagrange(n, 1000, chebyshev);
	double error = 0.0;
	double compartment = 2 * M_PI / 1000;
	double value = -M_PI;
	for (int i = 0; i < 1000; i++) {
		error += std::abs(f1(value - lag[i].getY())); 
		value += compartment;
	}
	return error;
}

void lagrangeWithError(int n,int m, bool c) {
	std::pair<double, std::vector<Point>> s;
	s.first = lagrangeError(n, c);
	//s.second = lagrange(n, m, c);
	std::string str = "lagrange" + std::to_string(n) + boolToString(c);
	std::fstream plik;
	plik.open(str+"ee.txt", std::ios::out | std::ios::app);
	std::cout <<n<<" "<<boolToString(c)<<" "<< s.first << "\n";
	//for (Point result : s.second) {
	//	std::cout << std::fixed;
	//	plik << result.getX() << " " << result.getY() << std::endl;
	//	std::cout << result.getX() << " " << f2(result.getX()) << std::endl;
	//}
}


int main()
{

	//for (int i = 2; i < 30; i++) {
	//	lagrangeWithError(i, 1000, false);
	//	lagrangeWithError(i, 1000, true);
	//}
	std::cout<<lagrangeError(20,  false);
	//std::vector<Point> results = lagrange(50, 1000, true);
}