#ifndef _AREX_HPP_
#define _AREX_HPP_

#include <vector>
#include "population.hpp"
#include "individual.hpp"
#include "parameter.hpp"
#include "random.hpp"
#include "evaluator.hpp"

class AREX
{
private:
  int parent_count_;
  int child_count_;
  double alpha_;

public:
  explicit AREX(const Parameter &param);

  Population generateOffspring(
      const Population &population,
      const Parameter &param,
      Random &random,
      Evaluator &evaluator);

  double alpha() const;

  // 子集団にNSGA-IIのrank/crowding_distanceを付与した後で呼ぶ。
  void updateAlpha(
      const Population &offspring,
      const Parameter &param);

private:
  std::vector<int> selectParentIndices(
      int population_size,
      Random &random) const;

  std::vector<Individual> extractParents(
      const Population &population,
      const std::vector<int> &parent_indices) const;

  std::vector<double> computeCentroid(
      const std::vector<Individual> &parents,
      int dimension) const;

  std::vector<double> computeDescentCenter(
      std::vector<Individual> parents,
      int dimension) const;

  std::vector<std::vector<double>> computeDeviationVectors(
      const std::vector<Individual> &parents,
      const std::vector<double> &centroid,
      int dimension) const;

  Individual generateChild(
      const std::vector<double> &descent_center,
      const std::vector<std::vector<double>> &deviations,
      const Parameter &param,
      Random &random) const;

  // 多項式突然変異。mutationrate <= 0 の場合は何もしない。
  void mutate(
      Individual &child,
      const Parameter &param,
      Random &random) const;

  // 単純クリッピングではなく反射で範囲内に戻す。
  void repairBounds(
      Individual &child,
      const Parameter &param) const;
};

#endif
