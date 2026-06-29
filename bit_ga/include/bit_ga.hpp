#ifndef BIT_GA_HPP
#define BIT_GA_HPP

#include "population.hpp"
#include "parameter.hpp"
#include "random.hpp"
#include "evaluator.hpp"
#include "nsga2.hpp"

class BitGA
{
public:
  BitGA() = default;

  Population generateOffspring(
      const Population &population,
      const Parameter &param,
      Random &random,
      Evaluator &evaluator,
      const NSGA2 &nsga2) const;

private:
  const Individual &tournamentSelect(
      const Population &population,
      Random &random,
      const NSGA2 &nsga2) const;

  void onePointCrossover(
      const Individual &parent1,
      const Individual &parent2,
      Individual &child1,
      Individual &child2,
      const Parameter &param,
      Random &random) const;

  void mutate(
      Individual &individual,
      const Parameter &param,
      Random &random) const;
};

#endif