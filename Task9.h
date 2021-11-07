#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task9
{
private:
    // y'' + P(x) * y' + Q(x) * y = R(x)
    std::function<double(double)> P = [](double x) { return 0; };
    std::function<double(double)> Q = [](double x) { return 0; };
    std::function<double(double)> R = [](double x) { return sin(x); };
    double A = 0;
    double B = M_PI;

    int n = 0;
    double h = 0;

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> a;
    std::vector<double> b;
    std::vector<double> c;
    std::vector<double> d;

    std::vector<double> epsilon;
    std::vector<double> tetta;

    void Calculate(int _n, double ct1, double ct2, double ct, double dt1, double dt2, double dt)
    {
        n = _n;
        h = (B - A) / n;

        x.resize(n+1);
        y.resize(n+1);
        a.resize(n+1);
        b.resize(n+1);
        c.resize(n+1);
        d.resize(n+1);

        for(int i=0; i<=n;++i)
        {
            x[i] = A + i * h;
            a[i] = 1 / (h * h) - P(x[i]) / (2 * h);
            b[i] = 2 / (h * h) - Q(x[i]);
            c[i] = 1 / (h * h) + P(x[i]) / (2 * h);
            d[i] = R(x[i]);
        }

        epsilon.resize(n+1);
        tetta.resize(n+1);

        epsilon[1] = -ct2 / (ct1 * h - ct2);
        tetta[1] = ct * h / (ct1 * h - ct2);

        for(int k = 1; k < n; ++k)
        {
            epsilon[k + 1] = c[k] / (b[k] - a[k] * epsilon[k]);
            tetta[k + 1] = (tetta[k] * a[k] - d[k]) / (b[k] - a[k] * epsilon[k]);
        }

        y[n] = (dt2 * tetta[n] - dt * h) / (dt2 * (1 - epsilon[n]) + dt1 * h);

        for(int j = n; j>0; --j)
        {
            y[j - 1] = y[j] * epsilon[j] + tetta[j];
        }
    }

public:

    void solve()
    {
        // 1,0,0,1,0,0
        //1, 0, 1, 1, 0, -1
        Calculate(100, 1, 0, 0, 1, 0, 0);

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("x", x);
        arr->Add("y", y);
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        std::vector<double> mis;
        mis.resize(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            mis[i] = sin(x[i])+y[i];
        }


        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", x);
        arr2->Add("y", mis);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();
    }

};