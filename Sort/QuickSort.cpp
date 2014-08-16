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

public:
  void InsertSort(ElemType Array[], int N);
  void QSort(int Left, int Right);
  void QuickSort();
  ElemType Median3(int Left, int Right);
  Sort();
  void Swap(int One, int Other);
  void Display();
};

Sort::Sort()
{
  CurrentSize = 0;
  ElemType temp;

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

void Sort::QuickSort()
{
  QSort(0, CurrentSize-1);
}

void Sort::QSort(int Left, int Right)
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

      QSort(Left, i);
      QSort(i+1, Right);
    }
  else
    {
      InsertSort(Fun+Left, Right-Left+1);
    }
}

void Sort::Display()
{
  for(int i = 0; i < CurrentSize; i++)
    {
      cout << Fun[i] << ' ';
    }

  cout << endl;
}

int main()
{
  start = clock();
  ifstream In("Elements.in");
  cin.rdbuf(In.rdbuf());

  Sort S;
  
  S.QuickSort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
