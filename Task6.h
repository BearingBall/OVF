#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task6
{
private:
    std::function<double(double)> du_dx = [](double x) { return -x; };
    double from = 0;
    double to = 3;
    double y_left = 1;

    std::vector<double> x_range;
    std::vector<double> y_range;
public:
    void solve()
    {
        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();

        setXRange(0.1);

        arr->Add("x", x_range);
        arr->Add("Euler", EulerSolution(0.1));
        arr->Add("Runge2", RungeSolution(0.1));
        arr->Add("Runge4", RungeSolutionForth(0.1));
        arr->Add("exp(-x)", y_range);
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", x_range);
        arr2->Add("Euler", Error(EulerSolution(0.1)));
        arr2->Add("Runge2", Error(RungeSolution(0.1)));
        arr2->Add("Runge4", Error(RungeSolutionForth(0.1)));
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();

    }

    std::vector<double> Error(std::vector<double> values)
    {
        std::vector<double> error;

        for (unsigned int i = 0; i < x_range.size(); ++i)
        {
            error.push_back(abs(values[i]-y_range[i]));
        }
        return error;
    }


    void setXRange(double delta)
    {
        x_range = std::vector<double>();
        y_range = std::vector<double>();
        double value = from;
        while (value <= to)
        {
            x_range.push_back(value);
            value += delta;
        }

        for (unsigned int i = 0; i < x_range.size(); ++i)
        {
            y_range.push_back(exp(-x_range[i]));
        }
    }

    std::vector<double> EulerSolution(double delta)
    {
        std::vector<double> y;
        y.push_back(y_left);
        for(unsigned int i = 1; i<x_range.size();++i)
        {
            y.push_back(y.back() + delta * du_dx(y.back()));
        }
        return y;
    }

    std::vector<double> RungeSolution(double delta)
    {
        std::vector<double> y;
        y.push_back(y_left);
        for (unsigned int i = 1; i < x_range.size(); ++i)
        {
            y.push_back(y.back() + delta * du_dx(y.back() + delta/2 * du_dx(y.back())));
        }
        return y;
    }

    std::vector<double> RungeSolutionForth(double delta)
    {
        std::vector<double> y;
        y.push_back(y_left);
        for (unsigned int i = 1; i < x_range.size(); ++i)
        {
            double k1 = du_dx(y.back());
            double k2 = du_dx(y.back() + delta/2*k1);
            double k3 = du_dx(y.back() + delta / 2 * k2);
            double k4 = du_dx(y.back() + delta*k3);
            y.push_back(y.back() + delta/6*(k1+2*k2+2*k3+k4));
        }
        return y;
    }
};