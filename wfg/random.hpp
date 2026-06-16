#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "config.hpp"
#include <stdexcept>

class Random
{
private:
    mt19937 engine_;
    unsigned int seed_;

public:
    explicit Random(unsigned int seed)
        : engine_(seed), seed_(seed)
    {
    }

    void seed(unsigned int seed)
    {
        seed_ = seed;
        engine_.seed(seed_);
    }

    //シード設定
    unsigned int seedValue() const
    {
        return seed_;
    }

    //実数生成
    double uniformReal(double lower = 0.0, double upper = 1.0)
    {
        if (lower > upper)
        {
            throw invalid_argument("uniformReal: lower > upper");
        }

        uniform_real_distribution<double> dist(lower, upper);
        return dist(engine_);
    }

    //整数生成
    int uniformInt(int lower, int upper)
    {
        if (lower > upper)
        {
            throw invalid_argument("uniformInt: lower > upper");
        }

        uniform_int_distribution<int> dist(lower, upper);
        return dist(engine_);
    }

    //正規分布に従う乱数生成
    double normal(double mean = 0.0, double stddev = 1.0)
    {
        if (stddev < 0.0)
        {
            throw invalid_argument("normal: stddev < 0");
        }

        normal_distribution<double> dist(mean, stddev);
        return dist(engine_);
    }

    bool bernoulli(double probability)
    {
        if (probability < 0.0 || probability > 1.0)
        {
            throw invalid_argument("bernoulli: probability must be in [0, 1]");
        }

        bernoulli_distribution dist(probability);
        return dist(engine_);
    }

    template <class T>
    void shuffle(std::vector<T>& values)
    {
        shuffle(values.begin(), values.end(), engine_);
    }

    mt19937& engine()
    {
        return engine_;
    }
};

#endif
