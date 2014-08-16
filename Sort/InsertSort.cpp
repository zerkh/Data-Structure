#include <iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 100
clock_t start, end;

class Sort
{
  ElemType Fun[MaxSize];
  int CurrentSize;

public:
  void InsertSort();
  Sort();
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
    }
}

void Sort::InsertSort()
{
  int p;

  for(int i = 1; i < CurrentSize; i++)
    {
      int tmp = Fun[i];
      
      for(p = i; p > 0 && Fun[p-1] > tmp; p--)
	{
	  Fun[p] = Fun[p-1];
	}

      Fun[p] = tmp;
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
  
  S.InsertSort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
