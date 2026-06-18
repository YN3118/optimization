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

  // コンストラクタ
  Population(int population_size, const Parameter &param, Random &random);
  // 初期化
  void initialize(int population_size, const Parameter &param, Random &random);
  // 評価関数
  void evaluateAll(const Parameter &param);
  // 母集団の大きさを返す
  int size() const;
  // 集団が空かどうか
  bool empty() const;

  Individual &at(int index);
  const Individual &at(int index) const;

  Individual &operator[](int index);
  const Individual &operator[](int index) const;

  vector<Individual> &individuals();
  const vector<Individual> &individuals() const;

  // リセット
  void clear();
  // 集団に追加
  void push_back(const Individual &ind);
  void push_back(Individual &&ind); // 二次元ベクトル用

  void reserve(int size);

  void print(ostream &os = cout) const;
};

// 関数の中身はcppファイルに書く
#endif