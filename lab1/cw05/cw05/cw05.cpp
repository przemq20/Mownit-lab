#include <iostream>
#include <cmath>
#include <math.h>
#include<iomanip>
#define M_E 2.71828182845904523536

void unstable() {
	for (float value = -1.0; value <= 1.0; value += 0.2) {
		std::cout << value << std::endl;
	}
}

void stable() {
	for (int value = -10; value <= 10; value += 2) {
		std::cout << (float)value/10 << std::endl;
	}
}

int main() {
	unstable();
	stable();
}
