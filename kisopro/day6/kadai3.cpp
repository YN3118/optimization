#include <cstdio>

int main()
{
  int a[12] = {0};
  int d;

  printf("初期値?");
  scanf("%d", &a[0]);
  printf("差?");
  scanf("%d", &d);

  for (int i = 0; i < 12; i++)
  {
    if (i < 8)
    {
      a[i] = a[0] + d * i;
    }
    printf("a[%d] = %d\n", i, a[i]);
  }
  return 0;
}