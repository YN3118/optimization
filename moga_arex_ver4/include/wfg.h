#ifndef WFG_WRAPPER_H
#define WFG_WRAPPER_H

#include <cassert>
#include <string>
#include <vector>

#include "WFG_Toolkit/ExampleProblems.h"
#include "WFG_Toolkit/ExampleShapes.h"
#include "WFG_Toolkit/TransFunctions.h"

// WFG / I problem の目的関数値を計算する
inline std::vector<double> problem_calc_fitness(
    const std::vector<double>& z,
    const int k,
    const int M,
    const std::string& fn
)
{
    using namespace WFG::Toolkit::Examples;

    if (fn == "WFG1")
    {
        return Problems::WFG1(z, k, M);
    }
    else if (fn == "WFG2")
    {
        return Problems::WFG2(z, k, M);
    }
    else if (fn == "WFG3")
    {
        return Problems::WFG3(z, k, M);
    }
    else if (fn == "WFG4")
    {
        return Problems::WFG4(z, k, M);
    }
    else if (fn == "WFG5")
    {
        return Problems::WFG5(z, k, M);
    }
    else if (fn == "WFG6")
    {
        return Problems::WFG6(z, k, M);
    }
    else if (fn == "WFG7")
    {
        return Problems::WFG7(z, k, M);
    }
    else if (fn == "WFG8")
    {
        return Problems::WFG8(z, k, M);
    }
    else if (fn == "WFG9")
    {
        return Problems::WFG9(z, k, M);
    }
    else if (fn == "I1")
    {
        return Problems::I1(z, k, M);
    }
    else if (fn == "I2")
    {
        return Problems::I2(z, k, M);
    }
    else if (fn == "I3")
    {
        return Problems::I3(z, k, M);
    }
    else if (fn == "I4")
    {
        return Problems::I4(z, k, M);
    }
    else if (fn == "I5")
    {
        return Problems::I5(z, k, M);
    }

    assert(false);
    return std::vector<double>();
}

// Pareto front 形状を直接計算したい場合用
// 通常の最適化では使わなくてもよい
inline std::vector<double> problem_optimal_soln(
    const std::vector<double>& y,
    const std::string& fn
)
{
    using namespace WFG::Toolkit::Examples;

    if (fn == "WFG1")
    {
        return Shapes::WFG1_shape(y);
    }
    else if (fn == "WFG2")
    {
        return Shapes::WFG2_shape(y);
    }
    else if (fn == "WFG3")
    {
        return Shapes::WFG3_shape(y);
    }
    else if (
        fn == "WFG4" ||
        fn == "WFG5" ||
        fn == "WFG6" ||
        fn == "WFG7" ||
        fn == "WFG8" ||
        fn == "WFG9"
    )
    {
        return Shapes::WFG4_shape(y);
    }
    else if (
        fn == "I1" ||
        fn == "I2" ||
        fn == "I3" ||
        fn == "I4" ||
        fn == "I5"
    )
    {
        return Shapes::I1_shape(y);
    }

    assert(false);
    return std::vector<double>();
}

#endif