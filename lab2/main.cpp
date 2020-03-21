#include <time.h>
#include <iostream>
#include "aghMatrix.h"

int main() {
	// initialize matrices using init value
	AGHMatrix<double> mat1(3, 3, 1.2);
	AGHMatrix<double> mat2(3, 3, 2.8);

	// Uncomment when implemented
	AGHMatrix<double> mat3 = mat1 * mat2;
	std::cout << mat3;

	// initialize matrix using specified values
	std::vector<std::vector<double>> init{
		{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
	std::cout << "TO" << std::endl;
	AGHMatrix<double> mat4(init);
	AGHMatrix<double> mat100 = mat4 * mat2;
	std::cout << mat100;
	std::vector<std::vector<double>> Aa{ {2, 1}, {1, 1}, {5, 1} };
	AGHMatrix<double> A(Aa);

	std::vector<std::vector<double>> Bb{ {1, 2, 3}, {2, 3, 1}, {3, 1, 2} };
	AGHMatrix<double> B(Bb);

	std::cout << B.isSymmetrical() << std::endl << std::endl;

	AGHMatrix<double> mat10(2, 2, 1000);

	std::cout << B.determinant() << std::endl;

	std::cout << A.transpose() << std::endl;

	std::vector<std::vector<double>> init_LU{
		{5.0, 3.0, 2.0}, {1.0, 2.0, 0.0}, {3.0, 0.0, 4.0} };

	// Jeśli się korzysta z implementacji laboratoryjnej
	AGHMatrix<double> mat6(init_LU);
	std::cout << mat6.luDecomoposition()[0];
	std::cout << mat6.luDecomoposition()[1];
	std::cout << mat6.luDecomoposition()[0] * mat6.luDecomoposition()[1];
	std::vector<std::vector<double>> init_cholesky{
		{4.0, 12.0, -16.0}, {12.0, 37.0, -43.0}, {-16.0, -43.0, 98.0} };

	//   // Jeśli się korzysta z implementacji laboratoryjnej
	AGHMatrix<double> mat7(init_cholesky);
	std::cout << mat7.choleskyDecomoposition()[0];
	std::cout << mat7.choleskyDecomoposition()[1];

	std::vector<std::vector<double>> Cb{ {2.0, 1.0, 4}, {1, 3, 7} };
	AGHMatrix<double> mat12(Cb);
	std::cout << mat12;

	std::cout << mat12.gaussianElimination() << std::endl;
	std::cout << mat12;
	std::cout << mat12.JacobiMethod()[1] << std::endl;


	return 0;
}