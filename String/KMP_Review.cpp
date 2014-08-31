#include <iostream>
#include <cstring>
using namespace std;

void get_next(char Bestr[], int next[]);
int KMP(char str[], char Bestr[], int Pos);

void get_next(char Bestr[], int next[])
{
  int len;
  len = strlen(Bestr);

  next[0] = 0;
  int i = 1, j = 0;

  while(i < len)
    {
      if(j == 0 || Bestr[i]==Bestr[j])
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

int KMP(char str[], char Bestr[], int pos)
{
  int next[255], i, j;
  
  i = pos, j = 0;
  int len = strlen(str), Belen = strlen(Bestr);
  get_next(Bestr, next);

  while(i < len && j < Belen)
    {
      if(j == 0 || str[i] == Bestr[j])
	{
	  i++;
	  j++;
	}
      else
	{
	  j = next[j];
	}
    }

  if(j >= Belen)
    {
      return i-Belen+1;
    }
  else
    {
      return 0;
    }
}

int main()
{
  char str[100], Bestr[100];
  int Pos;

  cout << "str:";
  cin >> str;
  cout << "Bestr:";
  cin >> Bestr;
  cout << "Pos:";
  cin >> Pos;

  cout << "\n" << KMP(str, Bestr, Pos) << endl;

  return 0;
}
