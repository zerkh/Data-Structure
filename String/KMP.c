#include <stdio.h>
#include <string.h>

void get_next(char Mstr[], int next[])
{
  int i = 1; 
  int j = 0;

  next[0] = 0;
  next[1] = 0;

  while(i <= Mstr[0])
    {
      if(j == 0 || Mstr[i] == Mstr[j])
	{
	  i++;
	  j++;
	  next[i] = j;
	}
      else
	j = next[j];
    }
}

int KMP_Match(char str[], char Mstr[], int pos)
{
  int next[255];
  int i, j;
  
  get_next(Mstr, next);

  i = pos;
  j = 1;

  while(i <= str[0] && j <= Mstr[0])
    {
      if(j == 0 || str[i] == Mstr[j])
	{
	  i++;
	  j++;
	}
      else
	{
	  j = next[j];
	}
    }

  if(j > Mstr[0])
    return i-Mstr[0];
  else
    return 0;
}

int main()
{
  char str[100], Mstr[10];
  int get_pos;
  int pos;
  
  printf("输入字符串:");
  scanf("%s", str+1);
  printf("\n");
  str[0] = '0';
  str[0] = strlen(str)-1;

  printf("输入要查找的字符串:");
  scanf("%s", Mstr+1);
  printf("\n");
  Mstr[0] = '0';
  Mstr[0] = strlen(Mstr)-1;

  printf("输入pos值:");
  scanf("%d", &pos);
  printf("\n");

  get_pos = KMP_Match(str, Mstr, pos);
  
  printf("该字符串在pos后的%d处\n", get_pos);

  return 0;
}
