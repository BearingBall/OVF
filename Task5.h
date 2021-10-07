#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include <chrono>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task5
{
private:
    int _n;
    std::vector<double> _x;
    std::vector<double> _y;
public:
    void solve(int n)
    {
        _n = n;
        calculateXY();

        std::vector<double> X;
        std::vector<double> Y;
        std::vector<double> Polinom;
        std::vector<double> Differ;
        for(int i=0;i<400;++i)
        {
            X.push_back(1 + static_cast<double>(i) / 400);
            Y.push_back(log10(X.back()));
            Polinom.push_back(P(X.back()));
            //Differ.push_back(Y.back() - Polinom.back());
            Differ.push_back(log10(abs(Y.back() - Polinom.back())));
        }

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("x", X);
        arr->Add("log", Y);
        arr->Add("P", Polinom);
        gnuDrawer.Add(arr);

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", X);
        arr2->Add("log-P", Differ);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();
    }

private:
    void calculateXY()
    {
        for(int k=0;k<=_n;++k)
        {
            _x.push_back(1.0 + static_cast<double>(k) / _n);
            _y.push_back(log10(_x.back()));
        }
    }

    double P(double x)
    {
        double sum = 0;
        for(int i=0;i<=_n;++i)
        {
            sum += _y[i] * l_i(i, x) / l_i(i, _x[i]);
        }
        return sum;
    }

    std::function<double(int, double)> l_i = [this](int i, double x)
    {
        double sum = 1;
        for(int j = 0;j<=_n;++j)
        {
            if (j!=i)
            {
                sum *= (x - _x[j]);
            }
        }
        return sum;
    };

};