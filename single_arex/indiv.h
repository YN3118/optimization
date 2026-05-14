#ifndef _INDIV_H_
#define _INDIV_H_

#include <vector>
#include "config.h"
#include "function.h"
#include "benchmark.h"
#include "constraint.h"
#include "parameter.h"

using namespace std;
namespace func = Function;

class Indiv
{
public:
    vector<double> x; // 設計変数
    double f;         // 関数値

    vector<double> eps; // AREXの拡張率計算用

    // コンストラクタ
    Indiv()
    {
        x.resize(param.dimension);
        double sum = 0.0;
        for (int i = 0; i < x.size(); i++)
        {
            // x[i]=func::generateRandomDouble(param.min_value,param.max_value);
            x[i] = func::generateRandomDouble(1.0, 5.0); //<----初期集団に偏りを持たせる
            sum += x[i];
        }

        // 制約あるときの処理
        if (param.orconstraint == 1)
        {
            // Rosenbrockのとき
            if (param.f_num == 0 || param.f_num == 5)
            {
                for (int i = 0; i < x.size(); i++)
                {
                    x[i] = x[i] + ((param.dimension - sum) / x.size());
                }
            }
            else
            {
                for (int i = 0; i < x.size(); i++)
                {
                    x[i] = x[i] - (sum / x.size());
                }
            }
        }
        f = f_value(param.f_num, x);
        eps.resize(param.p_size, 0.0);
    }

    Indiv(vector<double> a, int i)
    {
        x.resize(a.size());
        x = a;
        f = f_value(param.f_num, x);
        eps.resize(param.p_size, 0.0);
    }

    void echo()
    {
        for (int i = 0; i < param.dimension; i++)
        {
            printf("x[%d]:%f\t", i, x[i]);
        }
        printf("f(x):%6f\t", f);
        printf("\n");
    }

    // オペレータ
    Indiv &operator=(const Indiv &s)
    {
        x = s.x;
        f = s.f;
        eps = s.eps;
        return *this;
    }

    bool operator==(const Indiv &s) const
    {
        if (f != s.f)
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

    bool operator>(const Indiv &s) const
    {
        if (f > s.f)
            return true;
        return false;
    }

    bool operator<(const Indiv &s) const
    {
        // return (!operator>(s));
        if (f < s.f)
            return true;
        return false;
    }
};

#endif