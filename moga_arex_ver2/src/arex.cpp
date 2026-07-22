#include "arex.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

AREX::AREX(const Parameter &param)
    : parent_count_(param.p_size),
      child_count_(param.c_size),
      alpha_(1.0)
{
  if (parent_count_ <= 0)
  {
    throw std::invalid_argument("AREX: parent_count must be positive.");
  }
  if (child_count_ <= 0)
  {
    throw std::invalid_argument("AREX: child_count must be positive.");
  }
  if (child_count_ < parent_count_)
  {
    throw std::invalid_argument(
        "AREX: child_count must be greater than or equal to parent_count.");
  }
}

double AREX::alpha() const
{
  return alpha_;
}

Population AREX::generateOffspring(
    const Population &population,
    const Parameter &param,
    Random &random,
    Evaluator &evaluator)
{
  if (population.size() < parent_count_)
  {
    throw std::invalid_argument(
        "AREX::generateOffspring: population size is smaller than parent_count.");
  }

  const std::vector<int> parent_indices =
      selectParentIndices(population.size(), random);
  const std::vector<Individual> parents =
      extractParents(population, parent_indices);
  const std::vector<double> centroid =
      computeCentroid(parents, param.dimension);
  const std::vector<double> descent_center =
      computeDescentCenter(parents, param.dimension);
  const std::vector<std::vector<double>> deviations =
      computeDeviationVectors(parents, centroid, param.dimension);

  Population offspring;
  offspring.reserve(child_count_);

  for (int i = 0; i < child_count_; ++i)
  {
    Individual child = generateChild(
        descent_center, deviations, param, random);

    // 偏差が縮退した方向にも探索成分を与える。
    mutate(child, param, random);
    repairBounds(child, param);
    evaluator.evaluate(child, param);
    offspring.push_Back(std::move(child));
  }

  // alpha更新はここでは行わない。
  // main側で子集団をNSGA-IIにより順位付けした後に行う。
  return offspring;
}

std::vector<int> AREX::selectParentIndices(
    int population_size,
    Random &random) const
{
  std::vector<int> indices;
  indices.reserve(population_size);
  for (int i = 0; i < population_size; ++i)
  {
    indices.push_back(i);
  }
  random.shuffle(indices);
  indices.resize(parent_count_);
  return indices;
}

std::vector<Individual> AREX::extractParents(
    const Population &population,
    const std::vector<int> &parent_indices) const
{
  std::vector<Individual> parents;
  parents.reserve(parent_indices.size());
  for (int index : parent_indices)
  {
    parents.push_back(population.at(index));
  }
  return parents;
}

std::vector<double> AREX::computeCentroid(
    const std::vector<Individual> &parents,
    int dimension) const
{
  std::vector<double> centroid(dimension, 0.0);
  for (const Individual &parent : parents)
  {
    for (int d = 0; d < dimension; ++d)
    {
      centroid[d] += parent.x[d];
    }
  }
  for (int d = 0; d < dimension; ++d)
  {
    centroid[d] /= static_cast<double>(parents.size());
  }
  return centroid;
}

std::vector<double> AREX::computeDescentCenter(
    std::vector<Individual> parents,
    int dimension) const
{
  std::sort(parents.begin(), parents.end());

  std::vector<double> descent_center(dimension, 0.0);
  const int mu = static_cast<int>(parents.size());

  // parent_count == dimension + 1 以外でも重みの総和が1になる形。
  for (int i = 0; i < mu; ++i)
  {
    const double weight =
        2.0 * static_cast<double>(mu - i) /
        static_cast<double>(mu * (mu + 1));

    for (int d = 0; d < dimension; ++d)
    {
      descent_center[d] += weight * parents[i].x[d];
    }
  }
  return descent_center;
}

std::vector<std::vector<double>> AREX::computeDeviationVectors(
    const std::vector<Individual> &parents,
    const std::vector<double> &centroid,
    int dimension) const
{
  std::vector<std::vector<double>> deviations;
  deviations.reserve(parents.size());

  for (const Individual &parent : parents)
  {
    std::vector<double> deviation(dimension, 0.0);
    for (int d = 0; d < dimension; ++d)
    {
      deviation[d] = parent.x[d] - centroid[d];
    }
    deviations.push_back(std::move(deviation));
  }
  return deviations;
}

Individual AREX::generateChild(
    const std::vector<double> &descent_center,
    const std::vector<std::vector<double>> &deviations,
    const Parameter &param,
    Random &random) const
{
  Individual child(param.dimension, param.objectiveCount());
  std::vector<double> eps(parent_count_, 0.0);

  child.x = descent_center;

  const double stddev =
      std::sqrt(1.0 / static_cast<double>(param.dimension));

  for (int j = 0; j < parent_count_; ++j)
  {
    eps[j] = random.normal(0.0, stddev);
    for (int d = 0; d < param.dimension; ++d)
    {
      child.x[d] += alpha_ * eps[j] * deviations[j][d];
    }
  }

  // resetEvaluationInfoはepsを消さないが、順序を明確にするため先にリセットする。
  child.resetEvaluationInfo();
  child.eps = std::move(eps);
  return child;
}

