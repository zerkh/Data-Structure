#include <iostream>
using namespace std;
typedef int ElemType;
#define MaxSize 100

class Sort
{
  int CurrentSize;
  ElemType Fun[MaxSize];

public:
  Sort();
  void Shellsort();
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

void Sort::Shellsort()
{
  int Increment = CurrentSize/2;

  for(; Increment > 0; Increment /= 2)
    {
      for(int i = Increment; i < CurrentSize; i++)
	{
	  ElemType tmp;
	  int j;
	  
	  tmp = Fun[i];
	  for(j = i; j >= Increment; j -= Increment)
	    {
	      if(tmp < Fun[j-Increment])
		{
		  Fun[j] = Fun[j-Increment];
		}
	      else
		{
		  break;
		}
	    }
	  Fun[j] = tmp;
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
  clock_t start, end;

  start = clock();
  
  Sort S;
  
  S.Shellsort();
  S.Display();


  end = clock();

  cout << "Time:" << (double)(end-start)/CLOCKS_PER_SEC << "S" << endl;
  return 0;
}
