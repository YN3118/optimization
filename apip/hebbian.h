//ヘブ学習
#ifndef _HEBBIAN_H_
#define _HEBBIAN_H_
#include"indiv.h"

class Hebbian{
  public:
  Indiv teacher;
  Indiv student;

  Hebbian(Indiv t,Indiv s){
    teacher=t;
    student=s;
  }

  void execute(){
    //入力ベクトルxを生成(平均0，分散1/Nの正規分布に従う)
    vector<double> x(param.dimension);
    for(int i=0;i<x.size();i++){
      x[i]=func::generateRandomNomal(0.0,1.0/param.dimension);
    }

    double v=func::cal_mul(teacher.x,x);
    int f=func::sgn(v);

    //生徒のベクトル更新
    vector<double> temp(param.dimension);
    temp=func::cal_sum(student.x,func::cal_constmul(f,x));
    student.x=move(temp);
    student.m+=1;
  }
};


#endif