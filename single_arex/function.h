#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<random>

#include"config.h"

using namespace std;


namespace Function{

    //��̃x�N�g���̒��_�v�Z
    inline vector<double> cal_centor(vector<double> a,vector<double> b){
        vector<double> result_centor;
        for(int i=0;i<a.size();i++){
            result_centor.push_back((a[i]+b[i])/2);
        }
        return result_centor;
    }

    //��̃x�N�g���̍����v�Z
    //�֐��̈�����1������Ɛ�Βl�v�Z���[�h
    inline vector<double> cal_dis(vector<double> a,vector<double> b,int n){
        vector<double> result_dis;
        for(int i=0;i<a.size();i++){
            result_dis.push_back(a[i]-b[i]);
            if(n==1&&result_dis[i]<0) result_dis[i]=fabs(result_dis[i]);
        }

        return result_dis;
    }

    //��̃x�N�g���̐ς��v�Z
    //��ڂ̈����̉E�����ڂ̃x�N�g����������
    //�����(dim_num�~1)�~(1�~dim_num)������萔��Ԃ�
    inline double cal_mul(vector<double> a,vector<double> b){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*b[i];
        }
        return result;
    }

    //�萔�~�x�N�g��
    inline vector<double> cal_constmul(double a,vector<double> b){
        vector<double> result;
        for(int i=0;i<b.size();i++){
            result.push_back(a*b[i]);
        }
        return result;
    }

    //�x�N�g���̃m�������v�Z
    inline double cal_norm(vector<double> a){
        double result=0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*a[i];
        }
        return sqrt(result);
    }
    
    //��̃x�N�g���̘a���v�Z
    inline vector<double> cal_sum(vector<double> a,vector<double> b){
        vector<double> result_sum;
        for(int i=0;i<a.size();i++){
            result_sum.push_back(a[i]+b[i]);
        }
        return result_sum;
    }

    //�x�N�g���̘a�i�񎟌��Ή��j
    inline vector<double> cal_sumex(vector<vector<double>> b){
        vector<double> result;
        for(int i=0;i<b[0].size();i++){
            double sum=0.0;
            for(int j=0;j<b.size();j++){
                sum+=b[j][i];
            }
            result.push_back(sum);
        }
        return result;
    }

    //�x�N�g���̓��όv�Z
    inline double cal_naiseki(vector<double> a,vector<double> b){
        double result=0.0;
        for(int i=0;i<a.size();i++){
            result+=a[i]*b[i];
        }
        return result;
    }

    //double�̗����𐶐�
    inline double generateRandomDouble(double a,double b) {
        random_device rd; // �n�[�h�E�F�A����������
        //mt19937 gen(rd()); // �����Z���k�E�c�C�X�^
        //mt19937 gen(seed);
        uniform_real_distribution<> dis(a,b); // ��l���z

        return dis(gen);
    }

    //int�̗����𐶐�
    inline int generateRandomInt(int a,int b) {
        random_device rd; // �n�[�h�E�F�A����������
        //mt19937 gen(rd()); // �����Z���k�E�c�C�X�^
        //mt19937 gen(seed);
        uniform_real_distribution<> dis(a,b); // ��l���z

        return dis(gen);
    }

    //����mean �W���΍�stddev�̐��K�����𐶐�
    inline double generateRandomNomal(double mean,double stddev){
        random_device rd;
        //mt19937 gen(rd());
        //mt19937 gen(seed);
        normal_distribution<> dis(mean, stddev);//���K���z

        return dis(gen);
    }

    //��l���z�̗����𐶐�
    inline double generateRandomDist(double a,double b){
        random_device rd;
        uniform_real_distribution<> dist(a,b);
        return dist(gen);
    }

    //�]�u�s����v�Z
    inline vector<vector<double>> transpose(vector<vector<double>> a){
        vector<vector<double>> result(a[0].size(),vector<double>(a.size()));
        for(int i=0;i<a[0].size();i++){
            for(int j=0;j<a.size();j++){
                result[i][j]=a[j][i];
            }
        }
        return result;
    }
    
    //�t�s����v�Z

};

#endif
