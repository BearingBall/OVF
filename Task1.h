#pragma once
#include <limits>
#include <algorithm>
#include <math.h>
#include <vector>

class Task1
{
	// 1 + e/2  = 1 FirstCondition
	// 1 + e   != 1 SecondCondition
private:
	template<typename floatingPoint, typename std::enable_if<std::is_floating_point<floatingPoint>::value, floatingPoint>::type* = nullptr>
	static floatingPoint BinarySearch(floatingPoint LeftValue, floatingPoint RightValue, 
		bool(*FirstCondition)(floatingPoint),
		bool(*SecondCondition)(floatingPoint),
		floatingPoint(*MidValue)(floatingPoint, floatingPoint))
	{
		while (LeftValue <= RightValue) 
		{
			floatingPoint Mid = MidValue(LeftValue,RightValue);
			if (FirstCondition(Mid) && SecondCondition(Mid)) { 
				return Mid;             
			}
			if (FirstCondition(Mid))     
				LeftValue = Mid;  
			else                  
				RightValue = Mid;   
		}
		return LeftValue;
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
		return BinarySearch<floatingPoint>(static_cast<floatingPoint>(0), static_cast<floatingPoint>(1),
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
			if (static_cast<floatingPoint>(1) + static_cast<floatingPoint>(std::pow(10, -1 * TargetDecimal)) == static_cast<floatingPoint>(1))
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
				return TargetPow-2;
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
			static_cast<floatingPoint>(1) + e + e / 2 };
	}
};

