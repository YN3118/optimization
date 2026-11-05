#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "config.hpp"
#include <stdexcept>

class Random
{
private:
    mt19937 engine_;    // 乱数生成器
    unsigned int seed_; // シード値

public:
    // コンストラクタ（生成時の引数にシード値を受けとるようにする）
    explicit Random(unsigned int seed)
        : engine_(seed), seed_(seed)
    {
    }

    // シード値設定（この関数でシード値を再設定できる）
    void seed(unsigned int seed)
    {
        seed_ = seed;
        engine_.seed(seed_);
    }

    // シード確認
    unsigned int seedValue() const
    {
        return seed_;
    }

    // 実数生成
    double uniformReal(double min, double max)
    {
        if (min > max)
        {
            throw invalid_argument("uniformReal: min > max"); // 設定ミスを知らせる
        }

        uniform_real_distribution<double> dist(min, max);
        return dist(engine_);
    }

    // 整数生成
    int uniformInt(int min, int max)
    {
        if (min > max)
        {
            throw invalid_argument("uniformInt: min > max"); // 設定ミスを知らせる
        }

        uniform_int_distribution<int> dist(min, max);
        return dist(engine_);
    }

    // 正規分布に従う乱数生成
    double normal(double mean = 0.0, double stddev = 1.0)
    {
        if (stddev < 0.0)
        {
            throw invalid_argument("normal: stddev < 0");
        }

        normal_distribution<double> dist(mean, stddev);
        return dist(engine_);
    }

    // 入力された確率でTrueを返す
    bool bernoulli(double probability)
    {
        if (probability < 0.0 || probability > 1.0)
        {
            throw invalid_argument("bernoulli: probability must be in [0, 1]");
        }

        bernoulli_distribution dist(probability);
        return dist(engine_);
    }

    // 任意の型のvectorの要素を並び替える
    template <class T>
    void shuffle(vector<T> &values)
    {
        std::shuffle(values.begin(), values.end(), engine_);
    }

    mt19937 &engine()
    {
        return engine_;
    }
};

#endif
