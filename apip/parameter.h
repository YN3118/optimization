#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include"config.h"

using namespace std;

class Parameter {
public:
    int dimension;      //次元数
    int max_gen;        //最大世代数
    int seed;           //シード値
    string filename;    //出力ファイル名
    int test_times;     //いつテストするか
    int test_count;     //テスト回数
    int mode;           //学習法


    
    // コンストラクタ
    Parameter() {
        dimension=10;
        max_gen=1;
        seed=-1;
        filename="result.csv"; 
        test_times=100;
        test_count=10000;  
        mode=0;   
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
            else if(arg=="-g"){ //世代数
                if(i+1<argc){
                    max_gen=atoi(argv[i+1]);
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
            else if(arg=="-tt"){ //いつテストするか
                if(i+1<argc){
                    test_times=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-tc"){ //テスト回数
                if(i+1<argc){
                    test_count=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-m"){ //学習法
                if(i+1<argc){
                    mode=atoi(argv[i+1]);
                    i++;
                }
            }
            else if(arg=="-h"||arg=="--help"){ //ヘルプ表示
                showHelp();
                exit(0);
            }
        }
        calcDerived();
    }

    void calcDerived(){
        max_gen=100*dimension;
        test_times=max_gen/100;
    }

    // 設定値の表示
    void echo() {
        printf("--- Parameter Settings ---\n");
        printf("Dimension : %d\n",dimension);
        printf("Max Gen   : %d\n",max_gen);
        printf("seed      : %d\n",seed);
        printf("output filename: %s\n",filename.c_str());
        printf("test_times: %d\n",test_times);
        printf("test_count: %d\n",test_count);
        printf("mode      : %d\n",mode);
        printf("--------------------------\n");
    }

    // ヘルプ表示用
    void showHelp() {
        printf("Usage: ./main [options]\n");
        printf("Options:\n");
        printf("  -d <int>   Set dimension (default: 10)\n");
        printf("  -g <int>   Set max generation (default: 1)\n");
        printf("  -s <int>   Set seed\n");
        printf("  -o <name>  Set output filename (default: result.csv)\n");
        printf("  -tt<int>   Set test_times (default 100)\n");
        printf("  -tc<int>   Set test_count (default 10000)\n");
        printf("  -m <int>   Select mode ( 0: Hebbian, 1: perceptron, 2: adatron)\n");
        printf("  -h         Show this help message\n");
    }

};

// グローバル変数として宣言（実体は main.cpp に置く）
extern Parameter param;

#endif