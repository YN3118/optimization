#include "csv_writer.hpp"

#include <filesystem>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

CsvWriter::CsvWriter(const std::string& filename)
{
    file_.open(filename);

    if (!file_)
    {
        throw std::runtime_error(
            "CsvWriter: cannot open file: " + filename
        );
    }

    file_ << std::setprecision(17);
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

void CsvWriter::ensureDirectory(
    const std::string& directory
)
{
    if (!fs::exists(directory))
    {
        fs::create_directories(directory);
    }
}

std::string CsvWriter::makeResultDirectory(
    const Parameter& param
)
{
    return "results/" + param.fn;
}

std::string CsvWriter::makeSnapshotFilename(
    const Parameter& param,
    int generation
)
{
    std::ostringstream oss;

    oss << makeResultDirectory(param)
        << "/snapshot_gen"
        << std::setw(4)
        << std::setfill('0')
        << generation
        << ".csv";

    return oss.str();
}

std::string CsvWriter::makeFinalFilename(
    const Parameter& param
)
{
    return makeResultDirectory(param) + "/final.csv";
}

std::string CsvWriter::makeLogFilename(
    const Parameter& param
)
{
    return makeResultDirectory(param) + "/generation_log.csv";
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
    file_ << "seed," << seed << "\n";
    file_ << "constraint," << param.orconstraint << "\n";
    file_ << "output_filename," << param.filename << "\n";

    file_ << "bits_per_variable," << param.bits_per_variable << "\n";
    file_ << "total_bits," << param.total_bits << "\n";
    file_ << "crossover_rate," << param.crossover_rate << "\n";
    file_ << "bit_mutation_rate," << param.mutationrate << "\n";

    if (contain(param.fn,"WFG"))
    {
        file_ << "M," << param.M << "\n";
        file_ << "k," << param.k << "\n";
        file_ << "l," << param.l << "\n";
    }

    file_ << "\n";
}

void CsvWriter::writePopulation(
    const std::string& section_name,
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

        for (int i = 0; i < first.bitLength(); ++i)
        {
            file_ << ",bit" << i;
        }

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

void CsvWriter::writeIndividual(
    int index,
    const Individual& individual
)
{
    file_ << index;

    for (int bit : individual.bits)
    {
        file_ << "," << bit;
    }

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

void CsvWriter::writeSummary(
    const Parameter& param,
    const Evaluator& evaluator,
    int generation_count
)
{
    file_ << "summary,value\n";

    file_ << "function," << param.fn << "\n";
    file_ << "generation_count," << generation_count << "\n";
    file_ << "evaluation_count," << evaluator.evaluation_Count() << "\n";
    file_ << "population_size," << param.pop_size << "\n";
    file_ << "dimension," << param.dimension << "\n";

    file_ << "bits_per_variable," << param.bits_per_variable << "\n";
    file_ << "total_bits," << param.total_bits << "\n";
    file_ << "crossover_rate," << param.crossover_rate << "\n";
    file_ << "bit_mutation_rate," << param.mutationrate << "\n";

    if (contain(param.fn,"WFG"))
    {
        file_ << "M," << param.M << "\n";
        file_ << "k," << param.k << "\n";
        file_ << "l," << param.l << "\n";
    }

    file_ << "\n";
}

void CsvWriter::writeGenerationLogHeader()
{
    file_ << "generation";
    file_ << ",evaluation_count";
    file_ << ",population_size";
    file_ << "\n";
}

void CsvWriter::writeGenerationLog(
    int generation,
    const Evaluator& evaluator,
    const Population& population
)
{
    file_ << generation;
    file_ << "," << evaluator.evaluation_Count();
    file_ << "," << population.size();
    file_ << "\n";
}