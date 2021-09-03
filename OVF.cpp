#include <iostream>
#include <iomanip>
#include "Task1.h"

int main()
{
	std::cout << Task1::GetEpsilonManual<float>() << " Manual float value" << std::endl;
	std::cout << Task1::GetEpsilonAlgorithmic<float>() << " Algorithmic float value" << std::endl;
	std::cout << Task1::GetEpsilonManual<double>() << " Manual double value" << std::endl;
	std::cout << Task1::GetEpsilonAlgorithmic<double>() << " Algorithmic double value" << std::endl;
	std::cout << Task1::GetDecimalMantissaNumber<float>() << " Decimal Mantissa Number float" << std::endl;
	std::cout << Task1::GetDecimalMantissaNumber<double>() << " Decimal Mantissa Number double" << std::endl;
	std::cout << Task1::GetMinPow<float>() << " Min power float" << std::endl;
	std::cout << Task1::GetMinPow<double>() << " Min power double" << std::endl;
	std::cout << Task1::GetMaxPow<float>() << " Max power float" << std::endl;
	std::cout << Task1::GetMaxPow<double>() << " Max power double" << std::endl;

	std::vector<float> ValuesFloat = Task1::GetValues<float>();
	std::cout << std::setprecision(std::numeric_limits<float>::max_digits10) << "FloatValues:\n" << ValuesFloat[0] << "\n" << ValuesFloat[1] << "\n" << ValuesFloat[2] << "\n" << ValuesFloat[3] <<  std::endl;
	std::vector<double> ValuesDouble = Task1::GetValues<double>();
	std::cout << std::setprecision(std::numeric_limits<double>::max_digits10) << "DoubleValues:\n" << ValuesDouble[0] << "\n" << ValuesDouble[1] << "\n" << ValuesDouble[2] << "\n" << ValuesDouble[3] << std::endl;
}
