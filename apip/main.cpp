
#include"parameter.h"
#include"hebbian.h"
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
    fprintf(file,"times,cosR,error\n");

    //初期個体生成
    Indiv t;
    Indiv s;

    double f_a=func::cal_norm(t.x);
    double f_b=func::cal_norm(s.x);
    printf("cosR=%f\n",(func::cal_mul(t.x,s.x)/(f_a*f_b)));

    printf("------teacher-----\n");
    t.echo();
    printf("------------------\n");
    printf("------student-----\n");
    s.echo();
    printf("------------------\n");

    Hebbian hb(t,s);
    //学習実行(一定回数毎にテスト)
    for(int i=0;i<param.max_gen;i++){
      hb.execute();

      if((hb.student.m+1)%param.test_times==0){
        fprintf(file,"%f,",i/1000.0);
        Test(hb.teacher.x,hb.student.x,file);
      }
    }

    printf("------result-------\n");
    hb.student.echo();

    double a=func::cal_norm(t.x);
    double b=func::cal_norm(hb.student.x);
    printf("cosR=%f\n",(func::cal_mul(t.x,hb.student.x)/(a*b)));
    fclose(file);
    return 0;
}