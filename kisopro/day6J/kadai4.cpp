#include <cstdio>

int main()
{
  char moji[5][5] = {0};
  char temp = 65; // AのASCIIコード
  printf("%c\n", moji[0][0]);

  for (int i = 0; i < 5; i++)
  {
    moji[i][0] = temp;
    printf("%c\t", moji[i][0]);
    for (int j = 1; j < 5; j++)
    {
      moji[i][j] = moji[i][j - 1] + 1;
      printf("%c\t", moji[i][j]);
    }
    printf("\n");
    temp = moji[i][4] + 1;
  }

  int row, column;
  printf("行?");
  scanf("%d", &row);
  if (row <= -1 || 5 <= row)
  {
    printf("行の値が不正です\n");
    return -1;
  }
  printf("列?");
  scanf("%d", &column);
  if (column <= -1 || 5 <= column)
  {
    printf("列の値が不正です\n");
    return -1;
  }

  printf("moji[%d][%d] = %c\n", row, column, moji[row][column]);
  return 0;
}