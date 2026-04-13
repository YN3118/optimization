//個体クラス
#ifndef _INDIV_H_
#define _INDIV_H_
#include"function.h"

namespace func=Function;

class Indiv{
  public:
  //要素
  vector<double> x; //個体のベクトル
  int m;            //世代数

  //コンストラクタ
  //要素は平均0，分散1の正規分布に従って生成
  Indiv(){
    x.resize(param.dimension);
    for(int i=0;i<x.size();i++){
      x[i]=func::generateRandomNomal(0.0,1.0);
    }
    m=0;
  }

  void echo(){
    for(int i=0;i<x.size();i++){
      printf("x[%d]=%f\t",i,x[i]);
    }
    printf("\n");
  }
};

#endif