#include"arex.h"
#include"parameter.h"
#include<ctime>

Parameter param;

int main(int argc,char* argv[]){
    param.load(argc,argv);
    unsigned int seed;

    if(param.seed==-1){
        seed=(unsigned int)time(NULL);
    }
    else seed=(unsigned int)param.seed;
    srand(seed);
    gen.seed(seed);


    //ファイル書き込み
    FILE *file;
    file=fopen(param.filename.c_str(),"w");
    if(file==NULL){
        printf("Cannot open file %s\n",param.filename.c_str());
        return -1;
    }
    fprintf(file,"母集団サイズ,次元数,");
    if(param.orconstraint==1){
        fprintf(file,"制約あり\n");
    }
    else fprintf(file,"制約なし\n");
    fprintf(file,"%d,%d\n",param.pop_size,param.dimension);
    fprintf(file,"試行回数,探索成功回数,成功時の平均評価回数\n");

    long long total_eval=0;    //総評価回数
    int success_count=0; //成功回数

    for(int t=0;t<param.trial;t++){
        //printf("\n---trial %d / %d ---\n",t+1,param.trial);
        //初期母集団生成
        vector<Indiv> indiv;
        indiv.resize(param.pop_size);
        for(int i=0;i<param.pop_size;i++){
            indiv[i].indiv_num=i;
        }

        //AREX実行
        AREX arex(indiv,file);
        int count=0;
        bool judge=false;
        for(count=0;count<param.max_gen;count++){
            arex.execute();
            //関数値が十分小さくなったら終了
            if(arex.population[0].f<1.0e-9){
                judge=true;
                break;
            }
        }

        int eval=count*param.c_size;
        if(judge){
            success_count++;
            total_eval+=eval;
        }

        printf("\rProgress: [%3d/%3d] Success: %3d | Last eval: %4d",t+1,param.trial,success_count,eval);
        fflush(stdout);
    }
    printf("\n");
    param.echo();

    printf("Success rate : %d / %d (%.1f%%)\n",success_count,param.trial,100.0*success_count/param.trial);
    fprintf(file,"%d,%d,%f\n",param.trial,success_count,(double)total_eval/success_count);
    fclose(file);
    return 0;
}