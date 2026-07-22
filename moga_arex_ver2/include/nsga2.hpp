#ifndef _NSGA2_HPP_
#define _NSGA2_HPP_

#include <vector>

#include "population.hpp"
#include "individual.hpp"

class NSGA2
{
public:
  NSGA2() = default;

  // 支配されているかを判定
  bool dominates(const Individual &a, const Individual &b) const;
  // 非優越ソート
  vector<vector<int>> fastNonDominatedSort(Population &population) const;
  // 混雑距離計算
  void assignCrowdingDistance(Population &population, const vector<int> &front) const;
  // 次世代に残す個体を選択し，集団として保存
  Population environmentalSelection(Population &combined, int next_population_size) const;
  // 優越判定
  bool isBetter(const Individual &a, const Individual &b) const;
};

#endif