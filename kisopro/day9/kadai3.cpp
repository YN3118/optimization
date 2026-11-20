#include <cstdio>
#include <cmath>

#define pi 3.14159

void polygon2(double r, int n)
{
  // 例外処理
  if (n < 3 || n > 12)
  {
    printf("error: nが不正です\n");
    return;
  }
  double x[12], y[12];
  // 座標計算
  for (int i = 0; i < n; i++)
  {
    x[i] = r * cos(2 * pi * i / n);
    y[i] = r * sin(2 * pi * i / n);
  }

  // 面積計算
  double area = 0.0;
  for (int i = 0; i < n; i++)
  {
    // (i + 1) % nとすることでx[n] = x[0]となる
    area += (x[i] * y[(i + 1) % n]) - (x[(i + 1) % n] * y[i]);
  }
  area = fabs(area) / 2;
  printf("半径%.2fの内接正%d角形の面積は%.2fである\n", r, n, area);
}

int main()
{
  double r;
  printf("r?");
  scanf("%lf", &r);
  for (int i = 3; i <= 12; i++)
  {
    polygon2(r, i);
  }
  return 0;
}