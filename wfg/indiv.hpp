#ifndef _INDIV_HPP_
#define _INDIV_HPP_
#include "config.hpp"

class Indiv{
  public:
  vector<double> x; //設計変数ベクトル
  vector<double> f; //目的関数

  //NSGA2用の変数
  int rank; //ランク
  double cd; //混雑距離
  int dominant; //支配数

  //AREX用の変数
  vector<double> eps;
  

};


#endif
