#pragma once
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../GNUDraw/GNUDraw/GNUDrawLib.h"

class Task10
{
private:
    double D = 1;
    double alpha = 0;

    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> values;

    std::function<double(double)> u_start =
        [this](double x) { return x * (1 - x)*(1 - x); };

public:
    void solve(int l_res, int t_res, double max_t)
    {
        alpha = (max_t / t_res * D) / ((1.f / l_res)*(1.f / l_res));
        matrix.resize(l_res);
        for (int i = 0; i < l_res; ++i)
        {
            matrix[i].resize(l_res);
        }

        values.resize(t_res);
        for (int i = 0; i < t_res; ++i)
        {
            values[i].resize(l_res);
        }

        
        for (int i = 0; i < l_res; ++i)
        {
            matrix[i][i] = 2 * (1 + alpha);
            if (i+1 < l_res)
                matrix[i][i+1] = -alpha;
            if (i - 1 >= 0)
                matrix[i][i - 1] = -alpha;
        }
        matrix[0][0] = 1;
        matrix[l_res - 1][l_res - 1] = 1;
        matrix[0][1] = 0;
        matrix[l_res - 1][l_res - 2] = 0;

        std::vector<double> koefs_first(l_res);

        std::vector<double> koefs_second(l_res);

        for (int i = 0; i < l_res-1; ++i)
        {
            double koef = matrix[i + 1][i] / matrix[i][i];
            for (int j = 0; j < l_res; ++j)
            {
                matrix[i + 1][j] -= matrix[i][j] * koef;
            }
            koefs_first[i] = koef;
        }

        for (int i = l_res-1; i > 1; --i)
        {
            double koef = matrix[i - 1][i] / matrix[i][i];
            for (int j = 0; j < l_res; ++j)
            {
                matrix[i - 1][j] -= matrix[i][j] * koef;
            }
            koefs_second[i] = koef;
        }

        /*
        for (int i = 0; i < l_res; ++i)
        {
            for (int j = 0; j < l_res; ++j)
            {
                std::cout << std::fixed << std::setprecision(2) << double(matrix[i][j]) << " ";
            }
            std::cout << std::endl;
        }
        */
        
        for (int i = 0; i < l_res; ++i)
        {
            values[0][i] = u_start(double(i)/(l_res-1));
        }

        for (int i = 0; i < t_res-1; ++i)
        {
            for (int j = 0; j < l_res; ++j)
            {
                values[i + 1][j] = ((j == 0) || (j + 1 == l_res) ? 0 : ((alpha*values[i][j - 1] + 2 * (1 - alpha)*values[i][j] + alpha * values[i][j + 1]) / matrix[j][j]));
            }

            for (int j = 0; j < l_res - 1; ++j)
            {
                values[i + 1][j+1] -= values[i + 1][j] * koefs_first[j];
            }
            
            for (int j = l_res - 1; j > 1; --j)
            {
                values[i + 1][j - 1] -= values[i + 1][j] * koefs_second[j];
            }
        }

        std::vector<double> x;
        x.resize(l_res);

        for (int i = 0; i < l_res; ++i)
        {
            x[i] = double(i) / (l_res-1);
        }

        GNUDrawer gnuDrawer;
        auto arr = Arrays::Construct();
        arr->Add("x", x);

        for (int i = 0; i < t_res; ++i)
        {
            arr->Add(std::to_string(double(i)/(t_res-1)), values[i]);
        }
       
        gnuDrawer.Add(arr);
        gnuDrawer.Draw();

        std::vector<double>t_x(t_res);
        std::vector<double>max_temp(t_res);
        std::vector<double>exp_v(t_res);

        for (int i = 0; i < t_res; ++i)
        {
            t_x[i] = ((double)i) / (t_res - 1);
            max_temp[i] = *std::max_element(values[i].begin(), values[i].end());
            exp_v[i] = exp(-t_x[i]*10)*0.15;
        }


        GNUDrawer gnuDrawer2;
        auto arr2 = Arrays::Construct();
        arr2->Add("t", t_x);
        arr2->Add("max_temp", max_temp);
        arr2->Add("exp", exp_v);
        gnuDrawer2.Add(arr2);
        gnuDrawer2.Draw();
    }
};