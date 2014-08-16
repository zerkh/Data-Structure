#include <iostream>
#include <string.h>
using namespace std;

void get_next(char Mstr[], int next[])
{
  int i, j;
  int Mlen;

  i = 1;
  j = 0;
  Mlen = strlen(Mstr);
  next[0] = 0;
  
  while(i < Mlen)
    {
      if(j == 0 || Mstr[i] == Mstr[j])
	{
	  next[i] = j;
	  i++;
	  j++;
	}
      else
	{
	  j = next[j];
	}
    }
}

int KMP(char str[], char Mstr[], int pos)
{
  int i, j, len, Mlen;
  int next[255];

  len = strlen(str);
  Mlen = strlen(Mstr);
  
  get_next(Mstr, next);

  i = pos;
  j = 0;

  while(i < len && j < Mlen)
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

  if(j >= Mlen)
    {
      return i-Mlen+1;
    }
  else
    return 0;
}

int main()
{
  char str[100], Mstr[100];
  int pos;
  
  cout << "str:";
  cin >> str;
  cout << endl;
  cout << "Mstr:";
  cin >> Mstr;
  cout << endl;
  cout << "pos:";
  cin >> pos;
  cout << endl;
  
  cout << KMP(str, Mstr, pos) << endl;

  return 0;
}
