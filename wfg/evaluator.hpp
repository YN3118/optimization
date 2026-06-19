#ifndef _EVALUATOR_HPP_
#define _EVALUATOR_HPP_

#include "individual.hpp"
#include "parameter.hpp"

class Evaluator
{
private:
  int eval_count_; //評価回数

public:
  // デフォルトコンストラクタ
  Evaluator():eval_count_(0){}

  // 評価関数
  void evaluate(Individual &individual, const Parameter &param);

  // WFG関数の評価
  void evaluateWFG(Individual &individual, const Parameter &param);

  // ZDTの評価関数
  void evaluateZDT1(Individual &individual);
  void evaluateZDT2(Individual &individual);
  void evaluateZDT3(Individual &individual);
  void evaluateZDT4(Individual &individual);
  void evaluateZDT6(Individual &individual);

  //評価回数表示
  int evaluation_Count() const;
};
#endif