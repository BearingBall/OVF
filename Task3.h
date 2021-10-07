#pragma once
#include <functional>
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Integral
{
public:
	double left;
	double right;
	double value;
	std::function<double(double)> func;
};

class Task3
{
public:	
	const Integral a = { -1,1, 1.5707963267949,[](double x) { return 1.0 / (1.0 + x * x); } };
	const Integral b = { 0,1, 1.2958740087317, [](double x) { return std::pow(x,1.0/3.0) * exp(sin(x)); } };

	void solve()
	{
		draw(a);
		draw(b);
	}


	void draw(Integral integral)
	{
		GNUDrawer gnuDrawer;
    GNUDrawer gnuDrawer2;

		auto arr = Arrays::Construct();
    auto arr2 = Arrays::Construct();
		std::vector<double> trapHistory;
		std::vector<double> simpsoneHistory;
		std::vector<double> realValue;
		std::vector<double> range;
    std::vector<double> lgRange;
		std::vector<double> middleHistory;
		std::vector<double> leftHistory;
		std::vector<double> rightHistory;

    int delta = 15;

		for(int i = 1; i<delta;++i)
		{
			trapHistory.push_back(integrateTrapesoid(integral, std::pow(2, i)));
			simpsoneHistory.push_back(integrateSimpsone(integral, std::pow(2, i)));
			middleHistory.push_back(integrateMiddlePoint(integral, std::pow(2, i)));
			leftHistory.push_back(integrateLeftPoint(integral, std::pow(2, i)));
			rightHistory.push_back(integrateRightPoint(integral, std::pow(2, i)));
			realValue.push_back(integral.value);
			range.push_back(std::pow(2, i));
      lgRange.push_back(i);
		}
		arr->Add("x", range);
		arr->Add("Trap", trapHistory);
		arr->Add("Simp", simpsoneHistory);
		arr->Add("real", realValue);
		arr->Add("Middle", middleHistory);
		arr->Add("Left", leftHistory);
		arr->Add("Right", rightHistory);
		gnuDrawer.Add(arr);
		gnuDrawer.Draw();

    std::vector<double> trapMiss;
    std::vector<double> simpsoneMiss;
    std::vector<double> middleMiss;
    std::vector<double> leftMiss;
    std::vector<double> rightMiss;
    std::vector<double> pokazat;
    std::vector<double> pokazat2;

    for(int i = 0; i<delta-2;++i)
    {
        trapMiss.push_back( std::log(abs(trapHistory[i] - trapHistory[i + 1])));
        simpsoneMiss.push_back(std::log(abs(simpsoneHistory[i] - simpsoneHistory[i + 1])));
        middleMiss.push_back(std::log(abs(middleHistory[i] - middleHistory[i + 1])));
        leftMiss.push_back(std::log(abs(leftHistory[i] - leftHistory[i + 1])));
        rightMiss.push_back(std::log(abs(rightHistory[i] - rightHistory[i + 1])));
        pokazat.push_back(std::log(0.05 * 1 / ((i+1)*(i+1))));
        pokazat2.push_back(std::log(0.01 / ((i + 1)*(i + 1)*(i + 1)*(i + 1))));
    }

    lgRange.pop_back();

    arr2->Add("lg(2,x)", lgRange);
    arr2->Add("trapMiss", trapMiss);
    arr2->Add("simpsoneMiss", simpsoneMiss);
    arr2->Add("middleMiss", middleMiss);
    arr2->Add("leftMiss", leftMiss);
    arr2->Add("rightMiss", rightMiss);
    arr2->Add("1/N^2", pokazat);
    arr2->Add("1/N^4", pokazat2);
    gnuDrawer2.Add(arr2);
    gnuDrawer2.Draw();
	}
	
private:
	
	double integrateTrapesoid(Integral integral, unsigned int derNumber)
	{
		double sum = 0;
		for(unsigned int i=0;i<derNumber;++i)
		{
			double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
			double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i+1);
			sum += (integral.func(left) + integral.func(right)) / 2.0 * (right - left);
		}
		return sum;
	}
	
	double integrateSimpsone(Integral integral, unsigned int derNumber)
	{
		double sum = 0;
		for (unsigned int i = 0; i < derNumber; ++i)
		{
			double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
			double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i + 1);
			sum += (integral.func(left) + 4.0*integral.func((left+right)/2.0) + integral.func(right)) / 6.0 * (right - left);
		}
		return sum;
	}

	double integrateMiddlePoint(Integral integral, unsigned int derNumber)
	{
		double sum = 0;
		for (unsigned int i = 0; i < derNumber; ++i)
		{
			double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
			double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i + 1);
			sum += (integral.func(left) + integral.func(right)) / 2.0 * (right - left);
		}
		return sum;
	}

	double integrateLeftPoint(Integral integral, unsigned int derNumber)
	{
		double sum = 0;
		for (unsigned int i = 0; i < derNumber; ++i)
		{
			double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
			double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i + 1);
			sum += (integral.func(left)) * (right - left);
		}
		return sum;
	}
	
	double integrateRightPoint(Integral integral, unsigned int derNumber)
	{
		double sum = 0;
		for (unsigned int i = 0; i < derNumber; ++i)
		{
			double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
			double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i + 1);
			sum += (integral.func(right))* (right - left);
		}
		return sum;
	}
};