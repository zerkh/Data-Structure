#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

typedef int ElemType;
typedef struct TreeNode
{
  struct TreeNode *Left, *Right;
  int Npl;
  ElemType Data;
}*PriorityQueue;

void Initialize(PriorityQueue &PQ);
PriorityQueue Merge1(PriorityQueue PQ1, PriorityQueue PQ2);
PriorityQueue Merge(PriorityQueue PQ1, PriorityQueue PQ2);
PriorityQueue Insert1(PriorityQueue PQ, ElemType Data);
PriorityQueue DeleteMin1(PriorityQueue PQ);
ElemType FindMin(PriorityQueue PQ);
#define Insert(PQ, Data) (PQ = Insert1(PQ, Data))
#define DeleteMin(PQ) (PQ = DeleteMin1(PQ))

void Initialize(PriorityQueue &PQ)
{
  PQ = NULL;
}

PriorityQueue Merge1(PriorityQueue PQ1, PriorityQueue PQ2)
{
  if(PQ1->Left == NULL)
    {
      PQ1->Left = PQ2;
    }
  else
    {
      PQ1->Right = Merge(PQ1->Right, PQ2);

      if(PQ1->Left->Npl < PQ1->Right->Npl)
	{
	  PriorityQueue Temp;
	  Temp = PQ1->Right;
	  PQ1->Right = PQ1->Left;
	  PQ1->Left = Temp;
	}
      
      PQ1->Npl = PQ1->Right->Npl+1;
    }

  return PQ1;
}

PriorityQueue Merge(PriorityQueue PQ1, PriorityQueue PQ2)
{
  if(PQ1 == NULL)
    {
      return PQ2;
    }

  if(PQ2 == NULL)
    {
      return PQ1;
    }

  if(PQ1->Data < PQ2->Data)
    {
     return Merge1(PQ1, PQ2);
    }
  else
    {
     return  Merge1(PQ2, PQ1);
    }
}

PriorityQueue Insert1(PriorityQueue PQ, ElemType Data)
{
  PriorityQueue InNode;
    
  InNode = new struct TreeNode;

  if(InNode == NULL)
    {
      cerr << "Out of space!" << endl;
      exit(0);
    }
  else
    {
      InNode->Data = Data;
      InNode->Left = InNode->Right = NULL;
      InNode->Npl = 0;
      PQ = Merge(PQ, InNode);
    }
  
  return PQ;
}

PriorityQueue DeleteMin1(PriorityQueue PQ)
{
  PriorityQueue Temp, TempLeft, TempRight;
  
  Temp = PQ;
  TempLeft = PQ->Left;
  TempRight = PQ->Right;
  PQ = Merge(TempLeft, TempRight);
  
  delete Temp;

  return PQ;
}

ElemType FindMin(PriorityQueue PQ)
{
  if(PQ == NULL)
    {
      cerr << "Empty." << endl;
      return -1;
    }
  
  return PQ->Data;
}

int main()
{
  PriorityQueue PQ;
  
  Initialize(PQ);
  
  ElemType InsertElem;
  
  cout << "Insert the data:" << endl;
  while(cin >> InsertElem && InsertElem != -1)
    {
      Insert(PQ, InsertElem);
    }

  cout << FindMin(PQ) << endl;
  DeleteMin(PQ);
  cout << FindMin(PQ) << endl;
  DeleteMin(PQ);
  cout << FindMin(PQ) << endl;
  DeleteMin(PQ);
  cout << FindMin(PQ) << endl;
  DeleteMin(PQ);
  cout << FindMin(PQ) << endl;
  DeleteMin(PQ);
  
  return 0;
}
