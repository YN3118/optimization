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

    //������W�c����
    vector<Indiv> indiv;
    indiv.resize(param.pop_size);
    for(int i=0;i<param.pop_size;i++){
        indiv[i].indiv_num=i;
        // printf("pop_num:%d\t",i);
        // indiv[i].echo();
    }

    //�t�@�C����������
    FILE *file;
    file=fopen(param.filename.c_str(),"w");
    if(file==NULL){
        printf("Cannot open file %s\n",param.filename.c_str());
        return -1;
    }
    
    fprintf(file,"x�̍ŏ��l,%f,x�̍ő�l,%f,��W�c�T�C�Y,%d,�q�̐�����,%d\n",param.min_value,param.max_value,param.pop_size,param.c_size);
    fprintf(file,"���㐔,�ŗǌ�,�ň���,�g����");
    fprintf(file,",");
    for(int i=0;i<param.dimension;i++){
        fprintf(file,",var_x[%d]",i);
    }
    fprintf(file,",");
    for(int i=0;i<param.dimension;i++){
        fprintf(file,",best_x[%d]",i);
    }
    fprintf(file,",,�œK���Ƃ̋���\n");


    //AREX���s
    AREX arex(indiv,file);
    int count=0;
    for(count=0;count<param.max_gen;count++){
        printf("---%d�����---\n",count+1);
        fprintf(file,"%d,",count+1);
        arex.execute();
        //�֐��l���\���������Ȃ�����I��
        if(arex.population[0].f<1.0e-9) break;
    }
    param.echo();
    printf("Number of evaluation: %d\n",count*param.c_size);
    fprintf(file,"�]����,%d\n",count*param.c_size);
    fclose(file);
    return 0;
}