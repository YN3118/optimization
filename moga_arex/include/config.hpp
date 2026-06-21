#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_
#include <random>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <stdexcept>

using namespace std;

extern mt19937 gen;
#define pi 3.14

// 文字列発見器
inline bool contain(const string &s, const string &key)
{
  return s.find(key) != std::string::npos;
}

inline void toUpper(string &s) // 小文字を大文字に変換
{
  transform(
      s.begin(),
      s.end(),
      s.begin(),
      [](unsigned char c)
      {
        return toupper(c);
      });
}

#endif