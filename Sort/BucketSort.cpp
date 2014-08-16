#include <iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 100
#define LeftChild(i) (2*i + 1)
clock_t start, end;

class Sort
{
  ElemType Fun[MaxSize];
  int CurrentSize;

public:
  void BucketSort();
  Sort();
  void Swap(int i);
  void Display();
};

void Sort::Swap(int i)
{
  ElemType tmp;

  tmp = Fun[0];
  Fun[0] = Fun[i];
  Fun[i] = tmp;
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

void Sort::BucketSort()
{
  int Buckets[100] = {0};

  for(int i = 0; i < CurrentSize; i++)
    {
      Buckets[Fun[i]]++;
    }

  int j = 0;
  for(int i = 0; i < 100; i++)
    {
      while(Buckets[i] != 0)
	{
	  Fun[j++] = i;
	  Buckets[i]--;
	}
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
  
  S.BucketSort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
