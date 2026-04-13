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

    //初期母集団生成
    vector<Indiv> indiv;
    indiv.resize(param.pop_size);
    for(int i=0;i<param.pop_size;i++){
        printf("pop_num:%d\t",i);
        indiv[i].echo();
    }

    //初期個体を評価
    NSGA2 temp(indiv);
    temp.decide_rank();
    indiv.clear();
    for(int i=0;i<temp.F.size();i++){
        for(int j=0;j<temp.F[i].size();j++){
            indiv.push_back(temp.F[i][j]);
        }
    }

    //ファイル書き込み
    FILE *file;
    file=fopen(param.filename.c_str(),"w");
    if(file==NULL){
        printf("Cannot open file %s\n",param.filename.c_str());
        return -1;
    }    
    fprintf(file,"次元数,%d,母集団サイズ,%d,子個体生成数,%d\n",param.dimension,param.pop_size,param.c_size);
    fprintf(file,"初期f1,初期f2\n");
    for(int i=0;i<indiv.size();i++){
        fprintf(file,"%f,%f\n",indiv[i].f[0],indiv[i].f[1]);
    }
    fprintf(file,"\nf1,f2\n");

    //拡張率記録用ファイル
    FILE *result_alpha;
    result_alpha=fopen("result_alpha.csv","w");
    if(result_alpha==NULL){
        printf("Cannot open file %s\n","result_alpha.csv");
        return -1;
    }
    fprintf(result_alpha,"世代数,拡張率\n");
    
    //AREX実行
    AREX arex(indiv,file);
    int count=0;
    for(count=0;count<param.max_gen;count++){
        printf("---%d世代目---\n",count+1);
        arex.execute();
        fprintf(result_alpha,"%d,%f\n",count+1,arex.alpha);
        //ランクがすべて1なら終了
        if(rank_ck(arex.population)) break;
    }
    param.echo();
    for(int i=0;i<arex.population.size();i++){
        fprintf(file,"%f,%f\n",arex.population[i].f[0],arex.population[i].f[1]);
    }
    printf("Number of evaluation: %d\n",count*param.c_size);
    fprintf(file,"\n\n評価回数,%d\n",count*param.c_size);
    fclose(file);
    fclose(result_alpha);
    return 0;
}