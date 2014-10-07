#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Position;

typedef struct Student
{
  char Stu_Num[20];
  char Name[20];
}*Stu;

typedef struct Index_Table
{
  char Key[20];
  int Start;
  int Len;
}*ITbl;

int Create_Table(Stu st);
int Create_Index(Stu st, int st_Len, ITbl IT);
char* Left(char Str[], int Len);
Position BinSearch(ITbl IT, int Len,char Key[]);
void Find(Stu st, int st_Len, ITbl IT, int it_Len);

int Create_Table(Stu st)
{
  int i = 0, j;
  char Num[20], Name[20];

  freopen("data1.in", "r", stdin);

  while((scanf("%s%s", Num, Name) != EOF) && Num[0] != '#')
    {
      strcpy(st[i].Stu_Num, Num);
      strcpy(st[i++].Name, Name);
    }

  printf("原表为:\n");
  for(j = 0; j < i; j++)
    {
      printf("%s %s\n", st[j].Stu_Num, st[j].Name);
    }

  fclose(stdin);

  return i;
}

int Create_Index(Stu st, int st_Len, ITbl IT)
{
  int i, j, k = 0;
  char Key[20];
  
  j = 0;

  strcpy(IT[j].Key,Left(st[0].Stu_Num, 4));
  IT[j].Key[4]='\0';
  IT[j].Start = 0;
  
  strcpy(Key,Left(st[0].Stu_Num, 4));
  Key[4] = '\0';

  for(i = 0; i < st_Len; i++)
    {
      strcpy(Key,Left(st[i].Stu_Num, 4));
      Key[4] = '\0';
      
      if(strcmp(IT[j].Key, Key))
	{
	  IT[j++].Len = k;
	  strcpy(IT[j].Key,Left(st[i].Stu_Num, 4));
	  IT[j].Key[4]='\0';
	  IT[j].Start = i;
	  k = 0;
	}
      k++;
    }
  
  IT[j].Len = k;

  printf("索引表为:\n");
  for(k = 0; k <= j; k++)
    {
      printf("%s %d %d\n", IT[k].Key, IT[k].Start, IT[k].Len);
    }

  return j;
}
 
char* Left(char Str[], int Len)
{
  char Key[20];
  int i;

  for(i = 0; i < Len; i++)
    {
      Key[i] = Str[i];
    }
  Key[i+1] = '\0';

  return Key;
}

Position BinSearch(ITbl IT, int Len,char Key[])
{
  int Left, Right, Mid;
  int i;

  Left = 0;
  Right = Len-1;

  while(Left <= Right)
    {
      Mid = (Left+Right)/2;

      if(strcmp(IT[Mid].Key, Key) == 0)
	{
	  return Mid;
	}
      else if(strcmp(IT[Mid].Key, Key) > 0)
	{
	  Right = Mid-1;
	}
      else
	{
	  Left = Mid+1;
	}
    }

  return -1;
}

void Find(Stu st, int st_Len, ITbl IT, int it_Len)
{
  char Num[20];
  freopen("data2.in", "r", stdin);


  while((scanf("%s", Num) != EOF) && Num[0] != '#')
    {
      int i;
      Position pos = BinSearch(IT, it_Len, Left(Num, 4));
      int Start = IT[pos].Start, Len = IT[pos].Len;
      
      for(i = Start; i < Start+Len; i++)
	{
	  if(strcmp(st[i].Stu_Num, Num) == 0)
	    {
	      break;
	    }
	}

      printf("学号: %s 姓名:%s\n", st[i].Stu_Num, st[i].Name);
    }
}

int main()
{
  Stu st;
  ITbl IT;
  int st_len;
  int IT_len;

  st = (Stu)malloc(sizeof(struct Student)*100);
  IT = (ITbl)malloc(sizeof(struct Index_Table)*100);

  st_len = Create_Table(st);
  IT_len =  Create_Index(st,st_len,IT);

  Find(st, st_len,IT,IT_len);

  return 0;
}

 
