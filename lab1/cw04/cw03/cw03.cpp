#include <iostream>

int main() {
	float floatEpsilon = 1.0f;
	double doubleEpsilon = 1.0;

	while (1 + floatEpsilon > 1) {
		floatEpsilon /= 2;
	}
	std::cout << 2 * floatEpsilon << std::endl;

	while (1 + doubleEpsilon > 1) {
		doubleEpsilon /= 2;
	}
	std::cout << 2 * doubleEpsilon << std::endl;

	float a = 1.0f;
	while (a / 2 > 0) {
		a = a / 2;	
	}
	std::cout << a << std::endl;


	return 0;
}