//左式堆

#include <iostream>
#include <cstdlib>
using namespace std;

struct TreeNode;
typedef struct TreeNode* PriorityQueue;
typedef int ElemType;

ElemType FindMin(PriorityQueue P);
bool IsEmpty(PriorityQueue P);
PriorityQueue Merge(PriorityQueue P1, PriorityQueue P2);
PriorityQueue Merge1(PriorityQueue P1, PriorityQueue P2);
void SwapChildren(PriorityQueue P);

//解决左式堆与二叉堆Insert的矛盾
#define Insert(Elem, P) (P = Insert1(Elem, P))
#define DeleteMin(P) (P = DeleteMin1(P))

PriorityQueue Insert1(ElemType Elem, PriorityQueue P);
PriorityQueue DeleteMin1(PriorityQueue P);

struct TreeNode
{
  ElemType Element;
  PriorityQueue Left, Right;
  int Npl;
};

PriorityQueue Merge(PriorityQueue P1, PriorityQueue P2)
{
  if(P1 == NULL)
    {
      return P2;
    }
  if(P2 == NULL)
    {
      return P1;
    }
  if(P1->Element <  P2->Element)
    {
      Merge1(P1, P2);
    }
  else
    {
      Merge1(P2, P1);
    }
}

PriorityQueue Merge1(PriorityQueue P1, PriorityQueue P2)
{
  if(P1->Left == NULL)
    {
      P1->Left = P2;
    }
  else
    {
      P1->Right = Merge(P1->Right, P2);
      
      if(P1->Left->Npl < P1->Right->Npl)
	{
	  SwapChildren(P1);
	}

      P1->Npl = P1->Right->Npl + 1;
    }

  return P1;
}

PriorityQueue Insert1(ElemType Elem, PriorityQueue P)
{
  PriorityQueue SigleNode;
  
  SigleNode = new struct TreeNode;
  if(SigleNode == NULL)
    {
      cerr << "Out of space!" << endl;
      return P;
    }
  SigleNode->Element = Elem;
  SigleNode->Npl = 0;
  SigleNode->Left = NULL;
  SigleNode->Right = NULL;

  return Merge(SigleNode, P);
}

void SwapChildren(PriorityQueue P)
{
  PriorityQueue temp;
  
  temp = P->Left;
  P->Left = P->Right;
  P->Right = temp;
}

PriorityQueue DeleteMin1(PriorityQueue P)
{
  PriorityQueue LeftHeap, RightHeap;

  if(IsEmpty(P))
    {
      cerr << "The priorityqueue is empty!" << endl;
      return P;
    }

  cout << FindMin(P) << endl;;
  LeftHeap = P->Left;
  RightHeap = P->Right;

  delete P;

  P = Merge(LeftHeap, RightHeap);
  return P;
}

bool IsEmpty(PriorityQueue P)
{
  return (P == NULL)?true:false;
}

ElemType FindMin(PriorityQueue P)
{
      return P->Element;
}

int main()
{
  PriorityQueue P;
  
  P = NULL;
  
  ElemType temp;

  cout << "Input the element:";
  cin >> temp;
  
  while(temp != -1)
    {
      Insert(temp ,P);
      cout << "Input the element:";
      cin >> temp;
    }

  DeleteMin(P);
  DeleteMin(P);

  return 0;
}
