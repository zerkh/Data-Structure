//线索树

#include <iostream>
#include <string>
using namespace std;

typedef char ElemType;

typedef struct ThTree
{
  ElemType data;
  struct ThTree *Left, *Right;
  bool Lflag, Rflag;
}*Tree, TNode;

TNode *pre = NULL;

void InitTree(Tree &T)
{
  T = NULL;
}

void PreCreateTree(Tree &T)
{
  ElemType ch;

  cout << "输入该节点的数据:";
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

      PreCreateTree(T->Left);
      if(T->Left)
	{
	  T->Lflag = false;
	}
      PreCreateTree(T->Right);
      if(T->Right)
	{
	  T->Rflag = false;
	}
    }
}

void PreThreading(Tree &T)
{
      if(T)
	{
	  PreThreading(T->Left);

	  if(!T->Left)
	    {
	      T->Lflag = true;
	      T->Left = pre;//赋值后无限循环,只能中序
	    }
	  if(!pre->Right)
	    {
	      pre->Rflag = true;
	      pre->Right = T;
	    }
      
	  pre = T;

	  PreThreading(T->Right);
	}
}

void CreateThreading(Tree &Thrt, Tree &T)
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
      PreThreading(T);
      pre->Right = Thrt;
      pre->Rflag = true;
      Thrt->Right = pre;
    }
}

void PreOrderTraverse(Tree &T)
{
  Tree p;
  p = T->Left;

  while(p != T)
    {
       while(p->Lflag == false)
	 {
	   p = p->Left;
	 }
  
       cout << "此节点值为:" << p->data << endl;
       while(p->Rflag == true && p->Right != T)
	 {
	   p = p->Right;
	   cout << "此节点值为:" << p->data << endl;
	 }
       p = p->Right;
    }
}

int main()
{
  Tree T, Thrt;
  InitTree(T);
  PreCreateTree(T);
  CreateThreading(Thrt, T);
  PreOrderTraverse(Thrt);

  return 0;
}
