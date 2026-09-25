#include "sa.hpp"

void SA::sa_execute(const Population &population, const Parameter &param, Random &random)
{
  Population sa_pop;
  sa_pop.reserve(param.c_size);
  sa_pop = population;

  // 集団から個体をランダムに一つ選択
  int target = random.uniformInt(0,param.pop_size);
  // 変化させる要素を選択
}