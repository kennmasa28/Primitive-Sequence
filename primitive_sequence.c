//coding:utf-8
#include <stdio.h>
#include <stdlib.h>

void output(int s[], int k, int n);

int main()
{
  //define variable------------------------------------------
  int k;//------------------------------the digits of primitive sequence
  int pre_s;
  int n;//------------------------------parameter of primitive sequence
  int *good;//--------------------------good part
  int *bad;//---------------------------bad part
  good = (int *)malloc(sizeof(int));
  bad = (int *)malloc(sizeof(int));
  int exist;//-------------------------indicate that if bad part exist or not
  int badfirst;//----------------------the index of the most right element such that S[i]<S[K]

  //input-------------------------------------------
  printf("How much is the digits of primitive sequence? \n");
  printf("Please input 1-9 number. (For example, if you think (0,1,2,0), you should input 4)\n");
  scanf("%d", &k);
  k = k - 1;
  printf("\n");
  int *s;
  s = (int *)malloc(sizeof(int)*(k+1));
  if (s == NULL){
    exit(0);
  }

  for(int i=0 ; i<=k ;i++)
  {
    if(i==0)
    {
      printf("Please input 1st element from the left.(S[0])\n");
      scanf("%d", &pre_s);
      s[i] = pre_s;
    }
    if(i==1)
    {
      printf("Please input 2nd element from the left.(S[1])\n");
      scanf("%d", &pre_s);
      s[i] = pre_s;
    }
    if(i==2)
    {
      printf("Please input 3rd element from the left.(S[2])\n");
      scanf("%d", &pre_s);
      s[i] = pre_s;
    }
    if(i>=3)
    {
      printf("Please input %d th element from the left.(S[%d])\n",i+1,i);
      scanf("%d", &pre_s);
      s[i] = pre_s;
    }
  }

  printf("Please input parameter n of primitive sequence.\n");
  scanf("%d", &n);
  printf("\n");

  //output initial state-------------------------------------
  output(s,k,n);

  //main part----------------------------------------
  while (k != 0)
  {
    if (s[k]==0)//-----if S_k = 0
    {
      k = k - 1;
      s = (int *)realloc(s,sizeof(int)*(k+1));
      n = n + 1;
    }
    else //-----if S_k != 0
    {
      exist = 0;
      for (int i=0 ; i<=k ;i++)
      {
        //if bad part exist---------------------------------
        if (s[k-i]<s[k])
        {
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
        }
        //if bad part don't exist-----------------------------
        if (i==k && exist==0)
        {
          badfirst = k;
          good = (int *)realloc(good,sizeof(int)*(badfirst));
          for (int j=0; j<badfirst ;j++)
          {
            good[j] = s[j];
          }
          free(bad);
        }

      }
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
        //----good part----
        for (int i=0 ; i<badfirst; i++){
          s[i] = good[i];
        }
        //----copy bad part-------
        for (int i=0 ; i<n; i++)
        {
          for (int j=0 ; j<k-badfirst; j++){
            s[badfirst + i*(k-badfirst) + j] = bad[j];
          }
        }
        k = badfirst+(k-badfirst)*n-1;//update k
      }

    }

    //output new sequence-----------------------------------------------
    output(s,k,n);
  }//while

  //final output--------------------------------------------------------
  if (s[0]==0){
    n = n + 1;
  }
  printf("finish!...%d\n", n);
  return 0;
}//main


//function of output-----------------------------------------------------
void output(int s[], int k, int n)
{
  printf("(");
  for (int i = 0;i < k; i++) {
    printf("%d,",s[i]);
  }
  printf("%d", s[k]);
  printf(")[%d]\n",n);
}
