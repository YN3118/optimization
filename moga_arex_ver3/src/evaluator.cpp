#include "evaluator.hpp"
#include "wfg.h"

#include <cmath>
#include <stdexcept>
#include <string>

// コンストラクタ
void Evaluator::evaluate(Individual &individual, const Parameter &param)
{
  // 評価処理
  evaluation_count_++;

  if (contain(param.fn, "WFG") || contain(param.fn, "I"))
  {
    evaluateWFG(individual, param);
    return;
  }

  if (param.fn == "ZDT1")
  {
    evaluateZDT1(individual);
    return;
  }

  if (param.fn == "ZDT2")
  {
    evaluateZDT2(individual);
    return;
  }

  if (param.fn == "ZDT3")
  {
    evaluateZDT3(individual);
    return;
  }

  if (param.fn == "ZDT4")
  {
    evaluateZDT4(individual);
    return;
  }

  if (param.fn == "ZDT6")
  {
    evaluateZDT6(individual);
    return;
  }

  if (param.fn == "KUR")
  {
    evaluateKUR(individual);
    return;
  }

  throw invalid_argument(
      "Evaluator::evaluate: unsupported function " + param.fn);
}

// WFG関数の評価
void Evaluator::evaluateWFG(Individual &individual, const Parameter &param)
{
  individual.f = problem_calc_fitness(individual.x, param.k, param.M, param.fn);
  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}

// ZDT1
void Evaluator::evaluateZDT1(Individual &individual)
{
  const int n = individual.dimension();
  double f1 = individual.x[0];
  double g = 0.0;
  for (int i = 1; i < n; i++)
  {
    g += individual.x[i];
  }

  g = 1.0 + 9.0 * g / static_cast<double>(n - 1);

  double h = 1.0 - sqrt(f1 / g);

  individual.f[0] = f1;
  individual.f[1] = g * h;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}
// ZDT2
void Evaluator::evaluateZDT2(Individual &individual)
{
  const int n = individual.dimension();
  double f1 = individual.x[0];
  double g = 0.0;
  for (int i = 1; i < n; i++)
  {
    g += individual.x[i];
  }

  g = 1.0 + 9.0 * g / static_cast<double>(n - 1);

  double h = 1.0 - pow(f1 / g, 2.0);

  individual.f[0] = f1;
  individual.f[1] = g * h;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}
// ZDT3
void Evaluator::evaluateZDT3(Individual &individual)
{
  const int n = individual.dimension();
  double f1 = individual.x[0];
  double g = 0.0;
  for (int i = 1; i < n; i++)
  {
    g += individual.x[i];
  }

  g = 1.0 + 9.0 * g / static_cast<double>(n - 1);

  double ratio = f1 / g;
  double h = 1.0 - sqrt(ratio) - ratio * sin(10.0 * M_PI * f1);

  individual.f[0] = f1;
  individual.f[1] = g * h;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}
// ZDT4
void Evaluator::evaluateZDT4(Individual &individual)
{
  const int n = individual.dimension();
  double f1 = individual.x[0];
  double g = 1.0 + 10.0 * static_cast<double>(n - 1);
  for (int i = 1; i < n; i++)
  {
    g += individual.x[i] * individual.x[i] - 10.0 * cos(4.0 * M_PI * individual.x[i]);
  }

  double h = 1.0 - sqrt(f1 / g);

  individual.f[0] = f1;
  individual.f[1] = g * h;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}
// ZDT6
void Evaluator::evaluateZDT6(Individual &individual)
{
  const int n = individual.dimension();
  double x1 = individual.x[0];
  double f1 = 1.0 - exp(-4.0 * x1) * pow(sin(6.0 * M_PI * x1), 6.0);
  double sum = 0.0;
  for (int i = 1; i < n; i++)
  {
    sum += individual.x[i];
  }

  double g = 1.0 + 9.0 * pow(sum / static_cast<double>(n - 1), 0.25);

  double h = 1.0 - pow(f1 / g, 2.0);

  individual.f[0] = f1;
  individual.f[1] = g * h;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}

// KUR
void Evaluator::evaluateKUR(Individual &individual)
{
  const int n = individual.dimension();
  double f1 = 0.0;
  double f2 = 0.0;
  for (int i = 0; i < n - 1; i++)
  {
    f1 += -10 * exp(-0.2 * sqrt(pow(individual.x[i], 2) + pow(individual.x[i + 1], 2)));
  }
  for (int i = 0; i < n; i++)
  {
    f2 += pow(abs(individual.x[i]), 0.8) + 5 * sin(pow(individual.x[i], 3));
  }
  individual.f[0] = f1;
  individual.f[1] = f2;

  individual.constraint_violation = 0.0;
  individual.evaluated = true;
}

// 評価回数表示
int Evaluator::evaluation_Count() const
{
  return evaluation_count_;
}