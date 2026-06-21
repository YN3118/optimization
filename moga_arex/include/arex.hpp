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
  // コンストラクタ
  explicit AREX(const Parameter &param);
  // 子集団生成
  Population generateOffspring(const Population &population, const Parameter &param, Random &random, Evaluator &evaluator);
  // 拡張率を返す
  double alpha() const;

private:
  // 親選択
  vector<int> selectParentIndices(int population_size, Random &random) const;
  // 親が存在するか
  vector<Individual> extractParents(const Population &population, const vector<int> &parent_indices) const;
  // 重心計算
  vector<double> computeCentroid(const vector<Individual> &parents, int dimension) const;
  // 交叉中心降下
  vector<double> computeDescentCenter(vector<Individual> parents, int dimension) const;
  // 重心との差を計算
  vector<vector<double>> computeDeviationVectors(const vector<Individual> &parents, const vector<double> &centroid, int dimension) const;
  // 子個体生成
  Individual generateChild(const vector<double> &descent_center, const vector<vector<double>> &deviations, const Parameter &param, Random &random) const;
  // 解を範囲内に修正
  void repairBounds(Individual &child, const Parameter &param) const;
  // 拡張率更新
  void updateAlpha(const Population &offspring, const Parameter &param);
};

#endif