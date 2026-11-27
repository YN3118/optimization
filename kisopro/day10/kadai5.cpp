#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

double donut(double inner, double outer)
{
  if (inner > outer)
  {
    cout << "value error (inner > outer)" << endl;
    return -1;
  }

  double r = (outer - inner) / 2;
  double s = M_PI * r * r;
  double l = M_PI * (inner + outer);

  return s * l;
}

int main()
{
  double S[2] = {2, 4};
  double M[2] = {3, 6};
  double L[2] = {5, 8};

  char size;
  double v;
  double inner, outer;

  cout << "which size?" << endl;
  cin >> size;

  switch (size)
  {
  case 'S':
    inner = S[0];
    outer = S[1];
    break;
  case 'M':
    inner = M[0];
    outer = M[1];
    break;
  case 'L':
    inner = L[0];
    outer = L[1];
    break;

  default:
    cout << "oazuke" << endl;
    return 0;
  }

  v = donut(inner, outer);
  cout << "inner: " << inner << endl;
  cout << "outer: " << outer << endl;
  cout << "v =    " << v << endl;
  return 0;
}