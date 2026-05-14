#ifndef _RANDOM_H_
#define _RANDOM_H_

#include"parameter.h"
#include"random"

random_device rd;

//0~(母集団サイズ)の整数を一様分布で生成
uniform_real_distribution<> pop(0,param.pop_size);

//平均0，分散1/nの正規分布に従う乱数を生成
normal_distribution<> nomal(0.0,sqrt(1/param.dimension));

//0~1の乱数を生成
uniform_real_distribution<> probabilty(0.0,1.0);

#endif