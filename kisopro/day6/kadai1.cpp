#include <cstdio>
int main()
{
  int a[5];
  int count = 0;
  for (int i = 0; i < 5; i++)
  {
    printf("数字?");
    scanf("%d", &a[i]);
    if (a[i] <= 10)
    {
      count++;
    }
  }

  for (int i = 0; i < 5; i++)
  {
    printf("a[%d] = %d\n", i, a[i]);
  }
  printf("10以下の数は%d個です\n", count);
  return 0;
}