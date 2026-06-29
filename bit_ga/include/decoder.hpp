#ifndef DECODER_HPP
#define DECODER_HPP

#include "individual.hpp"
#include "parameter.hpp"

class Decoder
{
public:
  void decode(
      Individual &individual,
      const Parameter &param) const
  {
    const int b = param.bits_per_variable;

    for (int i = 0; i < param.dimension; ++i)
    {
      unsigned int value = 0;

      for (int j = 0; j < b; ++j)
      {
        int index = i * b + j;
        value = (value << 1) | individual.bits[index];
      }

      unsigned int max_int = (1u << b) - 1u;

      double ratio =
          static_cast<double>(value) / static_cast<double>(max_int);

      individual.x[i] =
          param.min_value[i] + ratio * (param.max_value[i] - param.min_value[i]);
    }
  }
};

#endif