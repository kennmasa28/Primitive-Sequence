//coding:utf-8
//教訓：二重にint badfirst= ~ とするとバグる
//ハーディ階層に合わせている
#include <stdio.h>
#include <stdlib.h>

int main(){
  //変数設定------------------------------------------
  int *s;
  int k=2;//-----------changeable
  s = (int *)malloc(sizeof(int)*(k+1));
  ///////////////changeable//////////////////////
  s[0]=0, s[1]=1, s[2]=1;
  int n = 3;
  //////////////////////////////////////////////
  if (s == NULL){
    exit(0);
  }
  int *good;
  int *bad;
  good = (int *)malloc(sizeof(int));
  bad = (int *)malloc(sizeof(int));
  int exist;
  int badfirst;

  //最初の配列を表示-------------------------------------
  printf("(");
  for (int i = 0;i < k; i++) {
    printf("%d,",s[i]);
  }
  printf("%d", s[k]);
  printf(")[%d]\n",n);
 //原始数列を変形----------------------------------------
  while (k != 0){

    if (s[k]==0)
    {
      //S_k = 0 のときのルール
      k = k - 1;
      s = (int *)realloc(s,sizeof(int)*(k+1));
      n = n + 1;
    }
    else
    {
      //S_k != 0 のときのルール
      exist = 0;
      for (int i=0 ; i<=k ;i++){
        //悪い部分が存在した場合---------------------------------
        if (s[k-i]<s[k]){
            badfirst = k-i;
            printf("\n" );
            good = (int *)realloc(good,sizeof(int)*(badfirst));
            bad = (int *)realloc(bad,sizeof(int)*(i));
            for (int j=0 ; j<badfirst; j++){
              good[j] = s[j];
            }
            for (int j=0 ; j<i;j++){
              bad[j] = s[k-i+j];
            }
            exist = 1;
            i = k;//breakのつもり
        }//if
        //悪い部分が存在しなかった場合-----------------------------
        if (i==k && exist==0){
          badfirst = k;
          good = (int *)realloc(good,sizeof(int)*(badfirst));
          for (int j=0; j<badfirst ;j++){
            good[j] = s[j];
          }
          free(bad);
        }

      }//for
      //ここからgoodとbadを原始数列に代入---------------------------
      if (exist == 0){
        //良い部分だけのときの処理---------------------
        s = (int *)realloc(s,sizeof(int)*k);
        for (int i=0 ; i<badfirst; i++){
          s[i] = good[i];
        }
        k = k-1;

      }else{
        //悪い部分もあるときの処理-------------------
        s = (int *)realloc(s,sizeof(int)*(badfirst+(k-badfirst)*n));
        //----良い部分を埋める----
        for (int i=0 ; i<badfirst; i++){
          s[i] = good[i];
        }
        //----悪い部分を埋める-------
        for (int i=0 ; i<n; i++){
          for (int j=0 ; j<k-badfirst; j++){
            s[badfirst + i*(k-badfirst) + j] = bad[j];
          }
        }
        k = badfirst+(k-badfirst)*n-1;//kの更新
      }

    }//else(右端が0かどうかの)

    //nをf(n)にするのと、新しい原始数列を表示--------------
    printf("(");
    for (int i = 0; i < k; i++) {
      printf("%d,",s[i]);
    }
    printf("%d", s[k]);
    printf(")[%d]\n",n);
  }//while

  //最後の出力--------------------------------------------------------
  if (s[0]==0){
    n = n + 1;
  }
  printf("finish!...%d\n", n);
  return 0;
}//main
