#ifndef _POPULATION_CPP_
#define _POPULATION_CPP_

#include "population.hpp"

// デフォルトコンストラクタ
Population::Population() {}
// コンストラクタ
Population::Population(int population_size, const Parameter &param, Random &random)
{
  initialize(population_size, param, random);
}

//初期化
void Population::initialize(int population_size, const Parameter &param, Random &random){
  if(population_size<0){

  }
}
#endif