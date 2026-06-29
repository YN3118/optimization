#include "nsga2.hpp"

bool NSGA2::dominates(const Individual &a, const Individual &b) const
{
  // 制約違反量を考慮する場合
  if (a.constraint_violation < b.constraint_violation)
  {
    return true;
  }
  if (a.constraint_violation > b.constraint_violation)
  {
    return false;
  }
  bool strictly_better = false;
  // 目的関数の数だけ調べる
  for (int m = 0; m < a.objectiveCount(); m++)
  {
    if (a.f[m] > b.f[m])
    {
      return false;
    }

    if (a.f[m] < b.f[m])
    {
      strictly_better = true;
    }
  }
  return strictly_better;
}

vector<vector<int>> NSGA2::fastNonDominatedSort(Population &population) const
{
  const int N = population.size();
  vector<vector<int>> dominated_set(N);
  vector<int> domination_count(N, 0);
  vector<vector<int>> fronts;
  vector<int> first_front;
  for (int p = 0; p < N; p++)
  {
    population[p].rank = -1;

    for (int q = 0; q < N; ++q)
    {
      if (p == q)
      {
        continue;
      }

      if (dominates(population[p], population[q]))
      {
        dominated_set[p].push_back(q);
      }
      else if (dominates(population[q], population[p]))
      {
        domination_count[p]++;
      }
    }

    if (domination_count[p] == 0)
    {
      population[p].rank = 0;
      first_front.push_back(p);
    }
  }
  fronts.push_back(first_front);
  int rank = 0;
  while (!fronts[rank].empty())
  {
    vector<int> next_front;
    for (int p : fronts[rank])
    {
      for (int q : dominated_set[p])
      {
        domination_count[q]--;

        if (domination_count[q] == 0)
        {
          population[q].rank = rank + 1;
          next_front.push_back(q);
        }
      }
    }
    rank++;
    if (!next_front.empty())
    {
      fronts.push_back(next_front);
    }
    else
    {
      break;
    }
  }
  return fronts;
}

void NSGA2::assignCrowdingDistance(Population &population, const vector<int> &front) const
{
  const int front_size = static_cast<int>(front.size());
  if (front_size == 0)
  {
    return;
  }
  if (front_size <= 2)
  {
    for (int index : front)
    {
      population[index].crowding_distance =
          numeric_limits<double>::infinity();
    }
    return;
  }
  for (int index : front)
  {
    population[index].crowding_distance = 0.0;
  }
  const int objective_count = population[front[0]].objectiveCount();
  for (int m = 0; m < objective_count; m++)
  {
    vector<int> sorted_front = front;
    sort(sorted_front.begin(), sorted_front.end(), [&](int a, int b)
              { return population[a].f[m] < population[b].f[m]; });

    const double f_min = population[sorted_front.front()].f[m];
    const double f_max = population[sorted_front.back()].f[m];

    // 端の個体の距離は無限大に設定
    population[sorted_front.front()].crowding_distance = numeric_limits<double>::infinity();
    population[sorted_front.back()].crowding_distance = numeric_limits<double>::infinity();

    if (f_max == f_min)
    {
      continue;
    }

    for (int i = 1; i < front_size - 1; i++)
    {
      const int current = sorted_front[i];
      const int previous = sorted_front[i - 1];
      const int next = sorted_front[i + 1];

      population[current].crowding_distance +=
          (population[next].f[m] - population[previous].f[m]) / (f_max - f_min);
    }
  }
}

bool NSGA2::isBetter(const Individual &a, const Individual &b) const
{
  if (a.rank != b.rank)
  {
    return a.rank < b.rank;
  }

  return a.crowding_distance > b.crowding_distance;
}

Population NSGA2::environmentalSelection(Population &combined, int next_population_size) const
{
  if (next_population_size <= 0)
  {
    throw invalid_argument(
        "NSGA2::environmentalSelection: next_population_size must be positive.");
  }
  vector<vector<int>> fronts = fastNonDominatedSort(combined);
  Population next_population;
  next_population.reserve(next_population_size);
  for (const auto &front : fronts)
  {
    if (next_population.size() + static_cast<int>(front.size()) <= next_population_size)
    {
      assignCrowdingDistance(combined, front);

      for (int index : front)
      {
        next_population.push_Back(combined[index]);
      }
    }
    else
    {
      assignCrowdingDistance(combined, front);
      vector<int> sorted_front = front;
      sort(sorted_front.begin(), sorted_front.end(), [&](int a, int b)
                { return combined[a].crowding_distance > combined[b].crowding_distance; });

      const int remaining = next_population_size - next_population.size();

      for (int i = 0; i < remaining; i++)
      {
        next_population.push_Back(combined[sorted_front[i]]);
      }

      break;
    }
  }

  return next_population;
}