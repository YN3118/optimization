#ifndef _TEST_H_
#define _TEST_H_

#include"indiv.h"

//teacherとstudentが同符号になる回数をカウント
void Test(vector<double> t,vector<double> s,FILE *file){
  int correct=0;
  vector<double> x(param.dimension);
  for(int i=0;i<param.test_count;i++){
    //テスト用の入力を生成
    for(int j=0;j<x.size();j++){
      x[j]=func::generateRandomNomal(0.0,1.0/param.dimension); //入力は平均0，分散1/Nの正規分布に従って生成
    }
    double teacher=func::cal_mul(t,x);
    double student=func::cal_mul(s,x);

    if((teacher>=0&&student>=0)||(teacher<0&&student<0)) correct+=1;
  }

  double a=func::cal_norm(t);
  double b=func::cal_norm(s);
  double cosR=(func::cal_mul(t,s))/(a*b);
  double error=1.0-(correct/param.test_count);

  fprintf(file,"%f,%f\n",cosR,error);

}

#endif