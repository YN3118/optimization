#ifndef _PARAMETER_CPP_
#define _PARAMETER_CPP_
#include "parameter.hpp"

// コンストラクタ
Parameter::Parameter()
    : dimension(10),
      pop_size(120),
      max_gen(1),
      mutationrate(0),
      seed(-1),
      orconstraint(0),
      filename("result.csv"),
      M(2),
      k(4),
      l(20),
      fn("WFG1"),
      min_value(dimension, 0.0),
      max_value(dimension, 0.0),
      snapshot_interval(100)
{
  // calcDerived();
}

// 変数読み込み
void Parameter::load(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    string arg = argv[i];
    if (arg == "-d")
    { // 次元数
      if (i + 1 < argc)
      {
        dimension = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-p")
    { // 親の数
      if (i + 1 < argc)
      {
        pop_size = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-g")
    { // 終了世代
      if (i + 1 < argc)
      {
        max_gen = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-o")
    { // 出力ファイル名
      filename = argv[i + 1];
      i++;
    }
    else if (arg == "-s")
    { // シード値
      if (i + 1 < argc)
      {
        seed = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-c")
    { // 制約の有無
      if (i + 1 < argc)
      {
        orconstraint = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-M")
    { // WFGの目的関数の数
      if (i + 1 < argc)
      {
        M = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-k")
    { // WFGのk
      if (i + 1 < argc)
      {
        k = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-l")
    { // WFGのl
      if (i + 1 < argc)
      {
        l = atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-fn")
    { // 関数の種類
      fn = argv[i + 1];
      i++;
      toUpper(fn);
    }
    else if (arg == "-snap")
    {
      if (i + 1 < argc)
      {
        snapshot_interval = std::atoi(argv[i + 1]);
        i++;
      }
    }
    else if (arg == "-h" || arg == "--help")
    { // ヘルプ表示
      showHelp();
      exit(0);
    }
  }
  calcDerived();
  // echo();
}

void Parameter::calcDerived()
{
  // WFG関数のときは設計変数の数がkとlで決まる
  if (contain(fn, "WFG"))
  {
    dimension = k + l;
  }
  p_size = dimension + 1;
  c_size = pop_size - p_size;
  min_value.resize(dimension);
  max_value.resize(dimension);
  learning_rate = 1.0 / (20 * dimension);
  setBounds();
}

// 定義域決定
void Parameter::setBounds()
{
  // WFGの定義域（WFG内でスケーリングされているので，この定義域になる．）
  if (contain(fn, "WFG"))
  {

    for (int i = 0; i < dimension; i++)
    {
      min_value[i] = 0.0;
      max_value[i] = 2.0 * (i + 1);
    }
  }
  // ZDT4
  else if (fn == "ZDT4")
  {
    min_value[0] = 0.0;
    max_value[0] = 1.0;
    for (int i = 1; i < dimension; i++)
    {
      min_value[i] = -5.0;
      max_value[i] = 5.0;
    }
  }
  // ZDT1, ZDT2, ZDT3, ZDT6
  else if (fn == "ZDT1" || fn == "ZDT2" || fn == "ZDT3" || fn == "ZDT6")
  {
    for (int i = 0; i < dimension; i++)
    {
      min_value[i] = 0.0;
      max_value[i] = 1.0;
    }
  }
  else
  {
    cout << "This function is not defined: " << fn << endl;
    exit(1);
  }
}

// 目的関数の数を返す
int Parameter::objectiveCount() const
{
  if (contain(fn, "WFG"))
  {
    return M;
  }

  // ZDT系なら基本2目的
  if (contain(fn, "ZDT"))
  {
    return 2;
  }

  return 2;
}

// パラメータ表示
void Parameter::echo()
{
  printf("--- Parameter Settings ---\n");
  printf("Dimension : %d\n", dimension);
  printf("Pop Size  : %d\n", pop_size);
  printf("Max Gen   : %d\n", max_gen);
  printf("Function  : %s\n", fn.c_str());
  printf("p_size    : %d\n", p_size);
  printf("c_size    : %d\n", c_size);
  printf("mut_rate  : %f\n", mutationrate);
  printf("seed      : %d\n", seed);
  printf("constraint: %d\n", orconstraint);
  printf("output filename: %s\n", filename.c_str());
  printf("--------------------------\n");
}

// ヘルプ表示
void Parameter::showHelp()
{
  printf("Usage: ./main [options]\n");
  printf("Options:\n");
  printf("  -d  <int>    Set dimension (default: 5)\n");
  printf("  -p  <int>    Set population size (default: 100)\n");
  printf("  -g  <int>    Set max generation (default: 1)\n");
  printf("  -o  <name>   Set output filename (default: result.csv)\n");
  printf("  -c  <int>    Set constraint (0: off, 1: on)\n");
  printf("  -snap<int>   Set snapshot_interval\n");
  printf("  -fn <string> Set function \n");
  printf("               ZDT1, ZDT2, ZDT3, ZDT4, ZDT6\n");
  printf("               WFG1~WFG9\n");
  printf("               I1~I5\n");
  printf("  -h         Show this help message\n");
}

#endif