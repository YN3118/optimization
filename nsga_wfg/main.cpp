#include "arex.h"
#include "parameter.h"
#include <ctime>

Parameter param;
mt19937 gen;

int main(int argc, char *argv[])
{
    param.load(argc, argv);
    unsigned int seed;

    if (param.seed == -1)
    {
        seed = (unsigned int)time(NULL);
    }
    else
        seed = (unsigned int)param.seed;
    srand(seed);
    gen.seed(seed);

    // 母集団生成
    vector<Indiv> indiv;
    indiv.resize(param.pop_size);
    for (int i = 0; i < param.pop_size; i++)
    {
        printf("pop_num:%d\t", i);
        indiv[i].echo();
    }

    // �����̂�]��
    NSGA2 temp(indiv);
    temp.decide_rank();
    indiv.clear();
    for (int i = 0; i < temp.F.size(); i++)
    {
        for (int j = 0; j < temp.F[i].size(); j++)
        {
            indiv.push_back(temp.F[i][j]);
        }
    }

    for (int i = 0; i < param.pop_size; i++)
    {
        printf("pop_num:%d\t", i);
        indiv[i].echo();
    }

    // �t�@�C����������
    FILE *file;
    file = fopen(param.filename.c_str(), "w");
    if (file == NULL)
    {
        printf("Cannot open file %s\n", param.filename.c_str());
        return -1;
    }

    fprintf(file, "������,%d,��W�c�T�C�Y,%d,�q�̐�����,%d\n", param.dimension, param.pop_size, param.c_size);
    fprintf(file, "����f1,����f2\n");
    for (int i = 0; i < indiv.size(); i++)
    {
        for (int j = 0; j < param.M; j++)
        {
            fprintf(file, "%f,", indiv[i].fitness[j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\nf1,f2\n");

    // AREX���s
    AREX arex(indiv, file);
    int count = 0;
    for (count = 0; count < param.max_gen; count++)
    {
        printf("---gen%d---\n", count + 1);
        arex.execute();
        // �����N�����ׂ�1�Ȃ�I��
        if (rank_ck(arex.population))
            break;
    }
    param.echo();
    for (int i = 0; i < arex.population.size(); i++)
    {
        for (int j = 0; j < param.M; j++)
        {
            fprintf(file, "%f,", arex.population[i].fitness[j]);
        }
        fprintf(file, "\n");
    }
    printf("Number of evaluation: %d\n", count * param.c_size);
    fprintf(file, "\n\n�]����,%d\n", count * param.c_size);
    fclose(file);
    return 0;
}