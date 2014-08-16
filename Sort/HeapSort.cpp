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
  void HeapSort();
  void PercDown(int i, int N);
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

void Sort::HeapSort()
{
  int i;

    // 由向下上层层下滤,完成max堆的构建
  for(i = CurrentSize/2; i >= 0; i--)
    {
      PercDown(i, CurrentSize);
    }

  // i不进入下滤的范围,通过不断BuildHeap的方式将最大值移到0处
  for(i = CurrentSize-1; i > 0; i--)
    {
      Swap(i);
      PercDown(0, i);
    }
}


void Sort::PercDown(int i, int N)
{
  ElemType tmp;
  int Child;

  for(tmp = Fun[i]; LeftChild(i) < N; i = Child)
    {
      Child = LeftChild(i);
      
      if(Child != N-1 && Fun[Child] < Fun[Child+1])
	{
	  Child++;
	}

      if(tmp < Fun[Child])
	{
	  Fun[i] = Fun[Child];
	}
      else
	break;
    }
  Fun[i] = tmp;
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
  
  S.HeapSort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
