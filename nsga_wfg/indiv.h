#ifndef _INDIV_H_
#define _INDIV_H_

#include <vector>
#include "wfg.h"
#include "function.h"
#include "benchmark.h"
#include "constraint.h"
#include "parameter.h"

using namespace std;
namespace func = Function;

class Indiv
{
public:
    vector<double> x;   // 設計変数ベクトル
    vector<double> eps; // AREXの拡張率計算用

    double crowding_distance; // 混雑距離
    int rank;                 // ランク
    int dominant;             // 支配数
    vector<double> fitness;

    // コンストラクタ
    Indiv()
    {
        x.resize(param.dimension);
        double sum = 0.0;
        x = problem_random_soln(param.k, param.l, param.fn);

        fitness.resize(param.M);
        fitness = problem_calc_fitness(x, param.k, param.M, param.fn);

        eps.resize(param.p_size, 0.0);

        crowding_distance = 0.0;
        rank = 0;
        dominant = 0;
    }

    Indiv(vector<double> a)
    {
        x.resize(a.size());
        x = a;
        fitness.resize(param.M);
        fitness = problem_calc_fitness(x, param.k, param.M, param.fn);
        eps.resize(param.p_size, 0.0);
        crowding_distance = 0.0;
        dominant = 0;
        rank = 0;
    }

    void echo()
    {
        for (int i = 0; i < x.size(); i++)
        {
            printf("x[%d]=%f\t", i, x[i]);
        }
        cout << endl;
        for (int i = 0; i < fitness.size(); i++)
        {
            printf("fitness[%d]=%f\t", i, fitness[i]);
        }
        cout << endl;
    }

    bool operator==(const Indiv &s) const
    {
        if (fitness != s.fitness)
            return false;
        for (int i = 0; i < param.dimension; i++)
        {
            if (x[i] != s.x[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Indiv &s) const
    {
        return (!operator==(s));
    }

    bool operator<(const Indiv &s) const
    {
        if (rank != s.rank)
            return rank < s.rank;
        return crowding_distance > s.crowding_distance;
    }

    bool operator>(const Indiv &s) const
    {
        return (!operator<(s));
    }
};

#endif