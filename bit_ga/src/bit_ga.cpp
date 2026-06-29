#include "bit_ga.hpp"

#include <algorithm>

const Individual &BitGA::tournamentSelect(
    const Population &population,
    Random &random,
    const NSGA2 &nsga2) const
{
  int a = random.uniformInt(0, population.size() - 1);
  int b = random.uniformInt(0, population.size() - 1);

  const Individual &ind_a = population[a];
  const Individual &ind_b = population[b];

  if (nsga2.isBetter(ind_a, ind_b))
  {
    return ind_a;
  }

  return ind_b;
}

void BitGA::onePointCrossover(
    const Individual &parent1,
    const Individual &parent2,
    Individual &child1,
    Individual &child2,
    const Parameter &param,
    Random &random) const
{
  const int n_bits = param.total_bits;

  child1.bits = parent1.bits;
  child2.bits = parent2.bits;

  if (n_bits < 2)
  {
    return;
  }

  if (!random.bernoulli(param.crossover_rate))
  {
    return;
  }

  int point = random.uniformInt(1, n_bits - 1);

  for (int i = point; i < n_bits; ++i)
  {
    swap(child1.bits[i], child2.bits[i]);
  }

  child1.resetEvaluationInfo();
  child2.resetEvaluationInfo();
}

void BitGA::mutate(
    Individual &individual,
    const Parameter &param,
    Random &random) const
{
  for (int i = 0; i < param.total_bits; ++i)
  {
    if (random.bernoulli(param.mutationrate))
    {
      individual.bits[i] = 1 - individual.bits[i];
    }
  }

  individual.resetEvaluationInfo();
}

Population BitGA::generateOffspring(
    const Population &population,
    const Parameter &param,
    Random &random,
    Evaluator &evaluator,
    const NSGA2 &nsga2) const
{
  Population offspring;
  offspring.reserve(param.pop_size);

  while (offspring.size() < param.pop_size)
  {
    const Individual &parent1 =
        tournamentSelect(population, random, nsga2);

    const Individual &parent2 =
        tournamentSelect(population, random, nsga2);

    Individual child1(
        param.dimension,
        param.objectiveCount(),
        param.total_bits);

    Individual child2(
        param.dimension,
        param.objectiveCount(),
        param.total_bits);

    onePointCrossover(
        parent1,
        parent2,
        child1,
        child2,
        param,
        random);

    mutate(child1, param, random);
    mutate(child2, param, random);

    evaluator.evaluate(child1, param);
    offspring.push_Back(move(child1));

    if (offspring.size() < param.pop_size)
    {
      evaluator.evaluate(child2, param);
      offspring.push_Back(move(child2));
    }
  }

  return offspring;
}