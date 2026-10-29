#include <cstdio>

int main()
{
  int row, column;

  for (row = 1; row <= 9; row++)
  {
    for (column = 1; column <= 9; column++)
    {
      printf("%d\t", row * column);
    }
    printf("\n");
  }
  return 0;
}