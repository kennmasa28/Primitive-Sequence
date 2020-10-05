//coding:utf-8
//consistent with Hardy hierarchy
#include <stdio.h>
#include <stdlib.h>

int main(){
  //define variable------------------------------------------
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

  //output initial state-------------------------------------
  printf("(");
  for (int i = 0;i < k; i++) {
    printf("%d,",s[i]);
  }
  printf("%d", s[k]);
  printf(")[%d]\n",n);
 //find good and bad part----------------------------------------
  while (k != 0){

    if (s[k]==0)
    {
      //if S_k = 0
      k = k - 1;
      s = (int *)realloc(s,sizeof(int)*(k+1));
      n = n + 1;
    }
    else
    {
      //if S_k != 0
      exist = 0;
      for (int i=0 ; i<=k ;i++){
        //if bad part exist---------------------------------
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
            i = k;//break
        }//if
        //if bad part don't exist-----------------------------
        if (i==k && exist==0){
          badfirst = k;
          good = (int *)realloc(good,sizeof(int)*(badfirst));
          for (int j=0; j<badfirst ;j++){
            good[j] = s[j];
          }
          free(bad);
        }

      }//for
      //create new primitive sequence---------------------------
      if (exist == 0){
        //if only good part---------------------
        s = (int *)realloc(s,sizeof(int)*k);
        for (int i=0 ; i<badfirst; i++){
          s[i] = good[i];
        }
        k = k-1;

      }else{
        //if bad part exist-------------------
        s = (int *)realloc(s,sizeof(int)*(badfirst+(k-badfirst)*n));
        //----良い部分を埋める----
        for (int i=0 ; i<badfirst; i++){
          s[i] = good[i];
        }
        //----copy bad part-------
        for (int i=0 ; i<n; i++){
          for (int j=0 ; j<k-badfirst; j++){
            s[badfirst + i*(k-badfirst) + j] = bad[j];
          }
        }
        k = badfirst+(k-badfirst)*n-1;//kの更新
      }

    }

    //n become f(n) and output new sequence--------------
    printf("(");
    for (int i = 0; i < k; i++) {
      printf("%d,",s[i]);
    }
    printf("%d", s[k]);
    printf(")[%d]\n",n);
  }//while

  //final output--------------------------------------------------------
  if (s[0]==0){
    n = n + 1;
  }
  printf("finish!...%d\n", n);
  return 0;
}//main
