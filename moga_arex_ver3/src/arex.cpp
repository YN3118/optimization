#include "arex.hpp"
#include "knn.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

// コンストラクタ
AREX::AREX(const Parameter &param)
    : parent_count_(param.p_size),
      child_count_(param.c_size),
      alpha_(1.0)
{
  if (parent_count_ <= 0)
  {
    throw invalid_argument("AREX: parent_count must be positive.");
  }

  if (child_count_ <= 0)
  {
    throw invalid_argument("AREX: child_count must be positive.");
  }
}

// 拡張率を返す
double AREX::alpha() const
{
  return alpha_;
}

// 子集団生成
Population AREX::generateOffspring(const Population &population, const Parameter &param, Random &random, Evaluator &evaluator, const NSGA2 &nsga2)
{
  if (population.size() < parent_count_)
  {
    throw invalid_argument(
        "AREX::generateOffspring: population size is smaller than parent_count.");
  }

  vector<int> parent_indices = selectParentIndices(population.size(), random);
  vector<Individual> parents = extractParents(population, parent_indices, random, param);
  vector<double> centroid = computeCentroid(parents, param.dimension);
  vector<double> descent_center = computeDescentCenter(parents, param.dimension);

  vector<vector<double>> deviations = computeDeviationVectors(parents, centroid, param.dimension);

  Population offspring;
  offspring.reserve(child_count_);

  for (int i = 0; i < child_count_; i++)
  {
    Individual child = generateChild(descent_center, deviations, param, random);
    repairBounds(child, param);
    evaluator.evaluate(child, param);
    offspring.push_Back(move(child));
  }

  // 生成した子個体にNSGA-Ⅱを適用してソート
  vector<vector<int>> fronts = nsga2.fastNonDominatedSort(offspring);
  for (const auto &front : fronts)
  {
    nsga2.assignCrowdingDistance(offspring, front);
  }

  updateAlpha(offspring, param);
  return offspring;
}

vector<int> AREX::selectParentIndices(int population_size, Random &random) const
{
  vector<int> indices;
  indices.reserve(population_size);
  for (int i = 0; i < population_size; i++)
  {
    indices.push_back(i);
  }
  random.shuffle(indices);
  indices.resize(parent_count_);
  return indices;
}

// 全ての個体のランクが0のときは特別な選択をするように改良
vector<Individual> AREX::extractParents(const Population &population, const vector<int> &parent_indices, Random &random, const Parameter &param) const
{
  vector<Individual> parents;
  parents.reserve(param.p_size);
  if (population[population.size() - 1].rank == 0)
  {
    parents.resize(param.p_size);
    int target = random.uniformInt(0, 1);
    parents = findKNearestIndividuals(population, target, param.p_size);
  }
  else
  {

    for (int index : parent_indices)
    {
      parents.push_back(population.at(index));
    }
  }

  return parents;
}

// 重心計算
vector<double> AREX::computeCentroid(const vector<Individual> &parents, int dimension) const
{
  vector<double> centroid(dimension, 0.0);
  for (const auto &parent : parents)
  {
    for (int d = 0; d < dimension; d++)
    {
      centroid[d] += parent.x[d];
    }
  }
  for (int d = 0; d < dimension; d++)
  {
    centroid[d] /= static_cast<double>(parents.size());
  }
  return centroid;
}

// 交叉中心降下
vector<double> AREX::computeDescentCenter(vector<Individual> parents, int dimension) const
{
  sort(parents.begin(), parents.end());
  vector<double> descent_center(dimension, 0.0);
  for (int i = 0; i < static_cast<int>(parents.size()); i++)
  {
    double weight =
        2.0 * (dimension + 1 - i) / static_cast<double>((dimension + 1) * (dimension + 2));

    for (int d = 0; d < dimension; d++)
    {
      descent_center[d] += weight * parents[i].x[d];
    }
  }
  return descent_center;
}

// 重心との差を計算
vector<vector<double>> AREX::computeDeviationVectors(const vector<Individual> &parents, const vector<double> &centroid, int dimension) const
{
  vector<vector<double>> deviations;
  deviations.reserve(parents.size());
  for (const auto &parent : parents)
  {
    vector<double> deviation(dimension, 0.0);
    for (int d = 0; d < dimension; d++)
    {
      deviation[d] = parent.x[d] - centroid[d];
    }
    deviations.push_back(move(deviation));
  }
  return deviations;
}

// 子個体生成
Individual AREX::generateChild(const vector<double> &descent_center, const vector<vector<double>> &deviations, const Parameter &param, Random &random) const
{
  Individual child(param.dimension, param.objectiveCount());
  vector<double> eps(parent_count_, 0.0);
  for (int d = 0; d < param.dimension; d++)
  {
    child.x[d] = descent_center[d];
  }
  double stddev = sqrt(1.0 / static_cast<double>(param.dimension));
  for (int j = 0; j < parent_count_; j++)
  {
    eps[j] = random.normal(0.0, stddev);

    for (int d = 0; d < param.dimension; d++)
    {
      child.x[d] += alpha_ * eps[j] * deviations[j][d];
    }
  }
  child.eps = eps;
  child.resetEvaluationInfo();
  return child;
}

// 解を範囲内に修正
void AREX::repairBounds(Individual &child, const Parameter &param) const
{
  for (int d = 0; d < param.dimension; d++)
  {
    if (child.x[d] < param.min_value[d])
    {
      child.x[d] = param.min_value[d];
    }
    if (child.x[d] > param.max_value[d])
    {
      child.x[d] = param.max_value[d];
    }
  }
}

// 拡張率更新
void AREX::updateAlpha(const Population &offspring, const Parameter &param)
{
  if (offspring.size() < parent_count_)
  {
    return;
  }
  Population sorted_offspring = offspring;
  sort(sorted_offspring.individuals().begin(), sorted_offspring.individuals().end());
  double sum1 = 0.0;
  double sum2 = 0.0;
  for (int j = 0; j < parent_count_; j++)
  {
    double e = 0.0;

    for (int i = 0; i < parent_count_; i++)
    {
      e += sorted_offspring.at(i).eps[j] / static_cast<double>(param.dimension + 1);
    }
    sum1 += pow(e, 2.0);
    sum2 += e;
  }

  sum2 = pow(sum2, 2.0) / static_cast<double>(param.dimension + 1);

  double L_cdp = pow(alpha_, 2.0) * static_cast<double>(param.dimension) * (sum1 - sum2);
  double L_avg = pow(alpha_, 2.0) * static_cast<double>(param.dimension) / static_cast<double>(param.dimension + 1);
  double c = param.learning_rate;
  double next_alpha = alpha_ * sqrt((1.0 - c) + c * L_cdp / L_avg);
  if (next_alpha < 1.0)
  {
    alpha_ = 1.0;
  }
  // // alphaに上限値を追加
  // else if (next_alpha > 3.0)
  // {
  //   alpha_ = 2.0;
  // }
  else
  {
    alpha_ = next_alpha;
  }
}