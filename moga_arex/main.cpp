#include <iostream>
#include <ctime>

#include "parameter.hpp"
#include "random.hpp"
#include "population.hpp"
#include "evaluator.hpp"
#include "arex.hpp"
#include "nsga2.hpp"

int main(int argc, char* argv[])
{
    Parameter param;
    param.load(argc, argv);

    unsigned int seed;

    if (param.seed == -1)
    {
        seed = static_cast<unsigned int>(time(nullptr));
    }
    else
    {
        seed = static_cast<unsigned int>(param.seed);
    }

    Random random(seed);
    Evaluator evaluator;
    NSGA2 nsga2;
    AREX arex(param);

    Population population;
    population.initialize(param.pop_size, param, random);
    population.evaluateAll(param);

    population = nsga2.environmentalSelection(
        population,
        param.pop_size
    );

    for (int gen = 0; gen < param.max_gen; ++gen)
    {
        Population offspring = arex.generateOffspring(
            population,
            param,
            random,
            evaluator
        );

        Population combined = mergePopulation(
            population,
            offspring
        );

        population = nsga2.environmentalSelection(
            combined,
            param.pop_size
        );

        cout << "generation: " << gen + 1
                  << " alpha: " << arex.alpha()
                  << endl;
    }

    population.print();

    return 0;
}