#ifndef _AREX_H_
#define _AREX_H_

#include"config.h"
#include"indiv.h"
#include"constraint.h"


class AREX{
    public:
    
    vector<Indiv> population; //�����O�̏W�c
    vector<Indiv> parent;     //�I�΂ꂽ�e��
    vector<Indiv> children;   //�ł����q��
    double alpha=1.0;         //�g����(�����l��1)
    FILE *file;               //�ۑ��p

    vector<int> permutation;
    Function func;

    //�R���X�g���N�^
    AREX(vector<Indiv> a,FILE *f){
        population.resize(a.size());
        for(int i=0;i<a.size();i++){
            population[i]=a[i];
        }
        children.resize(param.c_size);
        file=f;        
    }

    void execute(){
        selection();
        crossover();
        //mutation();
        evaluate();
    }

    void selection(){
        permutation.resize(param.pop_size);
        for(int i=0;i<param.pop_size;i++){
            permutation[i]=i;
        }

        for(int i=0;i<param.pop_size;i++){
            int temp1=rand()%param.pop_size;
            int temp2=rand()%param.pop_size;
            swap(permutation[temp1],permutation[temp2]);
        }


        //�e�͎̂�����+1�ɂ���
        parent.resize(param.p_size);
        for(int i=0;i<param.p_size;i++){
            parent[i]=population[permutation[i]];
        }
    }
    
    void crossover(){
        //�d�S���v�Z
        vector<double> g(param.dimension);
        for(int i=0;i<param.dimension;i++){
            double sum=0.0;
            for(int j=0;j<param.p_size;j++){
                sum+=parent[j].x[i];
            }
            g[i]=sum/(param.p_size);
        }
        


        //�������S�~��
        vector<Indiv> p_copy(param.p_size);
        p_copy=parent;
        sort(p_copy.begin(),p_copy.end());
        vector<double> new_g(param.dimension,0.0);
        for(int i=0;i<p_copy.size();i++){
            double tmp=(2.0*(param.dimension+1-i))/((param.dimension+1)*(param.dimension+2));
            new_g=func.cal_sum(new_g,func.cal_constmul(tmp,p_copy[i].x));
        }


        //�d�S�Ƃ̍��x�N�g��
        vector<vector<double>> v; 
        for(int i=0;i<param.p_size;i++){
            v.push_back(func.cal_dis(g,parent[i].x,0));
        }

        //�q�̐���
        vector<double> child_temp(param.dimension,0.0);
        vector<double> eps(param.p_size);

        for(int i=0;i<param.c_size;i++){
            do{
                vector<double> sum(param.dimension,0.0);
                for(int j=0;j<param.p_size;j++){
                    double tmp=func.generateRandomNomal(0.0,sqrt(1.0/param.dimension));
                    eps[j]=tmp;
                    sum=func.cal_sum(sum,func.cal_constmul(tmp,v[j]));
                }

                child_temp=func.cal_sum(new_g,func.cal_constmul(alpha,sum));
            }while(!(constraint(child_temp)));
            Indiv c(child_temp,i);
            children[i]=c;
            children[i].eps=eps;
        }

        v.clear();
    }

    void mutation(){
        double judge=func.generateRandomDouble(0.0,1.0);
        if(judge<param.mutationrate){
            double sum=0.0;
            int temp=rand()%children.size();
            for(int i=0;i<children[temp].x.size();i++){
                sum+=children[temp].x[i];
            }
            double avg=sum/param.dimension;
            for(int i=0;i<children[temp].x.size();i++){
                children[temp].x[i]=avg;
            }
            children[temp].f=Rastrigin(children[temp].x);
        }
    }

    void evaluate(){

        //�q�̕]��
        sort(children.begin(),children.end());

        //alpha更新
        double L_avg;
        double L_cdp=0.0;
        double sum1=0.0;//��敽��
        double sum2=0.0;//���ς̓��

        for(int j=0;j<param.p_size;j++){
            double e=0.0;
            for(int i=0;i<param.p_size;i++){
                e+=children[i].eps[j]/(param.dimension+1);
            }
            sum1+=pow(e,2);
            sum2+=e;
        }
        sum2=pow(sum2,2)/(param.dimension+1);



        //printf("sum1:%f\tsum2:%f\n",sum1,sum2);
        
        L_cdp=pow(alpha,2)*(param.dimension)*(sum1-sum2);
        L_avg=pow(alpha,2)*(param.dimension)/(param.dimension+1);
        double c=1.0/(5*param.dimension);//�w�K��
        double next_alpha=alpha*sqrt((1.0-c)+(c*L_cdp/L_avg));
        //printf("next_alpha=%f\n",next_alpha);
        if(next_alpha<1.0) alpha=1.0;
        else alpha=next_alpha;
        //printf("alpha=%f\n",alpha);


        //�����ヂ�f����JGG(�I�񂾐e�̂Ɠ�������������ւ�)
        sort(children.begin(),children.end());
        for(int i=0;i<param.p_size;i++){
            population[permutation[i]]=children[i];
        }
        sort(population.begin(),population.end());



    }
};

#endif