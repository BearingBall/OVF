#pragma once
#include <limits>
#include <algorithm>
#include <math.h>
#include <vector>

class Task1
{
public:
	static void solve()
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
		std::cout << std::setprecision(std::numeric_limits<float>::max_digits10) << "FloatValues:\n" << ValuesFloat[0] << "\n" << ValuesFloat[1] << "\n" << ValuesFloat[2] << "\n" << ValuesFloat[3] << std::endl;
		std::vector<double> ValuesDouble = Task1::GetValues<double>();
		std::cout << std::setprecision(std::numeric_limits<double>::max_digits10) << "DoubleValues:\n" << ValuesDouble[0] << "\n" << ValuesDouble[1] << "\n" << ValuesDouble[2] << "\n" << ValuesDouble[3] << std::endl;
	}
	
	// 1 + e/2  = 1 FirstCondition
	// 1 + e   != 1 SecondCondition
private:
	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static floatingPoint BinarySearch(floatingPoint LeftValue, floatingPoint RightValue, 
		bool(*FirstCondition)(floatingPoint),
		bool(*SecondCondition)(floatingPoint),
		floatingPoint(*MidValue)(floatingPoint, floatingPoint))
	{
		floatingPoint Mid;
		while (true) 
		{
			Mid = MidValue(LeftValue,RightValue);
			if (Mid == RightValue || Mid == LeftValue) { 
				return Mid;             
			}
			if (FirstCondition(Mid))     
				LeftValue = Mid;
			else
			if (SecondCondition(Mid))
				RightValue = Mid;   
		}
		return Mid;
	}
	
public:
	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static floatingPoint GetEpsilonManual()
	{
		return std::numeric_limits<floatingPoint>::epsilon();
	}

	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static floatingPoint GetEpsilonAlgorithmic()
	{
		return BinarySearch<floatingPoint>(static_cast<floatingPoint>(0), static_cast<floatingPoint>(3),
			[](floatingPoint e) { return 1 + e / 2 == 1; },
			[](floatingPoint e) { return 1 + e != 1; },
			[](floatingPoint a, floatingPoint b) { return (a + b) / 2; });
	}

	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static int GetDecimalMantissaNumber()
	{
		int TargetDecimal = 1;
		while(true)
		{
			if (static_cast<floatingPoint>(1) + static_cast<floatingPoint>(std::pow(2, -1 * TargetDecimal)) == static_cast<floatingPoint>(1))
				return TargetDecimal;
			TargetDecimal++;
		}
	}

	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static int GetMinPow()
	{
		int TargetPow = -1;
		floatingPoint prevValue = 1;
		while (true)
		{
			if (static_cast<floatingPoint>(std::pow(10, TargetPow)) >= prevValue)
				return TargetPow+2;
			prevValue = static_cast<floatingPoint>(std::pow(10, TargetPow));
			TargetPow--;
		}
	}
	
	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static int GetMaxPow()
	{
		int TargetPow = 1;
		floatingPoint prevValue = 0;
		while (true)
		{
			if (static_cast<floatingPoint>(std::pow(10, TargetPow))  <= prevValue)
				return TargetPow - 2;
			prevValue = static_cast<floatingPoint>(std::pow(10, TargetPow));
			TargetPow++;
		}
	}

	//1, 1+e/2, 1+e, 1+e+e/2
	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static std::vector<floatingPoint> GetValues()
	{
		floatingPoint e = GetEpsilonManual<floatingPoint>();
		return {
			static_cast<floatingPoint>(1),
			static_cast<floatingPoint>(1) + e / 2,
			static_cast<floatingPoint>(1) + e,
			(static_cast<floatingPoint>(1) + e/2) + e };
	}
};

