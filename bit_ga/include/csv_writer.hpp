#ifndef CSV_WRITER_HPP
#define CSV_WRITER_HPP

#include <fstream>
#include <string>

#include "parameter.hpp"
#include "population.hpp"
#include "evaluator.hpp"

class CsvWriter
{
private:
    std::ofstream file_;

public:
    explicit CsvWriter(const std::string& filename);
    ~CsvWriter();

    bool isOpen() const;

    void writeParameter(
        const Parameter& param,
        unsigned int seed
    );

    void writePopulation(
        const std::string& section_name,
        const Population& population
    );

    void writeSummary(
        const Parameter& param,
        const Evaluator& evaluator,
        int generation_count
    );

    void writeGenerationLogHeader();

    void writeGenerationLog(
        int generation,
        const Evaluator& evaluator,
        const Population& population
    );

    static void ensureDirectory(
        const std::string& directory
    );

    static std::string makeResultDirectory(
        const Parameter& param
    );

    static std::string makeSnapshotFilename(
        const Parameter& param,
        int generation
    );

    static std::string makeFinalFilename(
        const Parameter& param
    );

    static std::string makeLogFilename(
        const Parameter& param
    );

private:
    void writeIndividualHeader(
        const Population& population
    );

    void writeIndividual(
        int index,
        const Individual& individual
    );
};

#endif