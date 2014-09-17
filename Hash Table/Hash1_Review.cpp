#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef char ElemType;

struct HashCell
{
  ElemType Data[50];
  struct HashCell *next;
};

struct HashTbl
{
  struct HashCell **CellList;
  int TableSize;
};

typedef struct HashCell *Position;
typedef struct HashTbl *HashTable;

int Hash(HashTable H, ElemType Key[]);
void Initialize(HashTable &H);
void Insert(HashTable H, ElemType Key[]);
bool Delete(HashTable H, ElemType Key[]);
Position Find(HashTable H, ElemType Key[]);
int NextPrime(int TableSize);

int Hash(HashTable H, ElemType Key[])
{
  int HashVal = 0;

  while(*Key != '\0')
    {
      HashVal += *Key++;
    }

  return HashVal % H->TableSize;
}

void Initialize(HashTable &H)
{
  int TempSize;
  
  cout << "Input the TableSize:";
  cin >> TempSize;
  
  H = new HashTbl;
  if(H == NULL)
    {
      cout << "No Space!" << endl;
      return;
    }
  H->TableSize = NextPrime(TempSize);
  H->CellList = new struct HashCell*[H->TableSize];

  for(int i = 0; i < H->TableSize; i++)
    {
      H->CellList[i] = new struct HashCell;
      H->CellList[i]->next = NULL;
      strcpy(H->CellList[i]->Data, "#");
    }
}

void Insert(HashTable H, ElemType Key[])
{
  Position NewCell;
  if(Find(H,Key) == NULL)
    {
      NewCell = new struct HashCell;
      NewCell->next = H->CellList[Hash(H, Key)]->next;
      H->CellList[Hash(H,Key)]->next = NewCell;
      strcpy(NewCell->Data, Key);
    }
}

bool Delete(HashTable H, ElemType Key[])
{
  if(Find(H, Key) == NULL)
    {
      cout << "No Symbol!" << endl;
      return false;
    }
  else
    {
      int Index = Hash(H, Key);
      Position P1, P2 = H->CellList[Index];
      P1 = P2->next;

      while(P1 != NULL)
	{
	  if(strcmp(P1->Data, Key) == 0)
	    {
	      P2->next = P1->next;
	      delete P1;
	      P1 = NULL;
	    }
	  else
	    {
	      P1 = P1->next;
	      P2 = P2->next;
	    }
	}
    }
  
  return true;
}

Position Find(HashTable H, ElemType Key[])
{
  int Index = Hash(H, Key);
  Position P = H->CellList[Index]->next;

  while(P != NULL)
    {
      if(strcmp(P->Data, Key) == 0)
	return P;
      P = P->next;
    }

  return NULL;
}

int NextPrime(int TableSize)
{
  int Prime = TableSize;
  bool flag = true;

  while(1)
    {
      for(int i = 2; i < Prime; i++)
	{
	  if(Prime % i == 0)
	    {
	      flag = false;
	      break;
	    }
	}
      
      if(flag == true)
	return Prime;
      else
	{
	  Prime++;
	  flag = true;
	}
    }
}

int main()
{
  HashTable H;

  Initialize(H);
  
  for(int i = 0; i < 6; i++)
    {
      char Key[20];
      Key[0] = 'a'+i;
      Key[1] = '\0';
      Insert(H, Key);
    }
  
  char Key[20];
  
  strcpy(Key, "c");
  cout << Delete(H, Key) << endl;
  strcpy(Key, "b");
  cout << Find(H, Key)->Data << endl;
  strcpy(Key, "c");
  cout << Find(H, Key)->Data << endl;

  return 0;
}
