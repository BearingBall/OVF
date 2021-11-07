#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <complex>
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task12
{
private:
    double a0 = 1;
    double a1 = 0.002;
    double w0 = 5.1;
    double w1 = 25.5;
    double T = M_PI * 2;

    std::function<double(double)> signal =
        [this](double t) { return a0 * sin(w0 * t) + a1 * sin(w1 * t); };

    int N = 100;

    std::function<double(int, int)> hannWindow = [](int k, int N)
    {
        return 0.5 * (1 - cos(2 * M_PI * k / N));
    };

    std::function<double(int,int)> rectangleWindow = [](int k, int N)
    {
        return k >= N / 4 && k < N * 3 / 4 ? 1 : 0;
    };

    std::function<double(int, int)> noWindow = [](int k, int N)
    {
        return 1.0;
    };

    double offset = 0.1;

    std::tuple<std::vector<double>, std::vector<double>> STFT(std::function<double(double)> equation, std::function<double(int, int)> window)
    {
        std::complex<double> i = std::complex<double>(0, 1);
        std::vector<double> spectrum;
        std::vector<double> frequencies;

        double sampling = T / (N - 1);
        double samplingFreq = 1.0 / sampling;

        for (double k = 0; k < N; k += offset)
        {
            std::complex<double> sum = std::complex<double>(0, 0);

            for (int m = 0; m < N; ++m)
            {
                double x = T/2 - (double)m / (N - 1) * T;
                std::complex<double> y = equation(x);

                double angle = 2.0 * M_PI * m * k / (N + 1);
                double w = .5 * (1 - cos(2.0 * M_PI * m / N));

                sum += y * window(m, N) * w * std::exp(-angle * i);
            }

            double frequency = -samplingFreq * 0.5 + (double)k / (N - 1) * samplingFreq;
            spectrum.push_back(log(std::abs(sum)));
            //spectrum.Add(sum.Magnitude);
            frequencies.push_back(frequency);
        }

        return std::tuple<std::vector<double>, std::vector<double>>(frequencies, spectrum);
    }
public:

    void solve()
    {
        auto rect = STFT(signal, rectangleWindow);
        auto no = STFT(signal, noWindow);
        auto han = STFT(signal, hannWindow);


        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("x", std::get<0>(rect));
        arr->Add("rect", std::get<1>(rect));
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("x", std::get<0>(no));
        arr2->Add("no", std::get<1>(no));
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();

        GNUDrawer gnuDrawer3;
        auto arr3 = Arrays::Construct();
        arr3->Add("x", std::get<0>(han));
        arr3->Add("han", std::get<1>(han));
        gnuDrawer3.Add(arr3);
        gnuDrawer3.Draw();
    }

};