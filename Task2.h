#pragma once
#include <limits>
#include <algorithm>
#include <math.h>
#include <vector>
#include <functional>
#include <thread>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

std::pair<std::vector<double>, std::vector<double>> dihotom(double left, double right, std::function<double(double)> func);
std::vector<double> newton(double start, std::function<double(double)> func);
std::vector<double> iteration(double start, std::function<double(double)> func);


class Task2
{
public:
	void solve()
	{
		std::cout << "asimptote = " << asimptote(1) << std::endl;
		drawFunc(0.01, 0.99, 0.0001);
		drawDihotom(asimptote(1), 1);
		drawNewton((asimptote(1)+1.0)/2);
		drawIteration((asimptote(1) + 1.0) / 2);
		
	}

	void drawIteration(double start)
	{
		GNUDrawer gnuDrawer;

		auto history = iteration(start, [this](double a) { return this->function(a); });

		std::cout << "iter x= " << history.back() << " f(x) = " << function(history.back())<< std::endl;
		
		auto range = Generator::GenerateRange(0, history.size() - 1, 1);
		auto arr = Arrays::Construct();
		arr->Add("x", range);
		arr->Add("iter", history);
		gnuDrawer.Add(arr);
		gnuDrawer.Draw();
	}
	
	
	void drawNewton(double start)
	{
		GNUDrawer gnuDrawer;

		auto history = newton(start, [this](double a) { return this->function(a); });


		std::cout << "newton x= " << history.back() << " f(x) = " << function(history.back()) << std::endl;
		
		auto range = Generator::GenerateRange(0, history.size() - 1, 1);
		auto arr = Arrays::Construct();
		arr->Add("x", range);
		arr->Add("newton", history);
		gnuDrawer.Add(arr);
		gnuDrawer.Draw();
	}
	
	void drawDihotom(double left, double right)
	{
		GNUDrawer gnuDrawer;
		
		auto history = dihotom(left, right, [this](double a) { return this->function(a); });


		std::cout << "dihotom x= " << history.first.back() << " f(x) = " << function(history.first.back()) << std::endl;
		
		auto range = Generator::GenerateRange(0, history.first.size() - 1, 1);
		auto arr = Arrays::Construct();
		arr->Add("x", range);
		arr->Add("Left", history.first);
		arr->Add("right", history.second);
		gnuDrawer.Add(arr);
		gnuDrawer.Draw();
	}
	
	void drawFunc(double left, double right, double step)
	{
		GNUDrawer gnuDrawer;

		auto range = Generator::GenerateRange(left, right, step);
		auto funcValues = Generator::GenerateArray([this](double a) { return this->function(a); }, range);
		auto arr = Arrays::Construct();
		arr->Add("x", range);
		arr->Add("function", funcValues);
		gnuDrawer.Add(arr);
		gnuDrawer.Draw();
	}
	
	Task2(double _u, double _a) : u(_u), a(_a)
	{
		
	}

	double function(double epsilon) //return = f(x)
	{
		//double epsilon = -E / u;
		return 1.0 / (tan(sqrt(2.0 * a*a*u*(1.0 - epsilon)))) - sqrt(1.0 / epsilon - 1.0);
	}

	double asimptote(int number)
	{
		double point = -1.0 * ( 3.1415 * static_cast<double>(number)*3.1415 * static_cast<double>(number) / (2.0 * a * a * u) - 1.0);
		return point > 0 ? point : 0;
	}
	
private:
	double u; //U0
	double a; //a
};

std::pair<std::vector<double>,std::vector<double>> dihotom(double left, double right, std::function<double(double)> func)
{
	double mid;
	std::vector<double> left_history;
	std::vector<double> right_history;
	left_history.emplace_back(left);
	right_history.emplace_back(right);
	int counter = 0;
	while(right - left > 0.00001 )
	{
		mid = (left + right) / 2;
		if (func(mid) > 0)
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
		left_history.emplace_back(left);
		right_history.emplace_back(right);
		if (counter == 1000)
		{
			break;
		}
		counter++;
	}
	return {left_history, right_history};
}

std::vector<double> newton(double start, std::function<double(double)> func)
{
	std::vector<double> history;
	double res = 0.000001;

	history.push_back(start);
	while(true)
	{
		if (abs(func(start)) > res)
		{
			//d/dt
			start = start - func(start)*res / (func(start + res) - func(start));
			history.push_back(start);
		}
		else
		{
			break;
		}
		
	}
	return history;
}

std::vector<double> iteration(double start, std::function<double(double)> func)
{
	std::vector<double> history;
	double res = 0.000001;
	double a = start;
	double b = start;
	history.push_back(start);
	while (true)
	{
		if (abs(a+func(a)/(-1000)-b) > res)
		{
			b = a+func(a) / (-1000);
			a = b;
			history.push_back(a);
		}
		else
		{
			break;
		}

	}
	return history;
}