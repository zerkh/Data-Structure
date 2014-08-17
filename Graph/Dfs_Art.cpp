//用dfs解决割点问题

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
#define MaxSize 100
typedef int Vertex;
typedef char ElemType;
int Counter;

typedef struct ArcNode
{
  Vertex Pos;
  int Weight;
  struct ArcNode * next;
}*Arc;

struct VerNode
{
  ElemType Data;
  struct ArcNode* FirstArc;
};

typedef struct VerBox
{
  struct VerNode AdjaList[MaxSize];
  bool Visited[MaxSize];
  Vertex Num[MaxSize], Low[MaxSize], Parent[MaxSize];
  int CurrentSize;
}*Graph;

void CreateGraph(Graph &G);
void AssignNum(Graph &G, Vertex V);
void AssignLow(Graph &G, Vertex V);
void FindArt(Graph &G, Vertex V);

void CreateGraph(Graph &G)
{
  G = new struct VerBox;
  G->CurrentSize = 0;

  ifstream In("Elem3.in");
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
      A->Pos = W;
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
      A->Pos = V;
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

void AssignNum(Graph &G, Vertex V)
{
  Vertex W;

  G->Num[V] = Counter++;
  G->Visited[V] = true;

  Arc P;
  P = G->AdjaList[V].FirstArc;

  while(P != NULL)
    {
      W = P->Pos;
      if(!G->Visited[W])
	{
	  G->Parent[W] = V;
	  AssignNum(G, W);
	}

      P = P->next;
    }
}

void AssignLow(Graph &G, Vertex V)
{
  Vertex W;
  
  G->Low[V] = G->Num[V];

  Arc P;
  for(P = G->AdjaList[V].FirstArc; P != NULL; P = P->next)
    {
      W = P->Pos;
      if(G->Num[V] < G->Num[W])
	{
	  AssignLow(G, W);
	  if(G->Low[W] >= G->Num[V] && V != 0)
	    {
	      cout << V << " is an articulation point" << endl;
	    }
	  G->Low[V] = (G->Low[V]<G->Low[W]?G->Low[V]:G->Low[W]);
	}
      else if(G->Parent[V] != W)
	{
	  G->Low[V] = (G->Low[V]<G->Num[W]?G->Low[V]:G->Num[W]);
	}
    }
}

void FindArt(Graph &G, Vertex V)
{
  Vertex W;
  
  G->Visited[V] = true;
  G->Low[V] = G->Num[V] = Counter++;
  
  Arc P;
  for(P = G->AdjaList[V].FirstArc; P != NULL; P = P->next)
    {
      W = P->Pos;
      if(!G->Visited[W])
	{
	  G->Parent[W] = V;
	  FindArt(G, W);
	  if(G->Low[W] >= G->Num[V] && V != 0)
	    cout << V << " is an articulation point" << endl;
	  G->Low[V] = (G->Low[V]<G->Low[W]?G->Low[V]:G->Low[W]);
	}
      else if(G->Parent[V] != W)
	{
	  G->Low[V] = (G->Low[V]<G->Num[W]?G->Low[V]:G->Num[W]);
	}
    }
}

int main()
{
  Graph G;
  Counter = 1;
  
  CreateGraph(G);
  FindArt(G, 0); 
  // AssignNum(G, 0);
  // AssignLow(G, 0);

  return 0;
}
