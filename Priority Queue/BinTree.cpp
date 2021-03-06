//二项树

#include <iostream>
#include <cstdlib>
using namespace std;
#define MaxTrees 16
typedef int ElemType;
#define CapaCity 100

typedef struct TreeNode
{
  ElemType Element;
  struct TreeNode* LeftChild, *NextSibling;
}*BinTree;

typedef struct Collection
{
  int CurrentSize;
  BinTree TheTrees[MaxTrees];
}*BinQueue;

BinTree CombineTrees(BinTree B1, BinTree B2);
BinQueue Merge(BinQueue B1, BinQueue B2);
ElemType DeleteMin(BinQueue B);
BinQueue Init();
BinQueue Insert(ElemType X, BinQueue B);
bool IsEmpty(BinQueue B);

bool IsEmpty(BinQueue B)
{
  return (B->CurrentSize == 0)?true:false;
}

BinTree CombineTrees(BinTree B1, BinTree B2)
{
  if(B2->Element < B1->Element)
    {
      return CombineTrees(B2, B1);
    }
  B2->NextSibling = B1->LeftChild;
  B1->LeftChild = B2;
  return B1;
}

BinQueue Merge(BinQueue B1, BinQueue B2)
{
  BinTree T1, T2, Carry = NULL;

  if(B1->CurrentSize+B2->CurrentSize > CapaCity)
    {
      cerr << "Merge will exceed capacity!" << endl;
      exit (0);
    }
  
  B1->CurrentSize += B2->CurrentSize;
  
  for(int i = 0, j = 1; j <= B1->CurrentSize; j*=2, i++)
    {
      T1 = B1->TheTrees[i];
      T2 = B2->TheTrees[i];
      
      switch(!!T1+!!T2*2+!!Carry*4)
	{
	case 0:
	case 1:
	  break;
	case 2:
	  B1->TheTrees[i] = T2;
	  B2->TheTrees[i] = NULL;
	  break;
	case 3:
	  Carry = CombineTrees(T1, T2);
	  B1->TheTrees[i] = B2->TheTrees[i] = NULL;
	  break;
	case 4:
	  B1->TheTrees[i] = Carry;
	  Carry = NULL;
	  break;
	case 5:
	  Carry = CombineTrees(Carry, T1);
	  B1->TheTrees[i] = NULL;
	  break;
	case 6:
	  Carry = CombineTrees(Carry, T2);
	  B2->TheTrees[i] = NULL;
	  break;
	case 7:
	  B1->TheTrees[i] = Carry;
	  Carry = CombineTrees(T1, T2);
	  B2->TheTrees[i] = NULL;
	  break;
	}
    }

  return B1;
}

ElemType DeleteMin(BinQueue B)
{
  int MinTree;
  BinTree OldRoot, DeleteTree;
  BinQueue DeleteQueue;
  ElemType MinItem;
  
  if(IsEmpty(B))
    {
      cerr << "Empty bonomial queue!" << endl;
      return -1;
    }
  
  MinItem = 32767;
  
  for(int i = 0; i < MaxTrees; i++)
    {
      if(B->TheTrees[i] && B->TheTrees[i]->Element < MinItem)
	{
	  MinItem = B->TheTrees[i]->Element;
	  MinTree = i;
	}
    }

  DeleteTree = B->TheTrees[MinTree];
  OldRoot = DeleteTree;
  DeleteTree = DeleteTree->LeftChild;
  delete OldRoot;

  DeleteQueue = Init();
  DeleteQueue->CurrentSize = (1 << MinTree)-1;
  
  for(int i = MinTree-1; i >= 0; i--)
    {
      DeleteQueue->TheTrees[i] = DeleteTree;
      DeleteTree = DeleteTree->NextSibling;
      DeleteQueue->TheTrees[i]->NextSibling = NULL;
    }
  
  B->TheTrees[MinTree] = NULL;
  B->CurrentSize -= DeleteQueue->CurrentSize+1;
  B = Merge(B, DeleteQueue);

  return MinItem;
}

BinQueue Init()
{
  BinQueue B;
  
  B = new struct Collection;
  
  B->CurrentSize = 0;
  for(int i = 0; i < MaxTrees; i++)
    B->TheTrees[i] = NULL;

  return B;
}

BinQueue Insert(ElemType X, BinQueue B)
{
  BinQueue Single;
  
  Single = Init();
  Single->TheTrees[0] = new struct TreeNode;
  Single->TheTrees[0]->Element = X;
  Single->CurrentSize = 1;
  Single->TheTrees[0]->NextSibling = NULL;
  Single->TheTrees[0]->LeftChild = NULL;

  return Merge(B, Single);
}

int main()
{
  BinQueue B = Init();
  
  ElemType temp;

  cout << "Input the element:";
  cin >> temp;
  
  while(temp != -1)
    {
      Insert(temp ,B);
      cout << "Input the element:";
      cin >> temp;
    }

  cout << DeleteMin(B) << endl;
  cout << DeleteMin(B) << endl;

  return 0;
}

