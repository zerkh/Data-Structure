#include <iostream>
#include <string>
using namespace std;

#define NODE_MAX 100
typedef int ElemType;

//Parent Display
typedef struct
{
  ElemType data;
  int parent;
}TNode;

typedef struct
{
  TNode nodes[NODE_MAX];
  int r, n; //root's position and the amount of nodes
}PTree;

//Children Display
typedef struct CTNode
{
  int child;
  struct CTNode *next;
}*ChildPtr;

typedef struct
{
  ChildPtr firstchild;
  ElemType Data;
}CTBox;

typedef struct
{
  CTBox nodes[NODE_MAX];
  int r,n;
}CTree;

//Sib Display
typedef struct CSNode
{
  ElemType data;
  struct CSNode *firstchild, *rightsib;
}CSNode, *CSTree;











