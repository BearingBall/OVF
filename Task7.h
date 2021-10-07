#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task7
{
private:
    double a = 10;
    double b = 2;
    double c = 2;
    double d = 10;

    std::function<double(double, double)> x_point = 
        [this](double x, double y) { return a*x-b*x*y; };
    std::function<double(double, double)> y_point =
        [this](double x, double y) { return c * x * y - d * y; };

    std::vector<double> t;

public:

    void solve(double x0, double y0, double delta)
    {
        setT(0, 1, delta);

        std::vector<double> x;
        std::vector<double> y;
        x.push_back(x0);
        y.push_back(y0);
        for (unsigned int i = 1; i < t.size(); ++i)
        {
            x.push_back(x[i - 1] + delta *
                x_point(x[i - 1] + delta / 2 * x_point(x[i - 1], y[i - 1]), y[i - 1] + delta / 2));

            y.push_back(y[i-1] + delta * 
                y_point(x[i-1]+delta/2, y[i - 1] + delta / 2 * y_point(x[i-1],y[i-1])));
        }

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("t", t);
        arr->Add("x", x);
        arr->Add("y", y);
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", x);
        arr2->Add("y", y);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();
    }

    void setT(double from, double to, double delta)
    {
        t.clear();
        double value = from;
        while (value <= to)
        {
            t.push_back(value);
            value += delta;
        }
    }
};