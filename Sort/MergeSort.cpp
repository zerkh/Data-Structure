#include <iostream>
#include <cstdlib>
using namespace std;
typedef int ElemType;
#define MaxSize 100
clock_t start, end;

class Sort
{
  ElemType Fun[MaxSize];
  int CurrentSize;

public:
  void MergeSort();
  void MSort(int Left, int Right, ElemType TmpArray[]);
  Sort();
  void Merge(int Left, int Center, int Right, ElemType TmpArray[]);
  void Display();
};

void Sort::MSort(int Left, int Right, ElemType TmpArray[])
{
  int Center;

  if(Left < Right)
    {
      Center = (Left + Right)/2;
      MSort(Left, Center, TmpArray);
      MSort(Center+1, Right, TmpArray);
      Merge(Left, Center+1, Right, TmpArray);
    }
}

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
    }
}

void Sort::MergeSort()
{
  ElemType *TmpArray;

  TmpArray = (ElemType*)malloc(sizeof(ElemType)*CurrentSize);

  if(TmpArray != NULL)
    {
      MSort(0, CurrentSize-1, TmpArray);
      free(TmpArray);
    }
  else
    {
      exit(-1);
    }
}


void Sort::Merge(int Left, int Center, int Right, ElemType TmpArray[])
{
  int i = Left;
  int j = Center;
  int k = 0;

  while(i < Center && j <= Right)
    {
      if(Fun[i] < Fun[j])
	{
	  TmpArray[k++] = Fun[i++];
	}
      else
	{
	  TmpArray[k++] = Fun[j++];
	}
    }
  
  if(i < Center)
    {
      for(; i < Center; i++)
	{
	  TmpArray[k++] = Fun[i];
	}
    }
  if(j <= Right)
    {
      for(; j <= Right; j++)
	{
	  TmpArray[k++] = Fun[j];
	}
    }

  for(i = Left, k = 0; i <= Right; i++, k++)
    {
      Fun[i] = TmpArray[k];
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
  
  Sort S;
  
  S.MergeSort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
