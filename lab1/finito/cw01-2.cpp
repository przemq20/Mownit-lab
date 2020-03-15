#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <fstream>
#include <cmath>
#include <iomanip>


float sum_rec(float tab[], int l, int r) {
	if (l == r) {
		return tab[l];
	}
	if (l < r) {
		int mid = (l + r) / 2;

		return sum_rec(tab, l, mid - 1) + tab[mid] + sum_rec(tab, mid + 1, r);
	}
	return 0;
}


float KahanSum(float tab[], int quantity) {
	float sum = 0.0f;
	float err = 0.0f;
	for (int i = 0; i < quantity; i++) {
		float y = tab[i] - err;
		float temp = sum + y;
		err = (temp - sum) - y;
		sum = temp;
	}
	return (float)sum;
}


int main()
{
	const auto value = 0.1f;
	const auto quantity = 10000000;
	float* tab = new float[quantity];
	auto sum = 0.0f;

	for (int i = 0; i < quantity; i++) {
		tab[i] = value;
	}

	int normclock1 = clock();
	for (int i = 0; i < quantity; i++) {
		sum += tab[i];
	}
	int normclock2 = clock() - normclock1;

	float predicted = value * (float)quantity;
	std::cout << "Zadanie 1:" << std::endl;
	std::cout << "	Zliczanie tablicy suma:" << sum << std::endl;

	float bezwgl = abs(predicted - sum);
	std::cout << "	Zliczanie tablicy blad bezwzgledny: " << bezwgl << std::endl;

	float wzgl = (bezwgl / predicted) * 100;
	std::cout << "	Zliczanie tablicy blad wzgledny: " << wzgl << " %" << std::endl;
	std::cout << "	Zliczanie tablicy czas dzialania: " << (float)normclock2 / CLOCKS_PER_SEC << std::endl;

	std::fstream plik;
	plik.open("results.txt", std::ios::out);
	//zapis co 25000 krokow do pliku
	sum = 0;

	for (int i = 0; i < quantity; i++) {
		sum += tab[i];
		if ((i + 1) % 25000 == 0) {
			float predicted = (i + 1) * value;
			float bezwgl = abs(sum - predicted);
			plik << (bezwgl / predicted) * 100 << std::endl;
		}
	}
	plik.close();

	std::cout << "	==============================" << std::endl;
	int recclock1 = clock();
	float recsum = sum_rec(tab, 0, quantity - 1);
	int recclock2 = clock() - recclock1;

	std::cout << "	Rekursywna suma: " << recsum << std::endl;
	std::cout << "	Rekursywny blad bezwzgledny: " << abs(recsum - predicted) << std::endl;
	std::cout << "	Rekursywny blad wzgledny: " << ((abs(recsum - predicted)) / predicted) * 100 << " %" << std::endl;
	std::cout << "	Rekursywny czas dzialania: " << (float)recclock2 / CLOCKS_PER_SEC << std::endl;


	std::cout << "	==============================" << std::endl;
	int kahanclock1 = clock();
	float kahan = KahanSum(tab, quantity);
	int kahanclock2 = clock() - kahanclock1;

	std::cout << "	Kahan suma: " << kahan << std::endl;
	std::cout << "	Kahan blad bezwzgledny: " << abs(kahan - predicted) << std::endl;
	std::cout << "	Kahan blad wzgledny: " << (abs((kahan - predicted)) / predicted) * 100 << " %" << std::endl;
	std::cout << "	Kahan czas dzialania: " << (float)kahanclock2 / CLOCKS_PER_SEC << std::endl;

}
