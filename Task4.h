#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include <chrono>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"


class Integral
{
public:
    double left;
    double right;
    std::function<double(double, double)> func;
};

class Task4
{
private:
    const Integral BesselZero = { 0,M_PI, [](double x, double t) { return 1.0 / M_PI * cos(-x*sin(t)); } };
    const Integral BesselFirst = { 0,M_PI, [](double x, double t) { return 1.0 / M_PI * cos(t-x * sin(t)); } };

public:
    void solve(double deltaX, double deltaProisvodX, double deltaT)
    {
        using namespace std::chrono;


        std::vector<double> BesselZeroValues;
        BesselZeroValues.reserve(M_2_PI / deltaX);
        std::vector<double> BesselFirstValues;
        BesselFirstValues.reserve(M_2_PI / deltaX);
        std::vector<double> BesselZeroProisvod;
        BesselZeroProisvod.reserve(M_2_PI / deltaX);
        std::vector<double> MainSum;
        MainSum.reserve(M_2_PI / deltaX);
        std::vector<double> range;
        range.reserve(M_2_PI / deltaX);


        auto start = high_resolution_clock::now();

        for(int currentX=0; currentX*deltaX<M_PI*2; ++currentX)
        {
            BesselZeroValues.push_back(integrateSimpsone(BesselZero, M_PI / deltaT, currentX*deltaX));
            BesselFirstValues.push_back(integrateSimpsone(BesselFirst, M_PI / deltaT, currentX*deltaX));
            range.push_back(currentX*deltaX);

            double F1 = integrateSimpsone(BesselZero, M_PI / deltaT, currentX*deltaX - 2 * deltaProisvodX);
            double F2 = integrateSimpsone(BesselZero, M_PI / deltaT, currentX*deltaX - deltaProisvodX);
            double F3 = integrateSimpsone(BesselZero, M_PI / deltaT, currentX*deltaX + deltaProisvodX);
            double F4 = integrateSimpsone(BesselZero, M_PI / deltaT, currentX*deltaX + 2 * deltaProisvodX);

            BesselZeroProisvod.push_back((F1 - 8 * F2 + 8 * F3 - F4) / (12 * deltaProisvodX));
            MainSum.push_back(BesselZeroProisvod.back() + BesselFirstValues.back());
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        std::cout << duration.count() << std::endl;
        std::cout << std::max_element(MainSum.begin(), MainSum.end())[0] << std::endl;
        std::cout << std::min_element(MainSum.begin(), MainSum.end())[0] << std::endl;

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("x", range);
        arr->Add("J0", BesselZeroValues);
        arr->Add("J1", BesselFirstValues);
        arr->Add("d J0", BesselZeroProisvod);
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", range);
        arr2->Add("sum", MainSum);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();
    }

private:
    double integrateSimpsone(Integral integral, unsigned int derNumber, double X)
    {
        double sum = 0;
        for (unsigned int i = 0; i < derNumber; ++i)
        {
            double left = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i);
            double right = integral.left + static_cast<double>(integral.right - integral.left) / derNumber * static_cast<double>(i + 1);
            sum += (integral.func(X,left) + 4.0*integral.func(X,(left + right) / 2.0) + integral.func(X,right)) / 6.0 * (right - left);
        }
        return sum;
    }
};