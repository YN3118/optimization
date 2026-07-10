#include <ctime>
#include <iostream>
#include <string>

#include "parameter.hpp"
#include "random.hpp"
#include "population.hpp"
#include "evaluator.hpp"
#include "nsga2.hpp"
#include "bit_ga.hpp"
#include "csv_writer.hpp"

int main(int argc, char* argv[])
{
    Parameter param;
    param.load(argc, argv);
    param.echo();

    unsigned int seed;

    if (param.seed == -1)
    {
        seed = static_cast<unsigned int>(std::time(nullptr));
    }
    else
    {
        seed = static_cast<unsigned int>(param.seed);
    }

    Random random(seed);
    Evaluator evaluator;
    NSGA2 nsga2;
    BitGA bit_ga;

    CsvWriter::ensureDirectory(
        CsvWriter::makeResultDirectory(param)
    );

    Population population;
    population.initialize(
        param.pop_size,
        param,
        random
    );

    population.evaluateAll(param);

    population = nsga2.environmentalSelection(
        population,
        param.pop_size
    );

    Population initial_population = population;

    {
        CsvWriter snapshot_writer(
            CsvWriter::makeSnapshotFilename(param, 0)
        );

        snapshot_writer.writeParameter(param, seed);
        snapshot_writer.writePopulation(
            "snapshot_generation_0",
            population
        );
    }

    CsvWriter log_writer(
        CsvWriter::makeLogFilename(param)
    );

    log_writer.writeGenerationLogHeader();

    log_writer.writeGenerationLog(
        0,
        evaluator,
        population
    );

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

        log_writer.writeGenerationLog(
            generation_count,
            evaluator,
            population
        );

        if (generation_count % 100 == 0)
        {
            CsvWriter snapshot_writer(
                CsvWriter::makeSnapshotFilename(
                    param,
                    generation_count
                )
            );

            snapshot_writer.writeParameter(param, seed);
            snapshot_writer.writePopulation(
                "snapshot_generation_" + std::to_string(generation_count),
                population
            );

            std::cout << "snapshot saved: generation "
                      << generation_count
                      << std::endl;
        }

        std::cout << "generation: "
                  << generation_count
                  << " evaluations: "
                  << evaluator.evaluation_Count()
                  << std::endl;
    }

    CsvWriter final_writer(
        CsvWriter::makeFinalFilename(param)
    );

    final_writer.writeParameter(param, seed);

    final_writer.writePopulation(
        "initial_population",
        initial_population
    );

    final_writer.writePopulation(
        "final_population",
        population
    );

    final_writer.writeSummary(
        param,
        evaluator,
        generation_count
    );

    return 0;
}