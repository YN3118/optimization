#ifndef _PARAMETER_CPP_
#define _PARAMETER_CPP_

#include "parameter.hpp"

Parameter::Parameter()
    : dimension(10),
      pop_size(120),
      max_gen(2000),
      p_size(0),
      c_size(0),
      seed(-1),
      orconstraint(0),
      filename("result.csv"),
      fn("WFG1"),
      mutationrate(-1.0),
      min_value(dimension, 0.0),
      max_value(dimension, 0.0),
      learning_rate(0.0),
      snapshot_interval(100),
      M(2),
      k(4),
      l(20)
{
}

void Parameter::load(int argc, char **argv)
{
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];

    auto requireValue = [&](const std::string &option)
    {
      if (i + 1 >= argc)
      {
        throw std::invalid_argument("Missing value for option " + option);
      }
    };

    if (arg == "-d")
    {
      requireValue(arg);
      dimension = std::atoi(argv[++i]);
    }
    else if (arg == "-p")
    {
      requireValue(arg);
      pop_size = std::atoi(argv[++i]);
    }
    else if (arg == "-g")
    {
      requireValue(arg);
      max_gen = std::atoi(argv[++i]);
    }
    else if (arg == "-o")
    {
      requireValue(arg);
      filename = argv[++i];
    }
    else if (arg == "-s")
    {
      requireValue(arg);
      seed = std::atoi(argv[++i]);
    }
    else if (arg == "-c")
    {
      requireValue(arg);
      orconstraint = std::atoi(argv[++i]);
    }
    else if (arg == "-M")
    {
      requireValue(arg);
      M = std::atoi(argv[++i]);
    }
    else if (arg == "-k")
    {
      requireValue(arg);
      k = std::atoi(argv[++i]);
    }
    else if (arg == "-l")
    {
      requireValue(arg);
      l = std::atoi(argv[++i]);
    }
    else if (arg == "-fn")
    {
      requireValue(arg);
      fn = argv[++i];
      toUpper(fn);
    }
    else if (arg == "-mr")
    {
      requireValue(arg);
      mutationrate = std::atof(argv[++i]);
    }
    else if (arg == "-snap")
    {
      requireValue(arg);
      snapshot_interval = std::atoi(argv[++i]);
    }
    else if (arg == "-h" || arg == "--help")
    {
      showHelp();
      std::exit(0);
    }
    else
    {
      throw std::invalid_argument("Unknown option: " + arg);
    }
  }

  calcDerived();
}

void Parameter::calcDerived()
{
  if (contain(fn, "WFG"))
  {
    dimension = k + l;
  }

  if (dimension <= 0)
  {
    throw std::invalid_argument("dimension must be positive.");
  }
  if (pop_size <= 0)
  {
    throw std::invalid_argument("population size must be positive.");
  }
  if (max_gen <= 0)
  {
    throw std::invalid_argument("max generation must be positive.");
  }

  p_size = dimension + 1;
  c_size = pop_size - p_size;

  if (c_size < p_size)
  {
    throw std::invalid_argument(
        "population size must satisfy pop_size >= 2 * (dimension + 1). ");
  }

  // 未指定時は遺伝子ごとに1/dimension。
  if (mutationrate < 0.0)
  {
    mutationrate = 1.0 / static_cast<double>(dimension);
  }
  if (mutationrate < 0.0 || mutationrate > 1.0)
  {
    throw std::invalid_argument("mutation rate must be in [0, 1].");
  }

  min_value.resize(dimension);
  max_value.resize(dimension);
  learning_rate = 1.0 / (20.0 * static_cast<double>(dimension));
  setBounds();
}

void Parameter::setBounds()
{
  if (contain(fn, "WFG"))
  {
    for (int i = 0; i < dimension; ++i)
    {
      min_value[i] = 0.0;
      max_value[i] = 2.0 * static_cast<double>(i + 1);
    }
  }
  else if (fn == "ZDT4")
  {
    min_value[0] = 0.0;
    max_value[0] = 1.0;
    for (int i = 1; i < dimension; ++i)
    {
      min_value[i] = -5.0;
      max_value[i] = 5.0;
    }
  }
  else if (fn == "ZDT1" || fn == "ZDT2" ||
           fn == "ZDT3" || fn == "ZDT6")
  {
    for (int i = 0; i < dimension; ++i)
    {
      min_value[i] = 0.0;
      max_value[i] = 1.0;
    }
  }
  else
  {
    throw std::invalid_argument("Unsupported function: " + fn);
  }
}

int Parameter::objectiveCount() const
{
  return contain(fn, "WFG") ? M : 2;
}

void Parameter::echo()
{
  std::printf("--- Parameter Settings ---\n");
  std::printf("Dimension : %d\n", dimension);
  std::printf("Pop Size  : %d\n", pop_size);
  std::printf("Max Gen   : %d\n", max_gen);
  std::printf("Function  : %s\n", fn.c_str());
  std::printf("p_size    : %d\n", p_size);
  std::printf("c_size    : %d\n", c_size);
  std::printf("mut_rate  : %f\n", mutationrate);
  std::printf("seed      : %d\n", seed);
  std::printf("constraint: %d\n", orconstraint);
  std::printf("output filename: %s\n", filename.c_str());
  std::printf("--------------------------\n");
}

void Parameter::showHelp()
{
  std::printf("Usage: ./main [options]\n");
  std::printf("Options:\n");
  std::printf("  -d <int>       Set dimension (default: 10)\n");
  std::printf("  -p <int>       Set population size (default: 120)\n");
  std::printf("  -g <int>       Set max generation (default: 2000)\n");
  std::printf("  -o <name>      Set output filename (default: result.csv)\n");
  std::printf("  -s <int>       Set random seed\n");
  std::printf("  -mr <double>   Per-variable mutation rate (default: 1/dimension)\n");
  std::printf("  -snap <int>    Set snapshot interval\n");
  std::printf("  -fn <string>   ZDT1, ZDT2, ZDT3, ZDT4, ZDT6, WFG1-WFG9, I1-I5\n");
  std::printf("  -h, --help     Show this help message\n");
}

#endif
