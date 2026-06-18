#ifndef _PARAMETER_HPP_
#define _PARAMETER_HPP_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "config.hpp"
using namespace std;

class Parameter
{
public:
    int dimension;       // 次元数
    int pop_size;        // 母集団サイズ
    int max_gen;         // 終了世代
    int p_size;          // 親の数
    int c_size;          // 子の数
    int seed;            // シード値
    int orconstraint;    // 制約の有無
    string filename;     // ファイル名
    string fn;           // 使用する関数名
    double mutationrate; // 突然変異率
    vector<double> min_value;
    vector<double> max_value;
    double learning_rate; // 学習率

    // WFGに関するパラメータ
    int M; // WFGの目的関数の数
    int k; // 位置決定のパラメータ
    int l; // 距離決定パラメータ

    // 関数のプロトタイプ
    void load(int argc, char **argv); // 変数読み込み
    void calcDerived();               // 次元数依存の変数等を計算
    void setBounds();                 // 定義域設定
    int objectiveCount();             // 目的関数の数を返す
    void echo();                      // パラメータ表示
    void showHelp();                  // ヘルプ表示
};

#endif