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
    int dimension;    // ?��?��?��?��?��?��
    int pop_size;     // ?��?��W?��c?��T?��C?��Y
    int max_gen;      // ?��ő吢?���?
    int f_num;        // ?��֐�?��ԍ�
    int p_size;       // ?��e?��̐�
    int c_size;       // ?��q?��̐�
    int seed;         // ?��V?��[?��h?��l
    int orconstraint; // ?��?��?��?��?��?��?��
    int trial;        // ?��?��?��s?��?��
    string filename;  // ?��o?��̓t?��@?��C?��?��?��?��

    // ?���?
    double mutationrate;
    double min_value; // ?��݌v?��ϐ�?��̍ŏ�?��l
    double max_value; // ?��݌v?��ϐ�?��̍ő�l
    vector<int> rast_shift;

    // ?��R?��?��?��X?��g?��?��?��N?��^
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
        calcDerived(); // ?��ˑ�?��ϐ�?��̌v?��Z
    }

    // ?��?��?��?��?��?��ǂݍ�?��?��Œl?��?��?��X?��V?��?��?��?��
    void load(int argc, char *argv[])
    {
        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "-d")
            { // ?��?��?��?��?��?��
                if (i + 1 < argc)
                {
                    dimension = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-p")
            { // ?��?��W?��c?��T?��C?��Y
                if (i + 1 < argc)
                {
                    pop_size = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-g")
            { // ?��?��?���?
                if (i + 1 < argc)
                {
                    max_gen = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-f")
            { // ?��֐�?��ԍ�
                if (i + 1 < argc)
                {
                    f_num = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-o")
            { // ?��t?��@?��C?��?��?��?��
                filename = argv[i + 1];
                i++;
            }
            else if (arg == "-s")
            { // ?��V?��[?��h?��l
                if (i + 1 < argc)
                {
                    seed = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-c")
            { // ?��?��?��?��?��?��?��
                if (i + 1 < argc)
                {
                    orconstraint = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-t")
            { // ?��?��?��s?��?��
                if (i + 1 < argc)
                {
                    trial = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (arg == "-h" || arg == "--help")
            { // ?��w?��?��?��v?��\?��?��
                showHelp();
                exit(0);
            }
        }
        // ?��l?��?��?��ς�?��?��?��?��̂ōČv?��Z
        calcDerived();
        // echo();
    }

    // ?��?��?��?��?��?��?��ȂǂɈˑ�?��?��?��?��ϐ�?��?��?��v?��Z
    void calcDerived()
    {
        p_size = dimension + 1;
        c_size = 4 * dimension;

        // ?��֐�?��?��?��ɒ�`?��?��?��ύX
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
            fgets(line, sizeof(line), file); ///ヘッダー削除

            // �s���Ƃɓǂݍ���
            while (fgets(line, sizeof(line), file) != NULL)
            {
                // ���s�������폜
                line[strcspn(line, "\r\n")] = '\0';

                // ��s�̏ꍇ�̓X�L�b�v
                if (strlen(line) == 0)
                    continue;

                // �J���}��؂�ŕ�����𕪊��i1��݂̂̏ꍇ������œ��삵�܂��j
                char *token = strtok(line, ",");
                while (token != NULL)
                {
                    // ������𐮐��ɕϊ����Ĕz��ɕۑ�
                    rast_shift[size] = atoi(token);
                    size++;
                    // ���̃g�[�N���i�J���}��؂�̎��̗v�f�j���擾
                    token = strtok(NULL, ",");
                }
            }
        }
    }

    // ?��ݒ�l?��̕\?��?��
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
    }

    // ?��w?��?��?��v?��\?��?��?��p
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

// ?��O?��?��?��[?��o?��?��?��ϐ�?��Ƃ�?��Đ錾?��i?��?��?��̂� main.cpp ?��ɒu?��?��?��j
extern Parameter param;

#endif