#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_

#include "config.hpp"
#include "individual.hpp"
#include "parameter.hpp"
#include "random.hpp"

class Evaluator;

class Population
{
private:
  std::vector<Individual> individuals_;

public:
  Population();
  Population(int population_size, const Parameter &param, Random &random);

  void initialize(int population_size, const Parameter &param, Random &random);

  // 評価回数を一元管理するため、mainのEvaluatorを参照で受け取る。
  void evaluateAll(const Parameter &param, Evaluator &evaluator);

  int size() const;
  bool empty() const;

  Individual &at(int index);
  const Individual &at(int index) const;
  Individual &operator[](int index);
  const Individual &operator[](int index) const;

  std::vector<Individual> &individuals();
  const std::vector<Individual> &individuals() const;

  void clear();
  void push_Back(const Individual &ind);
  void push_Back(Individual &&ind);
  void reserve(int size);
  void print(std::ostream &os = std::cout) const;
};

Population mergePopulation(const Population &a, const Population &b);

#endif
