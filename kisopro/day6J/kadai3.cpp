#include <cstdio>

int main()
{
  int a[][4] = {{4, 3, 2, 1}, {8, 7, 6, 5}, {12, 11, 10, 9}, {16, 15, 14, 13}};
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if ((i + j) % 2 == 0)
      {
        a[i][j] = 0;
      }
      printf("%d\t",a[i][j]);
    }
    printf("\n");
  }
  return 0;
}