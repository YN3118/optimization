#ifndef _CONSTRAINT_H_
#define _CONSTRAINT_H_

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "function.h"
#include "parameter.h"

// 制約条件
// 設計変数の和が0
// 定義域を超えないように

bool constraint(vector<double> x)
{
    if (param.orconstraint == 1)
    {
        double sum = 0.0;
        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] < param.min_value || param.max_value < x[i])
                return false;
            sum += x[i];
        }
        // Rosenbrockのときは和がnになるように(最適解が[1,1,...,1]のため)
        if (param.f_num == 0 || param.f_num == 5)
        {
            if (abs(sum) < param.dimension - 1.0e-9 || param.dimension + 1.0e-9 < abs(sum))
                return false;
        }
        else
        {
            if (abs(sum) > 1.0e-9)
                return false;
        }
        return true;
    }

    // 制約なし
    else
    {
        for (int i = 0; i < x.size(); i++)
        {
            if (x[i] < param.min_value || param.max_value < x[i])
                return false;
        }
        return true;
    };
}

#endif