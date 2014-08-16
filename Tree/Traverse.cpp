//树的遍历

#include <iostream>
#include <string>
using namespace std;

typedef char ElemType;

typedef struct TNode
{
  ElemType data;
  struct TNode *Left, *Right;
}*Tree, TNode;

void InitTree(Tree &T);
void DestroyTree(Tree &T);
void CreateTree(Tree &T);
void ClearTree(Tree &T);
bool TreeEmpty(Tree &T);
int TreeDepth(Tree &T);
TNode* Root(Tree &T);
ElemType Value(Tree &T);
void Assign(Tree &T, ElemType cur_e, ElemType value);
TNode* Parent(Tree &T, ElemType cur_e);
TNode* LeftChild(Tree &T, ElemType cur_e);
TNode* RightSibling(Tree &T, ElemType cur_e);
void InsertChild(Tree &T, TNode *node, Tree T_insert);
void DeleteChild(Tree &T, TNode *node);
void PreTraverse(Tree &T);

void InitTree(Tree &T)
{
  T = NULL;
}

void DestroyTree(Tree &T)
{
  if(T == NULL)
    {
      return;
    }
  DestroyTree(T->Left);
  DestroyTree(T->Right);
  delete T;
}

void CreateTree(Tree &T)
{
  ElemType ch;

  cout << "输入节点数据:";
  cin >> ch;
  cout << endl;

  if(ch == '#')
    {
      T = NULL;
    }
  else
    {
      T = new TNode;
      if(T == NULL)
	{
	  cerr << "Overflow" << endl;
	}
      T->data = ch;
      CreateTree(T->Left);
      CreateTree(T->Right);
    }
}

void PreOrderTraverse(Tree &T)
{
  if(T == NULL)
    {
      return;
    }

  cout << "此节点值为:";
  cout << T->data << endl;
 
  PreOrderTraverse(T->Left);
  PreOrderTraverse(T->Right);
}

void InOrderTraverse(Tree &T)
{
  if(T == NULL)
    {
      return;
    }

  InOrderTraverse(T->Left);
  cout << "此节点值为:";
  cout << T->data << endl;
  InOrderTraverse(T->Right);
}

void PostOrderTraverse(Tree &T)
{
  if(T == NULL)
    {
      return;
    }

  PostOrderTraverse(T->Left);
  PostOrderTraverse(T->Right);
  cout << "此节点值为:";
  cout << T->data << endl;
}

int main()
{
  Tree T;
  int select;

  InitTree(T);
  CreateTree(T);

  cout << "1.前序" << endl;
  cout << "2.中序" << endl;
  cout << "3.后序" << endl;

  cout << "请输入遍历方式" << endl;
  cin >> select;

  switch(select)
    {
    case 1:
      PreOrderTraverse(T);
      break;
    case 2:
      InOrderTraverse(T);
      break;
    case 3:
      PostOrderTraverse(T);
    }

  return 0;
}
