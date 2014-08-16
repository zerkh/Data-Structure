//哈希表
//开放定址法:平方探测法

#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

typedef unsigned int Index;
typedef Index Position;
typedef char ElemType;

enum Status{Empty, Full, Delete};

typedef struct HashEntry
{
  ElemType Key[255];
  int Data;
  enum Status Info;
}Cell;

typedef struct HashTbl
{
  int TableSize;
  Cell *TheCells;
}*HashTable;

int Hash(ElemType Key, int TableSize);
HashTable InitTable(int TableSize);
Position Find(ElemType Key, HashTable H);
void Insert(ElemType Key, HashTable H);
void Retrieve(ElemType Key, HashTable H);
int NextPrime(int TableSize);

int Hash(ElemType Key[], int TableSize)
{
  int HashVal = 0;
  int i = 0;
  
  while(*Key != '\0')
    {
      HashVal = (HashVal<<5)+*Key++;
      i++;
    }

  return HashVal%TableSize;
}

int NextPrime(int TableSize)
{
  int num;
  bool flag = false;

  for(num = TableSize;; num++)
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
	{
	  return num;
	}
      flag = false;
    }
}

HashTable InitTable(int TableSize)
{
  HashTable H;
  
  H->TableSize = NextPrime(TableSize);
  H->TheCells = (Cell*)malloc(sizeof(Cell)*H->TableSize);
  if(H->TheCells == NULL)
    {
      cerr << "Out of space!" << endl;
    }
  for(int i = 0; i < H->TableSize; i++)
    {
      H->TheCells[i].Info = Empty;
    }

  return H;
}

Position Find(ElemType Key[], HashTable H)
{
  Position CurrentPos;
  int CollsionNum = 0;

  CurrentPos = Hash(Key, H->TableSize);
  while(H->TheCells[CurrentPos].Info != Empty && strcmp(H->TheCells[CurrentPos].Key, Key))
    {
      CurrentPos += 2 * ++CollsionNum -1;
      if(CurrentPos >= H->TableSize)
	{
	  CurrentPos -= H->TableSize;
	}
    }

  return CurrentPos;
}

void Insert(ElemType Key[], HashTable H)
{
  Position Pos;
  
  Pos = Find(Key, H);
  if(H->TheCells[Pos].Info != Full)
    {
      H->TheCells[Pos].Info = Full;
      strcpy(H->TheCells[Pos].Key,Key);
      cout << "Input the data:";
      cin >> H->TheCells[Pos].Data;
    }
}

void Retrieve(ElemType Key[], HashTable H)
{
  Position Pos;
  
  Pos = Find(Key, H);

  if(H->TheCells[Pos].Info == Empty)
    {
      cout << "The cell is empty." << endl;
      return;
    }
  if(H->TheCells[Pos].Info == Delete)
    {
      cout << "The cell is deleted." << endl;
      return;
    }
  if(H->TheCells[Pos].Info == Full)
    {
      cout << "The data of cell is " << H->TheCells[Pos].Data << endl;
      return;
    }
}

int main()
{
  ElemType Key[255];
  HashTable H;
  int TableSize;

  cout << "Input the tablesize:";
  cin >> TableSize;

  H = InitTable(TableSize);

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
      Retrieve(Key, H);
      cout << "Input the search key:";
      cin >> Key;
    }

  return 0;
}
