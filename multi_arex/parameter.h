#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

class Parameter {
public:
    int dimension;      //次元数
    int pop_size;       //母集団サイズ
    int max_gen;        //最大世代数
    int f_num;          //関数番号
    int p_size;         //親の数
    int c_size;         //子の数
    int seed;           //シード値
    int orconstraint;   //制約条件
    string filename;    //出力ファイル名

    // 定数
    double mutationrate;    
    vector<double> min_value;
    vector<double> max_value;
    double learning_rate;
    
    // コンストラクタ
    Parameter() {
        dimension=10;
        pop_size=120;
        max_gen=1;
        f_num=1;
        mutationrate=0.0;
        seed=-1;
        orconstraint=0;
        filename="result.csv";

        
        min_value.resize(dimension);
        max_value.resize(dimension);
        
        calcDerived(); // 依存変数の計算
    }

    // 引数を読み込んで値を更新する
    void load(int argc,char* argv[]) {
        for (int i=1;i<argc;i++){
            string arg=argv[i];
            if(arg=="-d"){ //次元数
                if(i+1<argc){
                    dimension=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-p"){ //母集団サイズ
                if(i+1<argc){
                    pop_size=atoi(argv[i+1]);
                    i++;
                }
            } 
            else if(arg=="-g"){ //世代数
                if(i+1<argc){
                    max_gen=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-f"){ //関数番号
                if (i+1<argc) {
                    f_num=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-o"){ //ファイル名
                filename=argv[i+1];
                i++;
            }
            else if(arg=="-s"){ //シード値
                if(i+1<argc){
                    seed=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-c"){ //制約条件
                if(i+1<argc){
                    orconstraint=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-h"||arg=="--help"){ //ヘルプ表示
                showHelp();
                exit(0);
            }
        }
        // 値が変わったので再計算
        calcDerived();
        // echo();
    }

    // 次元数などに依存する変数を計算
    void calcDerived() {
        p_size=dimension+1;
        c_size=pop_size-p_size;
        min_value.resize(dimension);
        max_value.resize(dimension);
        learning_rate=1.0/(10*dimension);

        //目的関数毎に定義域を決定
        //ZDT4
        if(f_num==0){
            min_value[0]=0.0;
            max_value[0]=1.0;
            for(int i=1;i<dimension;i++){
                min_value[i]=-5.0;
                max_value[i]=5.0;
            }
        }

        //ZDT1, ZDT2, ZDT3, ZDT6
        if(f_num==1||f_num==2||f_num==3||f_num==4){
            for(int i=0;i<dimension;i++){
                min_value[i]=0.0;
                max_value[i]=1.0;
            }
        }
        
    }

    // 設定値の表示
    void echo() {
        printf("--- Parameter Settings ---\n");
        printf("Dimension : %d\n",dimension);
        printf("Pop Size  : %d\n",pop_size);
        printf("Max Gen   : %d\n",max_gen);
        printf("Function  : %d\n",f_num);
        printf("p_size    : %d\n",p_size);
        printf("c_size    : %d\n",c_size);
        printf("mut_rate  : %f\n",mutationrate);
        printf("seed      : %d\n",seed);
        printf("constraint: %d\n",orconstraint);
        printf("output filename: %s\n",filename.c_str());
        printf("--------------------------\n");
    }

    // ヘルプ表示用
    void showHelp() {
        printf("Usage: ./main [options]\n");
        printf("Options:\n");
        printf("  -d <int>   Set dimension (default: 5)\n");
        printf("  -p <int>   Set population size (default: 100)\n");
        printf("  -g <int>   Set max generation (default: 2000)\n");
        printf("  -o <name>  Set output filename (default: result.csv)\n");
        printf("  -c <int>   Set constraint (0: off, 1: on)\n");
        printf("  -f <int>   Set function ID\n");
        printf("             0:ZDT4, 1:ZDT1, 2:ZDT2, 3:ZDT3, 4:ZDT6\n");
        printf("  -h         Show this help message\n");
    }

};

// グローバル変数として宣言（実体は main.cpp に置く）
extern Parameter param;

#endif