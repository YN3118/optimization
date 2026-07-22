#include "population.hpp"
#include "evaluator.hpp"

Population::Population() = default;

Population::Population(
    int population_size,
    const Parameter &param,
    Random &random)
{
  initialize(population_size, param, random);
}

void Population::initialize(
    int population_size,
    const Parameter &param,
    Random &random)
{
  if (population_size <= 0)
  {
    throw std::invalid_argument(
        "Population::initialize: population_size must be positive.");
  }

  individuals_.clear();
  individuals_.reserve(population_size);

  for (int i = 0; i < population_size; ++i)
  {
    Individual individual(param.dimension, param.objectiveCount());
    for (int j = 0; j < param.dimension; ++j)
    {
      individual.x[j] = random.uniformReal(
          param.min_value[j], param.max_value[j]);
    }
    individuals_.push_back(std::move(individual));
  }
}

void Population::evaluateAll(
    const Parameter &param,
    Evaluator &evaluator)
{
  for (Individual &individual : individuals_)
  {
    evaluator.evaluate(individual, param);
  }
}

int Population::size() const
{
  return static_cast<int>(individuals_.size());
}

bool Population::empty() const
{
  return individuals_.empty();
}

Individual &Population::at(int index)
{
  if (index < 0 || index >= size())
  {
    throw std::out_of_range("Population::at: index out of range.");
  }
  return individuals_[index];
}

const Individual &Population::at(int index) const
{
  if (index < 0 || index >= size())
  {
    throw std::out_of_range("Population::at: index out of range.");
  }
  return individuals_[index];
}

Individual &Population::operator[](int index)
{
  return individuals_[index];
}

const Individual &Population::operator[](int index) const
{
  return individuals_[index];
}

std::vector<Individual> &Population::individuals()
{
  return individuals_;
}

const std::vector<Individual> &Population::individuals() const
{
  return individuals_;
}

void Population::clear()
{
  individuals_.clear();
}

void Population::reserve(int size)
{
  individuals_.reserve(size);
}

void Population::push_Back(const Individual &individual)
{
  individuals_.push_back(individual);
}

void Population::push_Back(Individual &&individual)
{
  individuals_.push_back(std::move(individual));
}

void Population::print(std::ostream &os) const
{
  for (int i = 0; i < size(); ++i)
  {
    os << "individual " << i << ": ";
    individuals_[i].print(os);
  }
}

Population mergePopulation(const Population &a, const Population &b)
{
  Population merged;
  merged.reserve(a.size() + b.size());

  for (int i = 0; i < a.size(); ++i)
  {
    merged.push_Back(a[i]);
  }
  for (int i = 0; i < b.size(); ++i)
  {
    merged.push_Back(b[i]);
  }
  return merged;
}
