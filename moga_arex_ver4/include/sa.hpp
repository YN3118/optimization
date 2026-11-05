#ifndef _SA_HPP_
#define _SA_HPP_

#include <vector>

#include "population.hpp"
#include "individual.hpp"
#include "parameter.hpp"
#include "random.hpp"
#include "evaluator.hpp"
#include "nsga2.hpp"

class SA
{
  public:
  void sa_execute(const Population &population, const Parameter &param, Random &random);
};


#endif