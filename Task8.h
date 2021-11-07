#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task8
{
private:
    double a = 998;
    double b = 1998;
    double c = -999;
    double d = -1999;

    std::function<double(double, double)> u_point =
        [this](double u, double v) { return a * u + b * v; };
    std::function<double(double, double)> v_point =
        [this](double u, double v) { return c * u + d * v; };

public:
    double t0 = 0;
    double t1 = 5;

    void solve()
    {
        auto sol1 = Ochevid();
        auto sol2 = neOchevid();

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("t", sol1[0]);
        arr->Add("u_1", sol1[1]);
        arr->Add("v_1", sol1[2]);
        arr->Add("u_2", sol2[1]);
        arr->Add("v_2", sol2[2]);
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("u_1", sol1[1]);
        arr2->Add("v_1", sol1[2]);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();

        GNUDrawer gnuDrawer3;
        auto arr3 = Arrays::Construct();
        arr3->Add("u_2", sol2[1]);
        arr3->Add("v_2", sol2[2]);
        gnuDrawer3.Add(arr3);
        gnuDrawer3.Draw();
    }

    std::vector<std::vector<double>> Ochevid(double u = 0.01, double v = 0.01, double h = 0.0001)
    {
        std::vector<double> u_value;
        std::vector<double> v_value;
        std::vector<double> t_value;

        for (double t = t0; t < t1; t += h)
        {
            t_value.push_back(t);
            u_value.push_back(u);
            v_value.push_back(v);
            u = (u + b * h * v / (1 - d * h)) / (1 - a * h - c * b * h*h / (1 - d * h));
            v = (v + c * h * u) / (1 - d * h);
        }

        return { t_value, u_value, v_value };
    }

    std::vector<std::vector<double>> neOchevid(double u = 0.01, double v = 0.01, double h = 0.0001)
    {
        std::vector<double> u_value;
        std::vector<double> v_value;
        std::vector<double> t_value;

        u_value.push_back(u);
        v_value.push_back(v);

        for (double t = t0; t < t1; t += h)
        {
            t_value.push_back(t);
        }

        for (unsigned int i = 1; i < t_value.size(); ++i)
        {
            u_value.push_back(u_value[i - 1] + h * u_point(u_value[i - 1], v_value[i - 1]));

            v_value.push_back(v_value[i - 1] + h * v_point(u_value[i - 1], v_value[i - 1]));
        }

        return { t_value, u_value, v_value };
    }
};