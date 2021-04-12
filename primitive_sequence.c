//coding:utf-8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Input();
int Error(int error_num);
int ctoi(char c);
int output();
int BadAndGood();

int *s;
int k;
int n;


int main()
{
    Input();
    output();
    int roop = 0;
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
        BadAndGood();
      }

    //output new sequence
      output();
      roop = roop + 1;
      if (roop > 100) Error(5);
    }

  //final output--------------------------------------------------------
  if (s[0]==0){
    n = n + 1;
  }
  printf("final output: %d\n", n);
  return 0;

}

int Input()
{
    printf("Please input primitive sequence, like this: (0,1,2)[2]\n");
    printf(">>");
    char str[256];
	  scanf("%[^\n]",str);
    int str_num = strlen(str);
    k = (str_num - 6)/2;
    s = (int *)malloc(sizeof(int)*k+1);
    //printf("ok");
    for (int i=0; i<str_num; i++)
    {
        //printf("%c\n", str[i]);
        if (str[0] != '('){Error(0);}
        if (str[i] == ' '){Error(1);}
        if (str[i] == ',' && str[i+1] == ','){Error(2);}
        s[0] = ctoi(str[1]);
        if (str[i] == ','){
            if (i%2 != 0) Error(3);
            s[i/2] = ctoi(str[i+1]);
        }
        if (str[i] == ')'){
            if (str[i+1] == '[' && str[i+3] == ']'){
                n = ctoi(str[i+2]);
            }else{
                Error(4);
            }
        }
    }

    return 0;
}

int output()
{
    printf("(");
     for(int i=0; i<=k;i++){
        printf("%d",s[i]);
        if (i<k) printf(",");
        if (i==k) printf(")");
    }
    printf("[%d]\n",n);
}

int BadAndGood()
{
    int *good;//--------------------------good part
    int *bad;//---------------------------bad part
    good = (int *)malloc(sizeof(int));
    bad = (int *)malloc(sizeof(int));
    int exist;//-------------------------indicate that if bad part exist or not
    int badfirst;//----------------------the index of the most right element such that S[i]<S[K]

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

int Error(int error_num)
{
    switch (error_num)
    {
    case 0:
        printf("Error! First word must be '('");
        break;

    case 1:
        printf("Error! space ' ' is forbided");
        break;

    case 2:
        printf("Error! There must be an integer between ',' and ','");
        break;

    case 3:
        printf("Error! Input format is invalid. You can set only 0-9 number.");
        break;

    case 4:
        printf("Error! Next to ')' must be '[' 0-9 number ']'");
        break;

    case 5:
        printf("It is difficult to calculate more!");
        break;

    default:
        break;
    }
    //printf("E");
    exit(0);
}

int ctoi(char c) {
	switch (c) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default: Error(3);
	}
}
