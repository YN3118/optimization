#ifndef _ADATRON_H_
#define _ADATRON_H_
#include"indiv.h"
#include"test.h"

class Adatron{
  public:
  Indiv teacher;
  Indiv student;
  double J0;

  Adatron(Indiv &t,Indiv &s,double first_norm){
    teacher=t;
    student=s;
    J0=first_norm;
  }

  void execute(){
    //入力ベクトルxを生成(平均0，分散1/Nの正規分布に従う)
    vector<double> x(param.dimension);
    normal_distribution<> input(0.0,1.0/param.dimension);
    for(int i=0;i<x.size();i++){
      x[i]=input(gen);
    }

    double v=func::cal_mul(teacher.x,x);
    double l=func::cal_norm(student.x)/J0;
    double u=func::cal_mul(student.x,x)/l;
    double f=-u*func::step(-u*func::sgn(v));

    //生徒のベクトル更新
    vector<double> temp(param.dimension);
    temp=func::cal_sum(student.x,func::cal_constmul(f,x));
    student.x=move(temp);
    student.m+=1;

  }
};
#endif