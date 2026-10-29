#include<cstdio>

int main()
{
  char s[] = "engineering";
  char t[] = "SCIENCE";

  int i = 0;
  while(s[i] != 0)
  {
    s[i] = s[i] - 32;
    i++;
  }

  printf("SCHOOL OF %s %s\n", s, t);
  return 0;
}