//二叉堆的实现

#include <iostream>
#include <string>
#include <cstdlib>
#define MinData -1
using namespace std;

typedef int ElemType;

struct Heap;
typedef struct Heap *PriorityQueue;

PriorityQueue Init(int MaxElements);
void Destroy(PriorityQueue P);
void MakeEmpty(PriorityQueue P);
void Insert(ElemType elem, PriorityQueue P);
ElemType DeleteMin(PriorityQueue P);
ElemType FindMin(PriorityQueue P);
bool IsEmpty(PriorityQueue P);
bool IsFull(PriorityQueue P);

struct Heap
{
  ElemType *Elements;
  int Size;
  int Capacity;
};

PriorityQueue Init(int MaxElements)
{
  PriorityQueue P;
  
  P = new struct Heap;
  if(P == NULL)
    {
      cerr << "Out of space." << endl;
    }
  
  P->Elements = (ElemType*)malloc((MaxElements+1)*sizeof(ElemType));
  P->Capacity = MaxElements;
  P->Size = 0;
  P->Elements[0] = MinData;

  return P;
}

void Insert(ElemType elem, PriorityQueue P)
{
  if(IsFull(P))
    {
      cerr << "Priority queue is full." << endl;
      return;
    }
  
  int i;

  for(i = ++P->Size; P->Elements[i/2] > elem; i /= 2)
    {
      P->Elements[i] = P->Elements[i/2];
    }

  P->Elements[i] = elem;
}

ElemType DeleteMin(PriorityQueue P)
{
  int child;
  ElemType MinElement, LastElement;

  if(IsEmpty(P))
    {
      cerr << "Priority queue is empty." << endl;
      return P->Elements[0];
    }
  
  MinElement = P->Elements[1];
  LastElement = P->Elements[P->Size--];

  for(int i = 1; i * 2 <= P->Size; i = child)
    {
      child = i*2;
      
      if(child != P->Size && P->Elements[child+1]<P->Elements[child])
	{
	  child++;
	}
      
      if(P->Elements[child] < LastElement)
	{
	  P->Elements[i] = P->Elements[child];
	}
      else
	{
	  break;
	}
    }
  
  return MinElement;
}

void Destroy(PriorityQueue P)
{
  delete []P->Elements;
  delete P;
}

void MakeEmpty(PriorityQueue P)
{
  P->Size = 0;
}

bool IsEmpty(PriorityQueue P)
{
  return (P->Size == 0)?true:false;
}

ElemType FindMin(PriorityQueue P)
{
  if(IsEmpty(P))
    {
      cerr << "The priority queue is empty." << endl;
      return P->Elements[0];
    }
  
  return P->Elements[1];
}

bool IsFull(PriorityQueue P)
{
  return (P->Size == P->Capacity)?true:false;
}

int main()
{
  PriorityQueue P;
  int MaxElements;

  cout << "Input the amount of elements:";
  cin >> MaxElements;

  P = Init(MaxElements);
  
  ElemType elem;
  
  cout << "Input the elem:";
  cin >> elem;

  while(elem != -1)
    {
      Insert(elem, P);
      cout << "Input the elem:";
      cin >> elem;
    }
  
  
  elem = DeleteMin(P);
  cout << elem << endl;
  elem = FindMin(P);
  cout << elem << endl;
  elem = DeleteMin(P);
  cout << elem << endl;
  elem = FindMin(P);
  cout << elem << endl;

  return 0;
}
