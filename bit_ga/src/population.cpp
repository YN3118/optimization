#include "population.hpp"
#include "evaluator.hpp"

Population::Population()
{
}

// コンストラクタ
Population::Population(int population_size, const Parameter &param, Random &random)
{
  initialize(population_size, param, random);
}

// 初期化
void Population::initialize(int population_size, const Parameter &param, Random &random)
{
  if (population_size <= 0)
  {
    throw invalid_argument("Population::initialize: population_size must be positive.");
  }

  individuals_.clear();
  individuals_.reserve(population_size);

  for (int i = 0; i < population_size; i++)
  {
    Individual individual(param.dimension, param.objectiveCount(), param.total_bits);

    for (int j = 0; j < param.total_bits; j++)
    {
      individual.bits[j] = random.uniformInt(0, 1);
    }

    individuals_.push_back(move(individual));
  }
}

// 評価関数
void Population::evaluateAll(const Parameter &param)
{
  Evaluator evaluator;
  for (auto &individual : individuals_)
  {
    evaluator.evaluate(individual, param);
  }
}

// 母集団の大きさ
int Population::size() const
{
  return static_cast<int>(individuals_.size());
}

// 空かどうか
bool Population::empty() const
{
  return individuals_.empty();
}

// 個体にアクセス
Individual &Population::at(int index)
{
  if (index < 0 || index >= size())
  {
    throw out_of_range("Population::at: index out of range.");
  }

  return individuals_[index];
}

const Individual &Population::at(int index) const
{
  if (index < 0 || index >= size())
  {
    throw out_of_range("Population::at: index out of range.");
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

// 内部のindividualを返す
vector<Individual> &Population::individuals()
{
  return individuals_;
}

const vector<Individual> &Population::individuals() const
{
  return individuals_;
}

// リセット
void Population::clear()
{
  individuals_.clear();
}

void Population::reserve(int size)
{
  individuals_.reserve(size);
}

// 個体を追加
void Population::push_Back(const Individual &individual)
{
  individuals_.push_back(individual);
}

void Population::push_Back(Individual &&individual)
{
  individuals_.push_back(move(individual));
}

void Population::print(ostream &os) const
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
  for (int i = 0; i < a.size(); i++)
  {
    merged.push_Back(a[i]);
  }
  for (int i = 0; i < b.size(); i++)
  {
    merged.push_Back(b[i]);
  }

  return merged;
}