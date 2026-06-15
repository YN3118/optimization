#include <iostream>
#include <vector>
#include <string>
#include "wfg.h"

Parameter param;
mt19937 gen;
int main(int argc, char *argv[])
{
    int M = 2;          // 目的関数の数
    int k = 4;          // position-related parameters
    int l = 20;         // distance-related parameters
    std::string fn = "WFG4";

    param.load(argc, argv);
    unsigned int seed;

    if (param.seed == -1)
    {
        seed = (unsigned int)time(NULL);
    }
    else
        seed = (unsigned int)param.seed;
    srand(seed);
    gen.seed(seed);


    std::vector<double> z = problem_random_soln(k, l, fn);
    std::vector<double> f = problem_calc_fitness(z, k, M, fn);

    std::cout << "Problem: " << fn << std::endl;

    std::cout << "z = ";
    for (double v : z)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "f = ";
    for (double v : f)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout<<param.seed<<std::endl;

    return 0;
}