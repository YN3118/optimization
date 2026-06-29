#include <ctime>
#include <iostream>

#include "parameter.hpp"
#include "random.hpp"
#include "population.hpp"
#include "evaluator.hpp"
#include "arex.hpp"
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
    AREX arex(param);

    Population population;
    population.initialize(param.pop_size, param, random);
    population.evaluateAll(param);

    population = nsga2.environmentalSelection(
        population,
        param.pop_size
    );

    Population initial_population = population;

    string alpha_filename = makeAlphaFilename(param.filename);
    CsvWriter alpha_writer(alpha_filename);

    alpha_writer.writeGenerationLogHeader();

    alpha_writer.writeGenerationLog(
        0,
        arex,
        evaluator,
        population
    );

    int generation_count = 0;

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

        generation_count = gen + 1;

        alpha_writer.writeGenerationLog(
            generation_count,
            arex,
            evaluator,
            population
        );

        cout << "generation: " << generation_count
                  << " alpha: " << arex.alpha()
                  << " evaluations: " << evaluator.evaluation_Count()
                  << endl;
    }

    CsvWriter result_writer(param.filename);

    result_writer.writeParameter(param, seed);
    result_writer.writePopulation("initial_population", initial_population);
    result_writer.writePopulation("final_population", population);
    result_writer.writeSummary(param, evaluator, arex, generation_count);

    return 0;
}