#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#define MinData -1;

typedef struct HeapStruct
{
  int Size;
  int Capacity;
  int *Elements;
}*PriorityQueue;

void Initialize(PriorityQueue &PQ);
void Insert(PriorityQueue &PQ, int Data);
int DeleteMin(PriorityQueue &PQ);
void Destroy(PriorityQueue &PQ);
bool IsEmpty(PriorityQueue PQ);
bool IsFull(PriorityQueue PQ);

void Initialize(PriorityQueue &PQ)
{
  PQ = new struct HeapStruct;

  if(PQ == NULL)
    {
      cerr << "Out of space." << endl;
      exit(0);
    }

  cout << "Input the capacity:";
  cin >> PQ->Capacity;
  
  PQ->Size = 0;
  PQ->Elements = new int[PQ->Capacity+1];
  PQ->Elements[0] = MinData;
}

void Insert(PriorityQueue &PQ, int Data)
{
  if(IsFull(PQ))
    {
      cerr << "The priorityqueue is full." << endl;
      return;
    }

  int i;
  for(i = ++PQ->Size; PQ->Elements[i/2] > Data; i /= 2)
    {
      PQ->Elements[i] = PQ->Elements[i/2];
    }
  
  PQ->Elements[i] = Data;
}

int DeleteMin(PriorityQueue &PQ)
{
  if(IsEmpty(PQ))
    {
      cerr << "The priorityqueue is empty." << endl;
      return -1;
    }

  int Min = PQ->Elements[1];
  int LastElem = PQ->Elements[PQ->Size--];
  int i, Child;

  for(i = 1; i*2 <= PQ->Size; i = Child)
    {
      Child = i*2;

      if(Child != PQ->Size && PQ->Elements[Child] > PQ->Elements[Child+1])
	{
	  Child++;
	}
      
      if(PQ->Elements[Child] < LastElem)
	{
	  PQ->Elements[i] = PQ->Elements[Child];
	}
      else
	{
	  break;
	}
    }

  PQ->Elements[i] = LastElem;

  return Min;
}

void Destroy(PriorityQueue &PQ)
{
  delete []PQ->Elements;
  delete PQ;
}

bool IsEmpty(PriorityQueue PQ)
{
  return PQ->Size==0 ?true: false;
}

bool IsFull(PriorityQueue PQ)
{
  return PQ->Size==PQ->Capacity ?true: false;
}

int main()
{
  PriorityQueue PQ;

  Initialize(PQ);

  int Data;

  cout << "Insert data:" << endl;
  while(cin >> Data && Data != -1)
    {
      Insert(PQ, Data);
    }

  cout << DeleteMin(PQ) << endl;
  cout << DeleteMin(PQ) << endl;
  cout << DeleteMin(PQ) << endl;

  Destroy(PQ);

  return 0;
}
