
#include"parameter.h"
#include"hebbian.h"
#include"perceptron.h"
#include"adatron.h"
#include<ctime>

Parameter param;


int main(int argc,char* argv[]){
    param.load(argc,argv);
    unsigned int seed;

    if(param.seed==-1){
        seed=(unsigned int)time(NULL);
    }
    else seed=(unsigned int)param.seed;
    gen.seed(seed);

    //ファイル書き込み
    FILE *file;
    file=fopen(param.filename.c_str(),"w");
    if(file==NULL){
        printf("Cannot open file %s\n",param.filename.c_str());
        return -1;
    }
    fprintf(file,"dimension,%d,seed,%d\n,mode,",param.dimension,param.seed);
    if(param.mode==0)      fprintf(file,"hebbian\n");
    else if(param.mode==1) fprintf(file,"perceptron\n");
    else if(param.mode==2) fprintf(file,"adatron\n");
    fprintf(file,"times,cosR,error\n");

    //初期個体生成
    Indiv t;
    Indiv s;
    double J0=func::cal_norm(s.x);
    double f_a=func::cal_norm(t.x);
    double f_b=func::cal_norm(s.x);
    printf("cosR=%f\n",(func::cal_mul(t.x,s.x)/(f_a*f_b)));

    //テストデータ生成
    vector<vector<double>> test_data(param.test_count,vector<double>(param.dimension));
    normal_distribution<> test(0.0,sqrt(1.0/param.dimension));
    for(int i=0;i<test_data.size();i++){
      for(int j=0;j<test_data[i].size();j++){
        test_data[i][j]=test(gen);
      }
    }

    double time=0.0;
    fprintf(file,"%f,",time);
    Test(t.x,s.x,file,test_data);

    //ヘブ学習
    if(param.mode==0){
      Hebbian lm(t,s);
      for(int i=0;i<param.max_gen;i++){
        lm.execute();
        if((lm.student.m)%param.test_times==0){
          time+=0.1;
          fprintf(file,"%f,",time);
          Test(lm.teacher.x,lm.student.x,file,test_data);
        }
        printf("\r %d / %d ",i+1,param.max_gen);
        fflush(stdout);
      }
      double a=func::cal_norm(t.x);
      double b=func::cal_norm(lm.student.x);
      double cosR=(func::cal_mul(t.x,lm.student.x)/(a*b));
      printf("\n------result-------\n");
      printf("cosR=%f\n",cosR);
    }
    //パーセプトロン 
    else if(param.mode==1){
      Perceptron lm(t,s,J0);
      for(int i=0;i<param.max_gen;i++){
        lm.execute();
        if((lm.student.m)%param.test_times==0){
          time+=0.1;
          fprintf(file,"%f,",time);
          Test(lm.teacher.x,lm.student.x,file,test_data);
        }
        printf("\r %d / %d ",i+1,param.max_gen);
        fflush(stdout);
      }
      double a=func::cal_norm(t.x);
      double b=func::cal_norm(lm.student.x);
      double cosR=(func::cal_mul(t.x,lm.student.x)/(a*b));
      printf("\n------result-------\n");
      printf("cosR=%f\n",cosR);
    }
    //アダトロン学習
    else if(param.mode==2){
      Adatron lm(t,s,J0);
      for(int i=0;i<param.max_gen;i++){
        lm.execute();
        if((lm.student.m)%param.test_times==0){
          time+=0.1;
          fprintf(file,"%f,",time);
          Test(lm.teacher.x,lm.student.x,file,test_data);
        }
        printf("\r %d / %d ",i+1,param.max_gen);
        fflush(stdout);
      }
      double a=func::cal_norm(t.x);
      double b=func::cal_norm(lm.student.x);
      double cosR=(func::cal_mul(t.x,lm.student.x)/(a*b));
      printf("\n------result-------\n");
      printf("cosR=%f\n",cosR);
    } 
    param.echo();
    fclose(file);
    return 0;
}