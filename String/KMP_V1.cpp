#include <iostream>
#include <string.h>
using namespace std;

void get_next(char BeMat[], int next[])
{
  int i, j, len;
  
  len = strlen(BeMat);
  i = 1;
  j = 0;
  next[0] = 0;

  while(i < len)
    {
      if(j == 0 || BeMat[i] == BeMat[j])
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

int KMP_Sort(char Mat[], char BeMat[], int pos)
{
  int i, j, len, Belen;
  int next[255];

  i = pos;
  j = 0;

  len = strlen(Mat);
  Belen = strlen(BeMat);

  get_next(BeMat, next);

  while(i < len && j < Belen)
    {
      if(j == 0 || Mat[i] == BeMat[j])
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
  char Mat[100], BeMat[100];
  int pos;

  cout << "Mat:";
  cin >> Mat;
  cout << endl;
  cout << "BeMat";
  cin >> BeMat;
  cout << endl;
  cout << "pos:";
  cin >> pos;
  cout << endl;
  cout << KMP_Sort(Mat, BeMat, pos) << endl;

  return 0;
}
