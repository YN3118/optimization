#include <ctime>
#include <iostream>

#include "parameter.hpp"
#include "random.hpp"
#include "population.hpp"
#include "evaluator.hpp"
#include "bit_ga.hpp"
#include "nsga2.hpp"
#include "csv_writer.hpp"

int main(int argc, char* argv[])
{
    Parameter param;
    param.load(argc, argv);
    param.echo();

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
    BitGA bit_ga;

    Population population;
    population.initialize(param.pop_size, param, random);
    population.evaluateAll(param);

    population = nsga2.environmentalSelection(
        population,
        param.pop_size
    );

    Population initial_population = population;



    int generation_count = 0;

    for (int gen = 0; gen < param.max_gen; ++gen)
    {
        Population offspring = bit_ga.generateOffspring(
            population,
            param,
            random,
            evaluator,
            nsga2
        );

        Population combined = mergePopulation(
            population,
            offspring
        );

        population = nsga2.environmentalSelection(
            combined,
            param.pop_size
        );

        generation_count = gen + 1;


    }

    CsvWriter result_writer(param.filename);

    result_writer.writeParameter(param, seed);
    result_writer.writePopulation("initial_population", initial_population);
    result_writer.writePopulation("final_population", population);

    return 0;
}