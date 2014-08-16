//最小生成树的Kruskal算法

//Prim算法 与Dijkstra算法类似 但为无向图


#include <iostream>
#include <fstream>
using namespace std;

#define MaxSize 100
typedef int SetType;
typedef int Vertex;
typedef int DisjSet[MaxSize];
typedef char ElemType;
typedef struct HeapNode Edge;
#define Infinity 32767
#define NotAVertex -1

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

typedef struct Heap *PriorityQueue;

struct HeapNode
{
  Vertex HeadPos, TailPos;
  int Weight;
};

struct Heap
{
  Edge edges[MaxSize+1];
  int Size;
  int Capacity;
};

void CreateGraph(Graph &G);
void Initialize(DisjSet S);
SetType Find(int X, DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
void Display(Graph &G, Table &T);
void DisPath(Graph &G, Table &T, Vertex Pos);
void ReadGraphIntoHeap(Graph G, PriorityQueue &Q);
Edge DeleteMin(PriorityQueue &Q);
void Kruskal(Graph G);

void Kruskal(Graph G)
{
  int EdgeAccepted = 0;
  DisjSet S;
  PriorityQueue H;
  Vertex U, V;
  SetType Uset, Vset;
  Edge E;

  Initialize(S);
  ReadGraphIntoHeap(G, H);

  while(EdgeAccepted < G->CurrentSize-1)
    {
      E = DeleteMin(H);
      U = E.HeadPos;
      V = E.TailPos;
      Uset = Find(U, S);
      Vset = Find(V, S);
      if(Uset != Vset)
	{
	  EdgeAccepted++;
	  SetUnion(S, Uset, Vset);
	  cout << U << ' ' << V << endl;
	}
    }
}

void ReadGraphIntoHeap(Graph G, PriorityQueue &Q)
{
  Q = new struct Heap;
  
  Q->Size = 0;
  Q->Capacity = MaxSize;
  Q->edges[0].Weight = -1;
  Q->edges[0].HeadPos = -1;
  Q->edges[0].TailPos = -1;
  
  for(int i = 0; i < G->CurrentSize; i++)
    {
      Arc P;
      P = G->AdjaList[i].FirstArc;

      while(P != NULL)
	{
	  int Elem = P->Weight;
	  int j;
	  
	  for(j = ++Q->Size; Q->edges[j/2].Weight > Elem; j /= 2)
	    {
	      Q->edges[j].Weight = Q->edges[j/2].Weight;
	      Q->edges[j].HeadPos = Q->edges[j/2].HeadPos;
	      Q->edges[j].TailPos = Q->edges[j/2].TailPos;
	    }
	  Q->edges[j].Weight = P->Weight;
	  Q->edges[j].HeadPos = i;
	  Q->edges[j].TailPos = P->TailPos;

	  P = P->next;
	}
    }
}

Edge DeleteMin(PriorityQueue &Q)
{
  int Child;
  Edge MinData;
  Edge LastElement;
  LastElement.Weight = Q->edges[Q->Size].Weight;
  LastElement.HeadPos = Q->edges[Q->Size].HeadPos;
  LastElement.TailPos = Q->edges[Q->Size--].TailPos;
  MinData.Weight = Q->edges[1].Weight;
  MinData.HeadPos = Q->edges[1].HeadPos;
  MinData.TailPos = Q->edges[1].TailPos;

  int i;
  for(i = 1; i*2 <= Q->Size; i = Child)
    {
      Child = i*2;

      if(Child != Q->Size && Q->edges[Child+1].Weight < Q->edges[Child].Weight)
	{
	  Child++;
	}
      if(Q->edges[Child].Weight < LastElement.Weight)
	{
	  Q->edges[i].Weight = Q->edges[Child].Weight;
	  Q->edges[i].HeadPos = Q->edges[Child].HeadPos;
	  Q->edges[i].TailPos = Q->edges[Child].TailPos;
	}
      else
	{
	  break;
	}
    }
  Q->edges[i].Weight = LastElement.Weight;
  Q->edges[i].HeadPos = LastElement.HeadPos;
  Q->edges[i].TailPos = LastElement.TailPos;
 return MinData;
}

void Initialize(DisjSet S)
{
  for(int i = 0; i < MaxSize; i++)
    {
      S[i] = -1;
    }
}

SetType Find(int X, DisjSet S)
{
  if(S[X] < 0)
    {
      return X;
    }
  else
    {
      return  Find(S[X], S);
    }
}

void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
  S[Root2] = Root1;
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

int main()
{
  Graph G;
  
  CreateGraph(G);
  Kruskal(G);

  return 0;
}
