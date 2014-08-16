//哈希表
//分离链接法

#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;
typedef unsigned int Index;

struct ListNode;
typedef ListNode* Position;
struct HashTbl;
typedef HashTbl* HashTable;

/*
Index Hash(const char* Key, int TableSize)
{
  unsigned int HashVal = 0;
 
  while(*Key != '\0')
    HashVal += *Key++;

  return HashVal%TableSize;
}

Index Hash(const char* Key, int TableSize)
{
  return (Key[0]+Key[1]*27+Key[2]*27*27);
}
*/

Index Hash(const char* Key, int TableSize)
{
  unsigned int HashVal = 0;

  while(*Key != '\0')
    {
      HashVal = (HashVal<<5) + *Key++;
    }

  return HashVal%TableSize;
}

HashTable InitTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(char *Key, HashTable H);
void Insert(char *Key, HashTable H);
char* Retrieve(Position P);
int NextPrime(int TableSize);

struct ListNode
{
  char Element[255];
  int flag;
  Position next;
};

typedef Position List;

struct HashTbl
{
  int TableSize;
  List *TheLists;
};

HashTable InitTable(int TableSize)
{
  HashTable H;
  
  H = new HashTbl;

  H->TableSize = NextPrime(TableSize);

  H->TheLists = (List*)malloc(sizeof(List)*H->TableSize);

  for(int i = 0; i < H->TableSize; i++)
    {
      H->TheLists[i] = new ListNode;

      H->TheLists[i]->next = NULL;
    }

  return H;
}

int NextPrime(int TableSize)
{
  bool flag = false;

  for(int num = TableSize;; num++)
    {
      for(int i = 2; i < num; i++)
	{
	  if(num%i == 0)
	    {
	      flag = true;
	      break;
	    }
	}

      if(flag == false)
	return num;
      flag = false;
    }
}

Position Find(char* Key, HashTable H)
{
  Position P;
  List L;

  L = H->TheLists[Hash(Key, H->TableSize)];
  P = L->next;
  while(P != NULL && strcmp(P->Element,Key))
    {
      P = P->next;
    }
  return P;
}

void Insert(char* Key, HashTable H)
{
  Position Pos, NewCell;
  List L;

  Pos = Find(Key, H);

  if(Pos == NULL)
    {
      NewCell = new ListNode;
      if(NewCell == NULL)
	{
	  cerr << "Out Space!" << endl;
	}
      L = H->TheLists[Hash(Key, H->TableSize)];
      NewCell->next = L->next;
      strcpy(NewCell->Element, Key);
      cout << "Input the flag:";
      cin >> NewCell->flag;
      L->next = NewCell;
    }
}

int main()
{
  HashTable H;
  Position p;
  int TableSize;

  cout << "Input tablesize:";
  cin >> TableSize;
  H = InitTable(TableSize);
  char Key[255];
  cout << "Input the key:";
  cin >> Key;
  while(Key[0] != '#')
    {
      Insert(Key, H);
      cout << "Input the key:";
      cin >> Key;
    }
  
  cout << "Input the search key:";
  cin >> Key;

  while(Key[0] != '#')
    {
      p = Find(Key, H);
      cout << "The flag of the key:" << p->flag << endl;
      cout << "Input the search key:";
      cin >> Key;
    }

  return 0;
}
