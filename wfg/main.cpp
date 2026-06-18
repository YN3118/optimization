#include <ctime>
#include "parameter.hpp"
#include "random.hpp"

int main(int argc, char *argv[])
{
  Parameter param;
  param.load(argc, argv);

  unsigned int seed;

  // シード値-1ならランダム値
  if (param.seed == -1)
  {
    seed = static_cast<unsigned int>(time(nullptr));
  }
  else
  {
    seed = static_cast<unsigned int>(param.seed);
  }

  // Randomクラス呼び出し
  Random random(seed);
}