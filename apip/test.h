#ifndef _TEST_H_
#define _TEST_H_

#include"indiv.h"

//teacherとstudentが同符号になる回数をカウント
void Test(vector<double> &t,vector<double> &s,FILE *file,vector<vector<double>> &test_data){
  int correct=0;
  for(int i=0;i<param.test_count;i++){
    double teacher=func::cal_mul(t,test_data[i]);
    double student=func::cal_mul(s,test_data[i]);
    if((teacher>=0&&student>=0)||(teacher<0&&student<0)) correct+=1;
  }

  double a=func::cal_norm(t);
  double b=func::cal_norm(s);
  double cosR=(func::cal_mul(t,s))/(a*b);
  double error=1.0-(correct*1.0/param.test_count);

  fprintf(file,"%f,%f\n",cosR,error);

}

#endif