void AREX::mutate(
    Individual &child,
    const Parameter &param,
    Random &random) const
{
  if (param.mutationrate <= 0.0)
  {
    return;
  }

  // Debの多項式突然変異で一般的に使われる値。
  constexpr double eta_m = 20.0;

  for (int d = 0; d < param.dimension; ++d)
  {
    if (!random.bernoulli(param.mutationrate))
    {
      continue;
    }

    const double lower = param.min_value[d];
    const double upper = param.max_value[d];
    const double range = upper - lower;
    if (range <= 0.0)
    {
      continue;
    }

    const double x = std::clamp(child.x[d], lower, upper);
    const double delta1 = (x - lower) / range;
    const double delta2 = (upper - x) / range;
    const double u = random.uniformReal(0.0, 1.0);
    const double mut_pow = 1.0 / (eta_m + 1.0);

    double delta_q = 0.0;
    if (u <= 0.5)
    {
      const double xy = 1.0 - delta1;
      const double value =
          2.0 * u + (1.0 - 2.0 * u) *
                        std::pow(xy, eta_m + 1.0);
      delta_q = std::pow(value, mut_pow) - 1.0;
    }
    else
    {
      const double xy = 1.0 - delta2;
      const double value =
          2.0 * (1.0 - u) + 2.0 * (u - 0.5) *
                                  std::pow(xy, eta_m + 1.0);
      delta_q = 1.0 - std::pow(value, mut_pow);
    }

    child.x[d] = x + delta_q * range;
  }
}

void AREX::repairBounds(
    Individual &child,
    const Parameter &param) const
{
  for (int d = 0; d < param.dimension; ++d)
  {
    const double lower = param.min_value[d];
    const double upper = param.max_value[d];
    const double range = upper - lower;

    if (range <= 0.0)
    {
      throw std::invalid_argument(
          "AREX::repairBounds: upper bound must be greater than lower bound.");
    }

    // 何度も領域を越える大きな変位にも対応する反射写像。
    double shifted = std::fmod(child.x[d] - lower, 2.0 * range);
    if (shifted < 0.0)
    {
      shifted += 2.0 * range;
    }
    if (shifted <= range)
    {
      child.x[d] = lower + shifted;
    }
    else
    {
      child.x[d] = upper - (shifted - range);
    }
  }
}

void AREX::updateAlpha(
    const Population &offspring,
    const Parameter &param)
{
  if (offspring.size() < parent_count_)
  {
    return;
  }

  for (int i = 0; i < offspring.size(); ++i)
  {
    if (offspring[i].rank < 0)
    {
      throw std::logic_error(
          "AREX::updateAlpha: rank offspring with NSGA-II before updating alpha.");
    }
    if (static_cast<int>(offspring[i].eps.size()) != parent_count_)
    {
      throw std::logic_error(
          "AREX::updateAlpha: invalid eps vector size.");
    }
  }

  Population sorted_offspring = offspring;
  std::sort(
      sorted_offspring.individuals().begin(),
      sorted_offspring.individuals().end());

  double sum1 = 0.0;
  double sum2 = 0.0;

  // parent_count_ == dimension + 1 が現在の既定条件。
  const double selected_count = static_cast<double>(parent_count_);

  for (int j = 0; j < parent_count_; ++j)
  {
    double e = 0.0;
    for (int i = 0; i < parent_count_; ++i)
    {
      e += sorted_offspring.at(i).eps[j] / selected_count;
    }
    sum1 += e * e;
    sum2 += e;
  }

  sum2 = (sum2 * sum2) / selected_count;

  const double alpha2 = alpha_ * alpha_;
  const double dimension = static_cast<double>(param.dimension);
  const double L_cdp = alpha2 * dimension * (sum1 - sum2);
  const double L_avg = alpha2 * dimension / selected_count;

  if (!(L_avg > 0.0) || !std::isfinite(L_cdp))
  {
    return;
  }

  const double ratio = std::max(0.0, L_cdp / L_avg);
  const double inside =
      (1.0 - param.learning_rate) + param.learning_rate * ratio;

  if (!(inside >= 0.0) || !std::isfinite(inside))
  {
    return;
  }

  const double next_alpha = alpha_ * std::sqrt(inside);
  if (!std::isfinite(next_alpha))
  {
    return;
  }

  constexpr double alpha_min = 0.5;
  constexpr double alpha_max = 3.0;
  alpha_ = std::clamp(next_alpha, alpha_min, alpha_max);
}
