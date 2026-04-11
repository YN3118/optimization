#ifndef _EXTRACT_H_
#define _EXTRACT_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include"config.h"

template<typename T,typename Predicate>
vector<T> extract_if(vector<T>& vec,Predicate pred){
  //条件を満たすものを前方に移動(itは条件を満たさなかった最初の要素を指す)
  auto it=stable_partition(vec.begin(),vec.end(),pred);

  //集めた部分を新しいvectorに移動
  vector<T> extracted(
    make_move_iterator(vec.begin()),
    make_move_iterator(it)
  );

  //元のvectorから削除
  vec.erase(vec.begin(),it);

  return extracted;
}

// Gemini解説
// typename T: 「何かしらの型を T と呼ぶことにしますよ」という宣言です。ここに int や std::string が自動的に当てはまります。
// typename Predicate: Predicate（プレディケート＝述語・条件式）の略で、「何かしらの条件判定をしてくれる関数（またはラムダ式）」を指します。

//test

#endif