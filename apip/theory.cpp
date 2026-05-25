#include "config.h"
#define step 0.001

// ヘブ学習(厳密解の式に書き換える！！！)
double Hb_theory(double t)
{
  double R1 = sqrt(2.0 / M_PI) * t;
  double R2 = R1 * sqrt(1.0 + (M_PI / (2.0 * t)) + (M_PI / (2.0 * pow(t, 2))));
  return acos(R1 / R2) / M_PI;
}

// パーセプトロン学習
double Pc_dldt(const double &R, const double &l)
{
  double result1 = (R - 1.0) / sqrt(2.0 * M_PI);
  double result2 = (acos(R)) / (2.0 * M_PI * l);
  return result1 + result2;
}
double Pc_dRldt(const double &l, const double &R)
{
  return (1.0 - R) / sqrt(2.0 * M_PI);
}
double Pc_dRdt(const double &l, const double &R)
{
  double result1 = Pc_dRldt(l, R);
  double result2 = R * Pc_dldt(R, l);
  return (result1 - result2) / l;
}

// アダトロン学習
double Ad_dldt(const double &R, const double &l)
{
  double result1 = R * sqrt(1.0 - pow(R, 2));
  double result2 = acos(R);
  return (2.0 * l - 1.0) * (result1 - result2) / (2.0 * M_PI * l);
}
double Ad_dRldt(const double &l, const double &R)
{
  double result1 = pow((1.0 - pow(R, 2)), 3.0 / 2) / M_PI;
  double result2 = R * sqrt(1.0 - pow(R, 2));
  double result3 = acos(R);
  return result1 + (R * (result2 - result3) / M_PI);
}
double Ad_dRdt(const double &l, const double &R)
{
  double result1 = Ad_dRldt(l, R);
  double result2 = R * Ad_dldt(R, l);
  return (result1 - result2) / l;
}

// 関数ポインタの定義
typedef double (*FUNC)(const double &a, const double &b);

// 4次のルンゲクッタ法
double Runge_Kutta(FUNC f, const double &x, const double &y)
{
  double k1 = step * f(x, y);
  double k2 = step * f(x + (step / 2), y + (k1 / 2));
  double k3 = step * f(x + (step / 2), y + (k2 / 2));
  double k4 = step * f(x + (step / 2), y + k3);
  return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
}

int main(int argc, char *argv[])
{
  int mode = 0; // 0:ヘブ学習 1:パーセプトロン学習 2:アダトロン学習
  FILE *file;
  double t = 0.0;
  double l = 1.0;
  double R = 0.0;
  double max_t = 10.0;

  for (int i = 1; i < argc; i++)
  {
    string arg = argv[i];
    // モード設定
    if (arg == "-m")
    {
      if (i + 1 < argc)
      {
        mode = atoi(argv[i + 1]);
        i++;
      }
    }
    // 時間設定
    else if (arg == "-t")
    {
      if (i + 1 < argc)
      {
        max_t = atof(argv[i + 1]);
        i++;
      }
    }
  }
  // 関数ポインタ
  vector<FUNC> f_list;
  f_list.push_back(Pc_dldt);
  f_list.push_back(Pc_dRdt);
  f_list.push_back(Ad_dldt);
  f_list.push_back(Ad_dRdt);

  // ヘブ学習
  if (mode == 0)
  {
    file = fopen("hb_theory_result.csv", "w");
    fprintf(file, "t,eg\n");
    while (t <= max_t)
    {
      fprintf(file, "%f,%f\n", t, Hb_theory(t));
      t = t + step;
    }
  }
  // パーセプトロン学習
  else if (mode == 1)
  {
    file = fopen("pc_theory_result.csv", "w");
    fprintf(file, "t,l,R,eg\n");
    while (t <= max_t)
    {

      double next_l = Runge_Kutta(f_list[0], R, l);
      double next_R = Runge_Kutta(f_list[1], l, R);
      fprintf(file, "%f,%f,%f,%f\n", t, l, R, (acos(R)) / M_PI);
      l = next_l;
      R = next_R;
      t = t + step;
      printf("\rProgress: [%f/%f] ", t, max_t);
      fflush(stdout);
    }
  }
  // アダトロン学習
  else if (mode == 2)
  {
    file = fopen("ad_theory_result.csv", "w");
    fprintf(file, "t,l,R,eg\n");
    while (t <= max_t)
    {
      double next_l = Runge_Kutta(f_list[2], R, l);
      double next_R = Runge_Kutta(f_list[3], l, R);
      fprintf(file, "%f,%f,%f,%f\n", t, l, R, (acos(R)) / M_PI);
      l = next_l;
      R = next_R;
      t = t + step;
      printf("\rProgress: [%f/%f] ", t, max_t);
      fflush(stdout);
    }
  }
  else
  {
    cout << "mode error" << endl;
    return -1;
  }
  cout << endl;
  return 0;
}