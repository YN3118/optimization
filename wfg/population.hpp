#ifndef _POPULATION_HPP_
#define _POPULATION_HPP_
#include "config.hpp"
#include "individual.hpp"
#include "parameter.hpp"
#include "random.hpp"

class Population
{
private:
  vector<Individual> individuals_;

public:
  Population();

  Population(
      int population_size,
      const Parameter &param,
      Random &random);

  void initialize(
      int population_size,
      const Parameter &param,
      Random &random);

  void evaluateAll(const Parameter &param);

  int size() const;
  bool empty() const;

  Individual &at(int index);
  const Individual &at(int index) const;

  Individual &operator[](int index);
  const Individual &operator[](int index) const;

  vector<Individual> &individuals();
  const vector<Individual> &individuals() const;

  void clear();

  void push_back(const Individual &ind);
  void push_back(Individual &&ind);

  void reserve(int size);

  void print(ostream &os = cout) const;
};

// 関数の中身はcppファイルに書く
#endif