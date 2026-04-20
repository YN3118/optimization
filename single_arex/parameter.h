#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include<cstdio>
#include<vector>
#include<random>
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

class Parameter
{
public:
    int dimension;    // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
    int pop_size;     // �ｿｽ�ｿｽW�ｿｽc�ｿｽT�ｿｽC�ｿｽY
    int max_gen;      // �ｿｽﾅ大世�ｿｽ辮�
    int f_num;        // �ｿｽﾖ撰ｿｽ�ｿｽﾔ搾ｿｽ
    int p_size;       // �ｿｽe�ｿｽﾌ撰ｿｽ
    int c_size;       // �ｿｽq�ｿｽﾌ撰ｿｽ
    int seed;         // �ｿｽV�ｿｽ[�ｿｽh�ｿｽl
    int orconstraint; // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
    int trial;        // �ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ
    string filename;  // �ｿｽo�ｿｽﾍフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ

    // �ｿｽ關�
    double mutationrate;
    double min_value; // �ｿｽﾝ計�ｿｽﾏ撰ｿｽ�ｿｽﾌ最擾ｿｽ�ｿｽl
    double max_value; // �ｿｽﾝ計�ｿｽﾏ撰ｿｽ�ｿｽﾌ最托ｿｽl
    vector<int> rast_shift;

    // �ｿｽR�ｿｽ�ｿｽ�ｿｽX�ｿｽg�ｿｽ�ｿｽ�ｿｽN�ｿｽ^
    Parameter()
    {
        dimension = 5;
        pop_size = 100;
        max_gen = 1;
        f_num = 1;
        mutationrate = 0.0;
        max_value = 5.12;
        min_value = -5.12;
        seed = -1;
        orconstraint = 1;
        trial = 1;
        filename = "result.csv";
        calcDerived(); // �ｿｽﾋ托ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽﾌ計�ｿｽZ
    }

    // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽﾅ値�ｿｽ�ｿｽ�ｿｽX�ｿｽV�ｿｽ�ｿｽ�ｿｽ�ｿｽ
    void load(int argc, char *argv[])
    {
        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "-d")
            { // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
                if (i + 1 < argc)
                {
                    dimension = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-p")
            { // �ｿｽ�ｿｽW�ｿｽc�ｿｽT�ｿｽC�ｿｽY
                if (i + 1 < argc)
                {
                    pop_size = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-g")
            { // �ｿｽ�ｿｽ�ｿｽ辮�
                if (i + 1 < argc)
                {
                    max_gen = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-f")
            { // �ｿｽﾖ撰ｿｽ�ｿｽﾔ搾ｿｽ
                if (i + 1 < argc)
                {
                    f_num = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-o")
            { // �ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
                filename = argv[i + 1];
                i++;
            }
            else if (arg == "-s")
            { // �ｿｽV�ｿｽ[�ｿｽh�ｿｽl
                if (i + 1 < argc)
                {
                    seed = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-c")
            { // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
                if (i + 1 < argc)
                {
                    orconstraint = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-t")
            { // �ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ
                if (i + 1 < argc)
                {
                    trial = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-h" || arg == "--help")
            { // �ｿｽw�ｿｽ�ｿｽ�ｿｽv�ｿｽ\�ｿｽ�ｿｽ
                showHelp();
                exit(0);
            }
        }
        // �ｿｽl�ｿｽ�ｿｽ�ｿｽﾏゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌで再計�ｿｽZ
        calcDerived();
        // echo();
    }

    // �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾈどに依托ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
    void calcDerived()
    {
        p_size = dimension + 1;
        c_size = 4 * dimension;

        // �ｿｽﾖ撰ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ抵ｿｽ`�ｿｽ�ｿｽ�ｿｽﾏ更
        // Rosenbrock
        if (f_num == 0)
        {
            min_value = -5.0;
            max_value = 5.0;
        }
        // Rastrigin
        else if (f_num == 1)
        {
            min_value = -5.12;
            max_value = 5.12;
        }
        // Sphere
        else if (f_num == 2)
        {
            min_value = -1.0e9;
            max_value = 1.0e9;
        }
        // Ackley
        else if (f_num == 3)
        {
            min_value = -32.768;
            max_value = 32.768;
        }
        // Schwefel
        else if (f_num == 4)
        {
            min_value = -500.0;
            max_value = 500.0;
        }
        // Rosenbrock_chain
        else if (f_num == 5)
        {
            min_value = -5.0;
            max_value = 5.0;
        }
        // Ellipsoid
        else if (f_num == 6)
        {
            min_value = -5.12;
            max_value = 5.12;
        }
        // Bohaxhevsky
        else if (f_num == 7)
        {
            min_value = -5.12;
            max_value = 5.12;
        }
        // Griewank
        else if (f_num == 8)
        {
            min_value = -300.0;
            max_value = 300.0;
        }
        // new_Rastrigin
        else if (f_num == 9)
        {
            min_value = -5.12;
            max_value = 5.12;
            const char *filename = "rastrigin_shift.csv";
            FILE *file = fopen(filename, "r");
            int size = 0;
            rast_shift.resize(dimension);

            char line[1024]; // 1行を読み込むためのバッファ

            // 行ごとに読み込む
            while (fgets(line, sizeof(line), file) != NULL)
            {
                // 改行文字を削除
                line[strcspn(line, "\r\n")] = '\0';

                // 空行の場合はスキップ
                if (strlen(line) == 0)
                    continue;

                // カンマ区切りで文字列を分割（1列のみの場合もこれで動作します）
                char *token = strtok(line, ",");
                while (token != NULL)
                {
                    // 文字列を整数に変換して配列に保存
                    rast_shift[size] = atoi(token);
                    size++;
                    // 次のトークン（カンマ区切りの次の要素）を取得
                    token = strtok(NULL, ",");
                }
            }
        }
    }

    // �ｿｽﾝ抵ｿｽl�ｿｽﾌ表�ｿｽ�ｿｽ
    void echo()
    {
        printf("--- Parameter Settings ---\n");
        printf("Dimension : %d\n", dimension);
        printf("Pop Size  : %d\n", pop_size);
        printf("Max Gen   : %d\n", max_gen);
        printf("Function  : %d\n", f_num);
        printf("p_size    : %d\n", p_size);
        printf("c_size    : %d\n", c_size);
        printf("seed      : %d\n", seed);
        printf("constraint: %d\n", orconstraint);
        printf("trial num : %d\n", trial);
        printf("output filename: %s\n", filename.c_str());
        printf("--------------------------\n");
        for(int i=0;i<rast_shift.size();i++){
            cout<<rast_shift[i]<<endl;
        }
    }

    // �ｿｽw�ｿｽ�ｿｽ�ｿｽv�ｿｽ\�ｿｽ�ｿｽ�ｿｽp
    void showHelp()
    {
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
        printf("             8:Griewank, 9:new_Rastrigin\n");
        printf("  -h         Show this help message\n");
    }
};

// �ｿｽO�ｿｽ�ｿｽ�ｿｽ[�ｿｽo�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽﾆゑｿｽ�ｿｽﾄ宣言�ｿｽi�ｿｽ�ｿｽ�ｿｽﾌゑｿｽ main.cpp �ｿｽﾉ置�ｿｽ�ｿｽ�ｿｽj
extern Parameter param;

#endif