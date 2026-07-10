#ifndef CSV_WRITER_HPP
#define CSV_WRITER_HPP

#include <fstream>
#include <string>

#include "parameter.hpp"
#include "population.hpp"
#include "evaluator.hpp"
#include "arex.hpp"

class CsvWriter
{
private:
    ofstream file_;

public:
    explicit CsvWriter(const string &filename);
    ~CsvWriter();

    bool isOpen() const;

    void writeParameter(const Parameter &param, unsigned int seed);

    void writePopulation(const string &section_name, const Population &population);

    void writeSummary(const Parameter &param, const Evaluator &evaluator, const AREX &arex, int generation_count);

    void writeGenerationLogHeader();

    void writeGenerationLog(int generation, const AREX &arex, const Evaluator &evaluator, const Population &population);

    static string makeResultDirectory(const Parameter &param);

    static string makeSnapshotFilename(const Parameter &param, int generation);

    static string makeFinalFilename(const Parameter &param);

    static void ensureDirectory(const std::string &directory);

private:
    void writeIndividualHeader(const Population &population);

    void writeIndividual(int index, const Individual &individual);
};

#endif