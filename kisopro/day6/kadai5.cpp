#include <cstdio>

int main()
{
  int n;
  printf("購入数を指定してください");
  scanf("%d", &n);

  if (0 <= n && n <= 10)
  {
    printf("割引なしで売値は%d円です\n", 500 * n);
  }
  else if (11 <= n && n <= 30)
  {
    printf("1割引で売値は%d円です\n", 450 * n);
  }
  else if (31 <= n)
  {
    printf("2割引で売値は%d円です\n", 400 * n);
  }
  else
    printf("購入数が不正です\n");

  return 0;
}