#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

#define MaxSize 100
typedef int Vertex;
typedef char ElemType;

typedef struct ArcNode
{
  Vertex Pos;
  struct ArcNode *next;
}*Arc;

struct VerNode
{
  struct ArcNode *FirstArc;
  ElemType Data;
};

typedef struct VerBox
{
  struct VerNode AdjaList[MaxSize];
  int VerNum;
}*Graph;

void CreateGraph(Graph G);
void TopSort(Graph G);
Vertex FindNewVertexOfIndegreeZero(int Ingree[], Graph G);
void InitIngree(Graph G, int Ingree[]);

void CreateGraph(Graph G)
{
  Arc A = NULL,  C = NULL;
  Vertex V, W;
  G->VerNum = 0;
  ElemType Elem;
  ifstream In("Elem1.in");
  streambuf* oldbuf = cin.rdbuf(In.rdbuf());
  
  for(int i = 0; i < MaxSize; i++)
    {
      cout << "输入第" << i+1 << "个节点:";
      if(cin >> Elem && Elem != '#')
	{
	  G->AdjaList[i].Data = Elem;
	  G->AdjaList[i].FirstArc = NULL;
	  G->VerNum++;
	}
      else
	{
	  while(i < MaxSize)
	    {
	      G->AdjaList[i].Data = '#';
	      G->AdjaList[i].FirstArc = NULL;
	      i++;
	    }
	  break;
	}
    }

  cout << "Input the headpos and tailpos:";
  while(cin >> V >> W)
    {
      if(V != -1 && W != -1)
	{
	  A = new struct ArcNode;
	  A->next = NULL;
	  A->Pos = W;
	  if((C = G->AdjaList[V].FirstArc) == NULL)
	    {
	      G->AdjaList[V].FirstArc = A;
	    }
	  else
	    {
	      while(C->next != NULL)
		{
		  C = C->next;
		}
	      C->next = A;
	    }
	  cout << "Input the headpos and tailpos:";
	}
      else
	{
	  break;
	}
    }
  cin.rdbuf(oldbuf);
}

void TopSort(Graph G)
{
  int Ingree[G->VerNum];
  InitIngree(G, Ingree);
  
  Vertex V, W;

  for(int i = 0; i < G->VerNum; i++)
    {
      V = FindNewVertexOfIndegreeZero(Ingree, G);

      if(V == -1)
	{
	  cerr << "This is a cycle!" << endl;
	  break;
	}
      else
	{
	  cout << V << ' ' << G->AdjaList[V].Data << endl;
	  
	  Arc A = G->AdjaList[V].FirstArc;

	  while(A != NULL)
	    {
	      Ingree[A->Pos]--;
	      A = A->next;
	    }
	}
    }
}

Vertex FindNewVertexOfIndegreeZero(int Ingree[], Graph G)
{
  int Size;
  Size = G->VerNum;
  for(int i = 0; i < Size; i++)
    {
      if(Ingree[i] == 0)
	{
	  Ingree[i]--;
	  return i;
	}
    }

  return -1;
}

void InitIngree(Graph G, int Ingree[])
{
  for(int i = 0; i < G->VerNum; i++)
    {
      Ingree[i] = 0;
    }

  for(int i = 0; i < G->VerNum; i++)
    {
      Arc A;
      A = G->AdjaList[i].FirstArc;
      
      while(A != NULL)
	{
	  Ingree[A->Pos]++;
	  A = A->next;
	}
    }
}

int main()
{
  Graph G = new struct VerBox;
  
  CreateGraph(G);
  TopSort(G);

  return 0;
}
