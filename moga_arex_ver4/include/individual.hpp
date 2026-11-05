#ifndef _INDIVIDUAL_HPP_
#define _INDIVIDUAL_HPP_

#include "config.hpp"

class Individual
{
public:
  vector<double> x;            // 設計変数ベクトル
  vector<double> f;            // 目的関数値ベクトル
  double constraint_violation; // 制約違反量

  // AREX用の変数
  vector<double> eps;

  // NSGA2用の変数
  int rank;                 // ランク
  double crowding_distance; // 混雑距離

  bool evaluated; // 評価済みフラグ

  // デフォルトコンストラクタ
  Individual()
      : constraint_violation(0.0),
        rank(-1),
        crowding_distance(0.0),
        evaluated(false)
  {
  }

  // コンストラクタ（次元数と目的関数の数を引数にする）
  Individual(int dimension, int objective_count)
      : x(dimension, 0.0),
        f(objective_count, 0.0),
        constraint_violation(0.0),
        rank(-1),
        crowding_distance(0.0),
        evaluated(false)
  {
    if (dimension <= 0)
    {
      throw invalid_argument("Individual: dimension must be positive.");
    }

    if (objective_count <= 0)
    {
      throw invalid_argument("Individual: objective_count must be positive.");
    }
  }

  // 次元数を返す
  int dimension() const
  {
    return static_cast<int>(x.size());
  }

  // 目的関数の数を返す
  int objectiveCount() const
  {
    return static_cast<int>(f.size());
  }

  // 制約を満たしているかどうか
  bool isFeasible() const
  {
    return constraint_violation <= 0.0;
  }

  // 評価情報を初期化
  void resetEvaluationInfo()
  {
    fill(f.begin(), f.end(), 0.0);
    constraint_violation = 0.0;
    rank = -1;
    crowding_distance = 0.0;
    evaluated = false;
  }

  // xだけを出力
  void printVariables(ostream &os = cout) const
  {
    os << setprecision(10);

    os << "x: ";
    for (double value : x)
    {
      os << value << " ";
    }
    os << "\n";
  }

  // 目的関数の値を出力
  void printObjectives(ostream &os = cout) const
  {
    os << setprecision(10);

    os << "f: ";
    for (double value : f)
    {
      os << value << " ";
    }
    os << "\n";
  }

  // 個体情報を出力
  void print(ostream &os = cout) const
  {
    os << setprecision(10);

    os << "x: ";
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
    os << " | violation: " << constraint_violation;
    os << " | evaluated: " << evaluated;
    os << "\n";
  }

  bool operator<(const Individual &other) const
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