#include<cstdio>
#include<vector>
#include<random>
#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;
int main(){
  mt19937 gen(1);
  FILE *file1;
  file1=fopen("rastrigin_shift.csv","w");
  int max=5;
  int min=-5;
  uniform_int_distribution<> dist(min,max);
  fprintf(file1,"min,%d,max,%d\n",min,max);
  for(int i=0;i<500;i++){
    fprintf(file1,"%d\n",dist(gen));
  }
  fclose(file1);
  vector<int> tmp(3);

  // 読み込むファイル名
    const char *filename = "rastrigin_shift.csv";
    
    // ファイルを開く
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error : file cannot open\n");
        return 1;
    }

    // --- std::vector の代わりとなる動的配列の準備 ---
    int capacity = 10; // 初期容量
    int size = 0;      // 現在の要素数
    int *data = (int *)malloc(capacity * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "メモリ割り当てエラー\n");
        fclose(file);
        return 1;
    }

    char line[1024]; // 1行を読み込むためのバッファ
    fgets(line, sizeof(line),file);

    // 行ごとに読み込む
    while (fgets(line, sizeof(line), file) != NULL) {
        // 改行文字を削除
        line[strcspn(line, "\r\n")] = '\0';

        // 空行の場合はスキップ
        if (strlen(line) == 0) continue;

        // カンマ区切りで文字列を分割（1列のみの場合もこれで動作します）
        char *token = strtok(line, ",");
        while (token != NULL) {
            
            // 配列の容量が足りなくなったら、サイズを2倍に拡張 (vectorの内部動作と同様)
            if (size >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(data, capacity * sizeof(int));
                if (temp == NULL) {
                    fprintf(stderr, "メモリ再割り当てエラー\n");
                    free(data);
                    fclose(file);
                    return 1;
                }
                data = temp;
            }

            // 文字列を整数に変換して配列に保存
            data[size] = atoi(token);
            size++;

            // 次のトークン（カンマ区切りの次の要素）を取得
            token = strtok(NULL, ",");
        }
    }

    fclose(file);

    // --- 結果の確認（最初の10要素を表示） ---
    printf("読み込み完了。要素数: %d\n", size);
    for (int i = 0; i < size && i < 10; ++i) {
        printf("%d ", data[i]);
    }
    printf("...\n");

    // 使い終わったメモリは必ず解放する
    free(data);

    return 0;
}