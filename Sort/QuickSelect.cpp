#include <iostream>
#include <fstream>
using namespace std;
typedef int ElemType;
#define MaxSize 100
#define Cutoff 3
clock_t start, end;

class Sort
{
  ElemType Fun[MaxSize];
  int CurrentSize;
  int K;

public:
  void InsertSort(ElemType Array[], int N);
  void QSelect(int Left, int Right);
  void QuickSelect();
  ElemType Median3(int Left, int Right);
  Sort();
  void Swap(int One, int Other);
  void Display();
};

Sort::Sort()
{
  CurrentSize = 0;
  ElemType temp;

  ifstream In("Elements.in");
  streambuf *oldbuf = cin.rdbuf(In.rdbuf());
  cout << "Input " << "1" << " element:";
  cin >> temp;
  for(int i = 0; i < MaxSize && temp != -1; i++)
    {
      Fun[i] = temp;
      CurrentSize++;
      cout << "Input " << i+2 << " element:";
      cin >> temp;
      cout << endl;
    }
  
  cin.rdbuf(oldbuf);
  cout << "Input the k:";
  cin >> K;
}

void Sort::Swap(int One, int Other)
{
  ElemType tmp;

  tmp = Fun[One];
  Fun[One] = Fun[Other];
  Fun[Other] = tmp;
}

void Sort::InsertSort(ElemType Array[], int N)
{
  int p;

  for(int i = 1; i < N; i++)
    {
      ElemType tmp;
      tmp = Fun[i];
      
      for(p = i; p > 0 && Fun[p-1] > tmp; p--)
	{
	  Fun[p] = Fun[p-1];
	}
      
      Fun[p] = tmp;
    }
}

ElemType Sort::Median3(int Left, int Right)
{
  int Center = (Left+Right)/2;

  if(Fun[Left] > Fun[Center])
    {
      Swap(Left, Center);
    }
  if(Fun[Left] > Fun[Right])
    {
      Swap(Left, Right);
    }
  if(Fun[Center] > Fun[Right])
    {
      Swap(Center, Right);
    }

  Swap(Center, Right-1);
  
  return Fun[Right-1];
}

void Sort::QuickSelect()
{
  QSelect(0, CurrentSize-1);
}

void Sort::QSelect(int Left, int Right)
{
  ElemType Pivot;

  if(Left+Cutoff >= Right)
    {
      Pivot = Median3(Left, Right);

      int i = Left;
      int j = Right-1;
      while(1)
	{  
	  while(Fun[++i] < Pivot){}
	  while(Fun[--j] > Pivot){}
      
	  if(i < j)
	    {
	      Swap(i, j);
	    }
	  else
	    {
	      break;
	    }
	}
      Swap(Fun[i], Fun[Right-1]);

      if(K <= i)
	{
	  QSelect(Left, i);
	}
      if(K > i+1)
	{
	  QSelect(i+1, Right);
	}
    }
  else
    {
      InsertSort(Fun+Left, Right-Left+1);
    }
}

void Sort::Display()
{
  cout << Fun[K-1] << endl;
  
  for(int i = 0; i < CurrentSize; i++)
    {
      cout << Fun[i] << ' ';
    }
  cout << endl;
}

int main()
{
  start = clock();

  Sort S;
  
  S.QuickSelect();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
