//Prim算法 与Dijkstra算法类似 但为无向图


#include <iostream>
#include <fstream>
using namespace std;

#define MaxSize 100
typedef int Vertex;
typedef char ElemType;
#define Infinity 32767
#define NotAVertex -1

typedef struct QueueNode
{
  Vertex Pos;
  struct QueueNode* next;
}*Node, *Queue;

typedef struct List
{
  bool Known;
  int Dist;
  Vertex Path;
}*Table;

typedef struct ArcNode
{
  Vertex TailPos;
  int Weight;
  struct ArcNode *next;
}*Arc;

struct VerNode
{
  Arc FirstArc;
  ElemType Data;
};

typedef struct VerBox
{
  struct VerNode AdjaList[MaxSize];
  int CurrentSize;
}*Graph;

void CreateGraph(Graph &G);
void InitTable(Graph &G, Table &T, Vertex Start);
void Dijkstra(Graph &G, Table &T);
void Display(Graph &G, Table &T);
Vertex FindMinDist(Graph &G, Table &T);
void DisPath(Graph &G, Table &T, Vertex Pos);
Queue CreateQueue();
void EnQueue(Queue &Q, Vertex Pos);
Vertex DeQueue(Queue &Q);
bool IsEmpty(Queue Q);
bool IsExist(Queue Q, Vertex W);
//具有负边值
void WeightNegative(Graph G, Table T, Vertex Start);

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

bool IsExist(Queue Q, Vertex W)
{
  Node P;
  P = Q;

  while(P != NULL)
    {
      if(P->Pos == W)
	{
	  return true;
	}
      P = P->next;
    }
  return false;
}

void CreateGraph(Graph &G)
{
  G = new struct VerBox;
  G->CurrentSize = 0;

  ifstream In("Elem2.in");
  streambuf *oldbuf = cin.rdbuf(In.rdbuf());

  cout << "Input the nodes:" << endl;
  for(int i = 0; i < MaxSize; i++)
    {
      ElemType Temp_Data;
      
      cin >> Temp_Data;
      if(Temp_Data == '#')
	{
	  break;
	}
      
      G->AdjaList[i].Data = Temp_Data;
      G->AdjaList[i].FirstArc = NULL;
      G->CurrentSize++;
    }

  cout << "Input the arc from head to tail and the weight:" << endl;
  Vertex V, W;
  int Temp_Weight;

  while(cin >> V >> W && V != -1 && W != -1)
    {
      cin >> Temp_Weight;
      
      Arc A;
      A = new struct ArcNode;
      A->TailPos = W;
      A->next = NULL;
      A->Weight = Temp_Weight;

      if(G->AdjaList[V].FirstArc == NULL)
	{
	  G->AdjaList[V].FirstArc = A;
	}
      else
	{
	  Arc P;
	  P = G->AdjaList[V].FirstArc;
	  
	  while(P->next != NULL)
	    {
	      P = P->next;
	    }
	  P->next = A;
	}

      A = new struct ArcNode;
      A->TailPos = V;
      A->next = NULL;
      A->Weight = Temp_Weight;

      if(G->AdjaList[W].FirstArc == NULL)
	{
	  G->AdjaList[W].FirstArc = A;
	}
      else
	{
	  Arc P;
	  P = G->AdjaList[W].FirstArc;
	  
	  while(P->next != NULL)
	    {
	      P = P->next;
	    }
	  P->next = A;
	}
    }
}

void InitTable(Graph &G, Table &T, Vertex Start)
{
  T = new struct List[G->CurrentSize];

  for(int i = 0; i < G->CurrentSize; i++)
    {
      T[i].Path = NotAVertex;
      T[i].Dist = Infinity;
      T[i].Known = false;
    }

  T[Start].Dist = 0;
}

Vertex FindMinDist(Graph &G, Table &T)
{
  Vertex MinPos = -1;
  int MinDist = Infinity;
  
  for(int i = 0; i < G->CurrentSize; i++)
    {
      if(T[i].Known == false)
	{
	  if(T[i].Dist < MinDist)
	    {
	      MinDist = T[i].Dist;
	      MinPos = i;
	    }
	}
    }

  return MinPos;
}

void Dijkstra(Graph &G, Table &T)
{
  Vertex V;

  while(1)
    {
      V = FindMinDist(G, T);
      
      if(V == NotAVertex)
	{
	  break;
	}
      
      T[V].Known = true;

      Arc P;
      P = G->AdjaList[V].FirstArc;
      while(P != NULL)
	{
	  if(T[P->TailPos].Known == false)
	    {
	      if(T[V].Dist+P->Weight < T[P->TailPos].Dist)
		{
		  T[P->TailPos].Dist = T[V].Dist+P->Weight;
		  T[P->TailPos].Path = V;
		}
	    }
	  P = P->next;
	}
    }
}

void Display(Graph &G, Table &T)
{
  for(int i = 0; i < G->CurrentSize; i++)
    {
      cout << "最小权值为" << T[i].Dist << endl;
      cout << "路径为 " << endl;
      DisPath(G, T, i);
      cout << endl;
    }
}

void DisPath(Graph &G, Table &T, Vertex Pos)
{
  if(T[Pos].Path != NotAVertex)
    {
      DisPath(G, T, T[Pos].Path);
      cout << " to ";
    }
  cout << Pos;
}

void WeightNegative(Graph G, Table T, Vertex Start)
{
  Queue Q;
  Vertex W, V;
  Q = CreateQueue();
  EnQueue(Q, Start);
  
  while(!IsEmpty(Q))
    {
      V = DeQueue(Q);
      
      Arc P;
      P = G->AdjaList[V].FirstArc;
      while(P != NULL)
	{
	  W = P->TailPos;
	  if(T[V].Dist+P->Weight < T[W].Dist)
	    {
	      T[W].Dist = T[V].Dist+P->Weight;
	      T[W].Path = V;
	      if(!IsExist(Q, W))
		EnQueue(Q, W); 
	    }
	  P = P->next;
	}
    }
}

int main()
{
  Graph G;
  Table T;
  
  CreateGraph(G);
  InitTable(G, T, 0);
  //  Dijkstra(G, T);
  WeightNegative(G, T, 0);
  Display(G, T);
  
  return 0;
}
