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
    int trial;          //試行回数
    string filename;    //出力ファイル名

    // 定数
    double mutationrate;
    double min_value;   //設計変数の最小値
    double max_value;   //設計変数の最大値

    // コンストラクタ
    Parameter() {
        dimension=5;
        pop_size=100;
        max_gen=1;
        f_num=1;
        mutationrate=0.0;
        max_value=5.12;
        min_value=-5.12;
        seed=-1;
        orconstraint=1;
        trial=1;
        filename="result.csv";
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
            else if(arg=="-t"){ //試行回数
                if(i+1<argc){
                    trial=atoi(argv[i+1]);
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
        c_size=4*dimension;

        //関数毎に定義域を変更
        //Rosenbrock
        if(f_num==0){
            min_value=-5.0;
            max_value=5.0;
        }
        //Rastrigin
        else if(f_num==1){
            min_value=-5.12;
            max_value=5.12;
        }
        //Sphere
        else if(f_num==2){
            min_value=-1.0e9;
            max_value=1.0e9;
        }
        //Ackley
        else if(f_num==3){
            min_value=-32.768;
            max_value=32.768;
        }
        //Schwefel
        else if(f_num==4){
            min_value=-500.0;
            max_value=500.0;
        }
        //Rosenbrock_chain
        else if(f_num==5){
            min_value=-5.0;
            max_value=5.0;
        }
        //Ellipsoid
        else if(f_num==6){
            min_value=-5.12;
            max_value=5.12;
        }
        //Bohaxhevsky
        else if(f_num==7){
            min_value=-5.12;
            max_value=5.12;
        }
        //Griewank
        else if(f_num==8){
            min_value=-300.0;
            max_value=300.0;
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
        printf("seed      : %d\n",seed);
        printf("constraint: %d\n",orconstraint);
        printf("trial num : %d\n",trial);
        printf("output filename: %s\n",filename.c_str());
        printf("--------------------------\n");
    }

    // ヘルプ表示用
    void showHelp() {
        printf("Usage: ./main [options]\n");
        printf("Options:\n");
        printf("  -d <int>   Set dimension (default: 5)\n");
        printf("  -p <int>   Set population size (default: 100)\n");
        printf("  -g <int>   Set max generation (default: 1)\n");
        printf("  -o <name>  Set output filename (default: result.csv)\n");
        printf("  -c <int>   Set constraint (0: off, 1: on)\n");
        printf("  -t <int>   Set trial num\n");
        printf("  -f <int>   Set function ID\n");
        printf("             0:Rosenbrock, 1:Rastrigin, 2:Sphere, 3:Ackley\n");
        printf("             4:Schwefel, 5:Rosenbrock_chain, 6:Ellipsoid, 7:Bohaxhevsky\n");
        printf("             8:Griewank\n");
        printf("  -h         Show this help message\n");
    }

};

// グローバル変数として宣言（実体は main.cpp に置く）
extern Parameter param;

#endif