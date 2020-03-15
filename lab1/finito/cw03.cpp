#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <iomanip>

double KahanSumVector(std::vector<double> tab, int quantity) {
	double sum = 0.0;
	double err = 0.0;
	for (int i = 0; i < quantity; i++) {
		double y = tab[i] - err;
		double temp = sum + y;
		err = (temp - sum) - y;
		sum = temp;
	}
	return (double)sum;
}


float seriesSum(int N) {
	float sum = 0.0;

	for (int k = 1; k <= N; k++) {
		sum += (float)1 / (float)pow(2, k + 1);
	}

	return sum;
}

float seriesSumBack(int N) {
	float sum = 0.0;

	for (int k = N; k >= 1; k--) {
		sum += (float)1 / (float)pow(2, k + 1);
	}

	return sum;
}

double seriesSumDouble(int N) {
	double sum = 0.0;

	for (int k = 1; k <= N; k++) {
		sum += (double)1 / pow(2, k + 1);
	}

	return sum;
}

double seriesSumDoubleBack(int N) {
	double sum = 0.0;

	for (int k = N; k >= 1; k--) {
		sum += (double)1 / pow(2, k + 1);
	}

	return sum;
}

int main()
{
	std::cout << "Zadanie 3:" << std::endl;
	std::cout << "	Pojedyncza precyzja:" << std::endl;

	std::vector<int> n = { 50, 100, 200, 500, 800 };

	std::cout.precision(17);

	for (int i = 0; i < (int)n.size(); i++) {
		std::cout << "		Suma dla n=" << n[i] << " liczona wprzod wynosi: " << seriesSum(n[i]) << std::endl;
	}
	std::cout << "\n";

	for (int i = 0; i < (int)n.size(); i++) {
		std::cout << "		Suma dla n=" << n[i] << " liczona w tyl wynosi: " << seriesSumBack(n[i]) << std::endl;
	}
	std::cout << "	Podwojna precyzja:" << std::endl;

	for (int i = 0; i < (int)n.size(); i++) {
		std::cout << "		Suma dla n=" << n[i] << " liczona wprzod wynosi: " << seriesSumDouble(n[i]) << std::endl;
	}
	std::cout << "\n";

	for (int i = 0; i < (int)n.size(); i++) {
		std::cout << "		Suma dla n=" << n[i] << " liczona w tyl wynosi: " << seriesSumDoubleBack(n[i]) << std::endl;
	}

	std::cout << "	Algorytm Kahana:" << std::endl;

	std::vector<double>seriesValues;

	for (int i = 0; i < (int)n.size(); i++) {
		for (int k = 1; k - 1 <= n[i]; k++) {
			seriesValues.push_back((double)1 / (double)pow(2, k + 1));
		}
		std::cout << "		Suma dla n=" << n[i] << " liczona algorytmem Kahana wynosi: " << KahanSumVector(seriesValues, (int)seriesValues.size()) << std::endl;
		seriesValues.resize(0);
	}
	std::cout << "\n";
}
