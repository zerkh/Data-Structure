#include <iostream>
#include <string>
using namespace std;

typedef char ElemType;

typedef struct TNode
{
  ElemType data;
  
  struct TNode *Left, *Right;
  
  bool Lflag, Rflag;
}*Tree, TNode;

Tree pre = NULL;

void InitTree(Tree &T)
{
  T = NULL;
}

void PreCreateTree(Tree &T)
{
  ElemType ch; 
  cout << "请输入该节点的值:";
  cin >> ch;
  cout << endl;
  
  if(ch == '#')
    {
      T = NULL;
    }
  else
    {
      T = new TNode;
      T->data = ch;
      T->Lflag = false;
      T->Rflag = false;
      
      PreCreateTree(T->Left);
      PreCreateTree(T->Right);
    }
}

void InThreading(Tree &T)
{
  if(T)
    {
      InThreading(T->Left);

      if(!T->Left)
	{
	  T->Lflag = true;
	  T->Left = pre;
	}
      if(!pre->Right)
	{
	  pre->Rflag = true;
	  pre->Right = T;
	}
      pre = T;

      InThreading(T->Right);
    }
}

void Thread(Tree &Thrt, Tree &T)
{
  Thrt = new TNode;
  Thrt->Lflag = false;
  Thrt->Rflag = true;
  Thrt->Right = Thrt;
  
  if(T == NULL)
    {
      Thrt->Left = Thrt;
    }
  else
    {
      pre = Thrt;
      Thrt->Left = T;
      InThreading(T);
      pre->Right = Thrt;
      Thrt->Right = pre;
      pre->Rflag = true;
    }
}

void InOrderTraverse(Tree &T)
{
  Tree p;

  p = T->Left;
  while(p != T)
    {
      while(p->Lflag == false)
	{
	  p = p->Left;
	}

      cout << "该节点的值为:" << p->data << endl;
      while(p->Rflag == true && p->Right != T)
	{
	  p = p->Right;
	  cout << "该节点的值为:" << p->data << endl;
	}

      p = p->Right;
    }
}

int main()
{
  Tree T, Thrt;
  InitTree(T);
  PreCreateTree(T);
  Thread(Thrt, T);
  InOrderTraverse(Thrt);

  return 0;
}
