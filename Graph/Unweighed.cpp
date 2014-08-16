#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define MaxSize 100
typedef int Vertex;
typedef char ElemType;

typedef struct ArcNode
{
  Vertex Pos;
  struct ArcNode * next;
}*Arc;

struct VerNode
{
  ElemType Data;
  struct ArcNode* FirstArc;
};

typedef struct QueueNode
{
  Vertex Pos;
  struct QueueNode* next;
}*Node, *Queue;

typedef struct TableNode
{
  bool Known;
  int Dist;
  int Path;
}*Table;

typedef struct VerBox
{
  struct VerNode AdjaList[MaxSize];
  int VerNum;
}*Graph;

void CreateGraph(Graph &G);
void Unweighed(Graph G, Table &T, Vertex S);
void InitTable(Table &T, int VerNum);
void Display(Graph G, Table T, Vertex S);
Queue CreateQueue();
void EnQueue(Queue &Q, Vertex Pos);
Vertex DeQueue(Queue &Q);
bool IsEmpty(Queue Q);

Queue CreateQueue()
{
  Queue Q;
  Q = NULL;
  
  return Q;
}

void EnQueue(Queue &Q, Vertex Pos)
{
  Node N, P;

  P = Q;
  N = new struct QueueNode;
  N->next = NULL;
  N->Pos = Pos;
  
  if(P == NULL)
    {
      Q = N;
      return;
    }

  while(P->next != NULL)
    {
      P = P->next;
    }

  P->next = N;
}

Vertex DeQueue(Queue &Q)
{
  Node P;
  Vertex num;
  
  P = Q;
  if(Q == NULL)
    {
      cerr << "The queue is empty!" << endl;
      return -1;
    }
  
  Q = P->next;
  num = P->Pos;
  delete P;

  return num;
}

bool IsEmpty(Queue Q)
{
  if(Q == NULL)
    {
      return true;
    }
  return false;
}

void InitTable(Table &T, int VerNum)
{
  T = new struct TableNode[VerNum];

  for(int i = 0; i <  VerNum; i++)
    {
      T[i].Known = false;
      T[i].Dist = -1;
      T[i].Path = 0;
    }
}

void CreateGraph(Graph &G)
{
  ifstream In("Elem1.in");
  streambuf *oldbuf = cin.rdbuf(In.rdbuf());

  G = new struct VerBox;
  G->VerNum = 0;
  Vertex V, W;
  ElemType Elem;
  int i = 0;
  
  cout << "Input the node:" << endl;;
  while(cin >> Elem && Elem != '#')
    {
      G->AdjaList[i].Data = Elem;
      G->VerNum++;
      G->AdjaList[i].FirstArc = NULL;
      i++;
    }
  
  cout << "Input the arc:" << endl;
  while(cin >> V >> W && V != -1 && W != -1)
    {
      Arc A, P;
      A = new struct ArcNode;
      A->next = NULL;
      A->Pos = W;
      
      P = G->AdjaList[V].FirstArc;
      if(P == NULL)
	{
	  G->AdjaList[V].FirstArc = A;
	  continue;
	}
      
      while(P->next != NULL)
	{
	  P = P->next;
	}
      P->next = A;
    }

  cin.rdbuf(oldbuf);
}

void Unweighed(Graph G, Table &T, Vertex S)
{
  Queue Q;
  Vertex V;

  Q = CreateQueue();
  EnQueue(Q, S);
  T[S].Dist = 0;
  T[S].Path = -1;

  while(!IsEmpty(Q))
    {
      V = DeQueue(Q);
      T[V].Known = true;
      
      Arc A;
      A = G->AdjaList[V].FirstArc;

      while(A != NULL)
	{
	  Vertex W;
	  W = A->Pos;
	  if(T[W].Dist == -1)
	    {
	      T[W].Dist = T[V].Dist+1;
	      T[W].Path = V;
	      EnQueue(Q, W);
	    }
	  A = A->next;
	}
    }
}

void Display(Graph G, Table T,  Vertex S)
{
  Vertex V;
  
  for(int i = 0; i < G->VerNum; i++)
    {
      if(T[i].Dist == -1)
	{
	  cout << "无法到达该节点" << endl;
	  continue;
	}
      
      cout << "到节点" << G->AdjaList[i].Data << "的最短距离为" << T[i].Dist << endl;
      cout << "逆向路径为:" << i;
      V = T[i].Path;
      while(V != S && V != -1)
	{
	  cout << " " << V;
	  V = T[V].Path;
	}
      cout << " " << S << endl;
    }
}

int main()
{
  Vertex S;
  Table T;

  Graph G = NULL;
  CreateGraph(G);
  cout << "Input the S:";
  cin >> S;

  InitTable(T, G->VerNum);
  Unweighed(G, T, S);
  Display(G, T, S);

  return 0;
}
