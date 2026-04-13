#ifndef _NSGA2_H_
#define _NSGA2_H_

#include"extract.h"
#include"parameter.h"
#include"indiv.h"

//aがbに優越していればtrueを返す
bool superiority(Indiv a,Indiv b){
  if(a.f[0]==b.f[0]&&a.f[1]==b.f[1]) return false;
  if(a.f[0]<=b.f[0]&&a.f[1]<=b.f[1]) return true;
  return false;
}

bool cmp_f1(const Indiv &a,const Indiv &b){
        return a.f[0]<b.f[0]; //昇順
}

bool cmp_f2(const Indiv &a,const Indiv &b){
        return a.f[1]<b.f[1]; //昇順
}

bool cmp_cd(const Indiv &a,const Indiv &b){
        return a.crowding_distance>b.crowding_distance; //降順
}

//混雑距離計算(参照渡しにして直接書き換える)
vector<Indiv> cal_cd(vector<Indiv> &a){
    //抽出された個体数が少ないときは全て無限にして終了
    if(a.size()<=2){
        for(int i=0;i<a.size();i++){
          a[i].crowding_distance=INFINITY;
        }
        return a;
    }
    //初期化
    for(int i=0;i<a.size();i++){
        a[i].crowding_distance=0.0;
    }
        
    //f1についての混雑距離計算
    sort(a.begin(),a.end(),cmp_f1);
    double f_max=a[a.size()-1].f[0];
    double f_min=a[0].f[0];
    for(int i=1;i<a.size()-1;i++){
      if(f_max!=f_min){
        a[i].crowding_distance+=(a[i+1].f[0]-a[i-1].f[0])/(f_max-f_min);
      }
    }


    //境界個体の距離を無限大にする
    a[a.size()-1].crowding_distance=a[0].crowding_distance=INFINITY;

    //f2についての混雑距離計算
    sort(a.begin(),a.end(),cmp_f2);
    f_max=a[a.size()-1].f[1];
    f_min=a[0].f[1];
    for(int i=1;i<a.size()-1;i++){
      if(f_max!=f_min){
        a[i].crowding_distance+=(a[i+1].f[1]-a[i-1].f[1])/(f_max-f_min);
      }
    }
    //境界個体の距離を無限大にする
    a[a.size()-1].crowding_distance=a[0].crowding_distance=INFINITY;
    return a;
}

class NSGA2{
  public:
  vector<Indiv> population;
  vector<vector<Indiv>> F; //ランク割り当て後の集団を保存
  vector<Indiv> next;

  //コンストラクタ
  NSGA2(vector<Indiv> a){
    population.resize(a.size());
    population=a;
    next.resize(a.size());
    //念のため初期化
    for(int i=0;i<population.size();i++){
      population[i].rank=0;
      population[i].dominant=0;
      population[i].crowding_distance=0.0;
    }
  }

  void exe(){
    decide_rank();
    create_next_pop();
  }

  //ランクづけ
  void decide_rank(){
    int r=1;

    while(!population.empty()){
      //支配数リセット
      for(int i=0;i<population.size();i++){
        population[i].dominant=0;
      }

      F.resize(r);
      for(int i=0;i<population.size();i++){
        for(int j=0;j<population.size();j++){
          if(i!=j){
            if(superiority(population[j],population[i])) population[i].dominant+=1;
          }
        }
      }

      //優越された解の個数が0個の個体にランクrを与える
      for(int i=0;i<population.size();i++){
        if(population[i].dominant==0) population[i].rank=r;
      }
      vector<Indiv> non_dominant=extract_if(population,[](const Indiv &t){return t.dominant==0;});
      F[r-1].resize(non_dominant.size());
      F[r-1]=move(non_dominant);
      r++;
    }
  }

  //次世代集団生成
  void create_next_pop(){
    int sum=0;
    for(int i=0;i<F.size();i++){
      if(sum+F[i].size()<next.size()){
        for(int j=0;j<F[i].size();j++){
          next[sum+j]=move(F[i][j]);
        }
      }
      else{
        cal_cd(F[i]);
        sort(F[i].begin(),F[i].end(),cmp_cd);
        for(int j=0;j<next.size()-sum;j++){
          next[sum+j]=move(F[i][j]);
        }
        F.clear();
        return;
      }
      sum+=F[i].size();
    }
  }
};

#endif
