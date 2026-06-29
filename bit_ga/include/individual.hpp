#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

class Individual
{
public:
    // bitstring 表現
    std::vector<int> bits;

    // デコード後の実数ベクトル
    std::vector<double> x;

    // 目的関数値
    std::vector<double> f;

    // NSGA-II 用
    int rank;
    double crowding_distance;

    // 制約・評価情報
    double constraint_violation;
    bool evaluated;

public:
    Individual()
        : rank(-1),
          crowding_distance(0.0),
          constraint_violation(0.0),
          evaluated(false)
    {
    }

    Individual(
        int dimension,
        int objective_count,
        int total_bits
    )
        : bits(total_bits, 0),
          x(dimension, 0.0),
          f(objective_count, 0.0),
          rank(-1),
          crowding_distance(0.0),
          constraint_violation(0.0),
          evaluated(false)
    {
    }

    int dimension() const
    {
        return static_cast<int>(x.size());
    }

    int objectiveCount() const
    {
        return static_cast<int>(f.size());
    }

    int bitLength() const
    {
        return static_cast<int>(bits.size());
    }

    void resetEvaluationInfo()
    {
        std::fill(f.begin(), f.end(), 0.0);
        rank = -1;
        crowding_distance = 0.0;
        constraint_violation = 0.0;
        evaluated = false;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << std::setprecision(10);

        os << "bits: ";
        for (int b : bits)
        {
            os << b;
        }

        os << " | x: ";
        for (double value : x)
        {
            os << value << " ";
        }

        os << " | f: ";
        for (double value : f)
        {
            os << value << " ";
        }

        os << " | rank: " << rank;
        os << " | crowding: " << crowding_distance;
        os << "\n";
    }

    bool operator<(const Individual& other) const
    {
        if (rank != other.rank)
        {
            return rank < other.rank;
        }

        if (crowding_distance != other.crowding_distance)
        {
            return crowding_distance > other.crowding_distance;
        }

        if (!f.empty() && !other.f.empty())
        {
            return f[0] < other.f[0];
        }

        return false;
    }
};

#endif