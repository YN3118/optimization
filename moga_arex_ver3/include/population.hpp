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

  // 個体にアクセス
  Individual &at(int index);
  const Individual &at(int index) const;
  Individual &operator[](int index);
  const Individual &operator[](int index) const;

  vector<Individual> &individuals();
  const vector<Individual> &individuals() const;

  // リセット
  void clear();

  // 集団に追加
  void push_Back(const Individual &ind);
  void push_Back(Individual &&ind); // 二次元ベクトル用

  // メモリを先に確保（resizeと同じ役割）
  void reserve(int size);

  // 集団の個体をすべて表示
  void print(ostream &os = cout) const;
};

// 二つの集団をくっつける
Population mergePopulation(const Population &a, const Population &b);

// 関数の中身はcppファイルに書く
#endif