#include "csv_writer.hpp"
#include "config.hpp"

#include <iostream>
#include <stdexcept>
#include <iomanip>

CsvWriter::CsvWriter(const string& filename)
{
    file_.open(filename);

    if (!file_)
    {
        throw runtime_error(
            "CsvWriter: cannot open file: " + filename
        );
    }

    file_ << setprecision(17);
}

CsvWriter::~CsvWriter()
{
    if (file_.is_open())
    {
        file_.close();
    }
}

bool CsvWriter::isOpen() const
{
    return file_.is_open();
}

void CsvWriter::writeParameter(
    const Parameter& param,
    unsigned int seed
)
{
    file_ << "parameter,value\n";

    file_ << "function," << param.fn << "\n";
    file_ << "dimension," << param.dimension << "\n";
    file_ << "population_size," << param.pop_size << "\n";
    file_ << "max_generation," << param.max_gen << "\n";
    file_ << "parent_size," << param.p_size << "\n";
    file_ << "child_size," << param.c_size << "\n";
    file_ << "seed," << seed << "\n";
    file_ << "constraint," << param.orconstraint << "\n";
    file_ << "mutation_rate," << param.mutationrate << "\n";
    file_ << "learning_rate," << param.learning_rate << "\n";

    if (contain(param.fn,"WFG"))
    {
        file_ << "M," << param.M << "\n";
        file_ << "k," << param.k << "\n";
        file_ << "l," << param.l << "\n";
    }

    file_ << "\n";
}

void CsvWriter::writePopulation(
    const string& section_name,
    const Population& population
)
{
    file_ << section_name << "\n";

    writeIndividualHeader(population);

    for (int i = 0; i < population.size(); ++i)
    {
        writeIndividual(i, population[i]);
    }

    file_ << "\n";
}

void CsvWriter::writeIndividualHeader(
    const Population& population
)
{
    file_ << "index";

    if (!population.empty())
    {
        const Individual& first = population[0];

        for (int i = 0; i < first.dimension(); ++i)
        {
            file_ << ",x" << i;
        }

        for (int m = 0; m < first.objectiveCount(); ++m)
        {
            file_ << ",f" << m;
        }
    }

    file_ << ",rank";
    file_ << ",crowding_distance";
    file_ << ",constraint_violation";
    file_ << ",evaluated";

    file_ << "\n";
}

void CsvWriter::writeGenerationLogHeader()
{
    file_ << "generation";
    file_ << ",alpha";
    file_ << ",evaluation_count";
    file_ << ",population_size";
    file_ << "\n";
}


void CsvWriter::writeIndividual(int index,const Individual& individual)
{
    file_ << index;

    for (double value : individual.x)
    {
        file_ << "," << value;
    }

    for (double value : individual.f)
    {
        file_ << "," << value;
    }

    file_ << "," << individual.rank;
    file_ << "," << individual.crowding_distance;
    file_ << "," << individual.constraint_violation;
    file_ << "," << individual.evaluated;

    file_ << "\n";
}
