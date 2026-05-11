#include "arex.h"
#include "parameter.h"
#include <ctime>

Parameter param;

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
    // srand(seed);
    // gen.seed(seed);

    FILE *file;
    file = fopen(param.filename.c_str(), "w");
    if (file == NULL)
    {
        printf("Cannot open file %s\n", param.filename.c_str());
        return -1;
    }
    fprintf(file, "pop_size,dimension,");
    if (param.orconstraint == 1)
    {
        fprintf(file, "constraint\n");
    }
    else
        fprintf(file, "not constraint\n");
    fprintf(file, "%d,%d\n", param.pop_size, param.dimension);
    fprintf(file, "trial time,success,eval_time when successing\n");

    long long total_eval = 0;
    int success_count = 0; // successing time

    for (int t = 0; t < param.trial; t++)
    {
        srand(seed);
        gen.seed(seed);
        // make population
        vector<Indiv> indiv;
        indiv.resize(param.pop_size);
        for (int i = 0; i < param.pop_size; i++)
        {
            indiv[i].indiv_num = i;
        }

        // AREX
        AREX arex(indiv, file);
        int count = 0;
        bool judge = false;
        for (count = 0; count < param.max_gen; count++)
        {
            arex.execute();
            // 終了条件
            if (arex.population[0].f < 1.0e-9)
            {
                judge = true;
                break;
            }
        }

        int eval = count * param.c_size;
        if (judge)
        {
            success_count++;
            total_eval += eval;
        }
        seed++;

        printf("\rProgress: [%3d/%3d] Success: %3d | Last eval: %d", t + 1, param.trial, success_count, eval);
        fflush(stdout);
    }
    printf("\n");
    param.echo();

    printf("Success rate : %d / %d (%.1f%%)\n", success_count, param.trial, 100.0 * success_count / param.trial);
    fprintf(file, "%d,%d,%f\n", param.trial, success_count, (double)total_eval / success_count);
    fclose(file);
    return 0;
}