#include "config.h"

double Hb_theory(double t)
{
  return 1 / sqrt(2 * M_PI * t);
}

int main()
{
  int mode = 0;      // 0:ヘブ学習 1:パーセプトロン学習 2:アダトロン学習
  double step = 0.1; // ステップ幅

  FILE *file;

  // ヘブ学習
  if (mode == 0)
  {
    file = fopen("hb_theory_result.csv", "w");
    fprintf(file, "t,eg\n");

    double t = 0.0;
    while (t <= 10)
    {
      fprintf(file, "%f,%f\n", t, Hb_theory(t));
      t = t + step;
    }
  }
  // パーセプトロン学習
  else if (mode == 1)
  {
    file = fopen("pc_theory_result.csv", "w");
  }
  // アダトロン学習
  else if (mode == 2)
  {
    file = fopen("ad_theory_result.csv", "w");
  }
  else
    return -1;

  return 0;
}