#include <iostream>
#include <cstring>
using namespace std;

typedef char ElemType; 
enum State{Empty, Full};

struct HashCell
{
  enum State Info;
  ElemType Key[100];
  int Data;
};

struct HashTbl
{
  struct HashCell *CellList;
  int TableSize;
};

typedef struct HashTbl* HashTable;
typedef struct HashCell* Cell;

void Initialize(HashTable &H);
int NextPrime(int TableSize);
void Insert(HashTable &H, ElemType Key[]);
bool Delete(HashTable &H, ElemType Key[]);
int Find(HashTable &H, ElemType Key[]);
int Hash(HashTable &H, ElemType Key[]);

void Initialize(HashTable &H)
{
  H = new struct HashTbl;

  if(H == NULL)
    {
      cout << "No Space!" << endl;
      return;
    }
  
  cout << "Input the tablesize:";
  cin >> H->TableSize;
  H->TableSize = NextPrime(H->TableSize);

  H->CellList = new struct HashCell[H->TableSize];
  
  for(int i = 0; i < H->TableSize; i++)
    {
      H->CellList[i].Info = Empty;
      strcpy(H->CellList[i].Key, "#");
    }
}

int NextPrime(int TableSize)
{
  int Prime;
  bool flag = true;
  
  Prime = TableSize;

  while(1)
    {
      for(int i = 2; i < Prime; i++)
	{
	  if(Prime%i == 0)
	    {
	      flag = false;
	      break;
	    }
	}
      
      if(flag)
	{
	  return Prime;
	}
      else
	{
	  Prime++;
	  flag = true;
	}
    }
}

void Insert(HashTable &H, ElemType Key[])
{
  int Pos;
  
  Pos = Find(H, Key);
  if(H->CellList[Pos].Info != Full)
    {
      H->CellList[Pos].Info = Full;
      strcpy(H->CellList[Pos].Key, Key);
      cout << "Input the Data:";
      cin >> H->CellList[Pos].Data;
    }
}

bool Delete(HashTable &H, ElemType Key[])
{
  int Pos;
  
  Pos = Find(H, Key);
  
  if(Pos == -1)
    {
      return false;
    }
  else
    {
      H->CellList[Pos].Info = Empty;
      strcpy(H->CellList[Pos].Key,"#");
      return true;
    }
}

int Find(HashTable &H, ElemType Key[])
{
  int deata = 0;
  int CurrentPos = Hash(H, Key);

  while(H->CellList[CurrentPos].Info != Empty && strcmp(Key, H->CellList[CurrentPos].Key))
    {
      CurrentPos += 2*deata-1;
      if(CurrentPos >= H->TableSize)
	{
	  CurrentPos = CurrentPos - H->TableSize;
	}
    }

  return CurrentPos;
}

int Hash(HashTable &H, ElemType Key[])
{
  int HashVal = 0;
  
  while(*Key != '\0')
    {
      HashVal += *Key++;
    }

  return HashVal % H->TableSize;
}

int main()
{
  ElemType Key[100];
  HashTable H;

  Initialize(H);

  cout << "Input the key:";
  cin >> Key;
  while(strcmp(Key, "#"))
    {
      Insert(H, Key);
      cout << "Input the key:";
      cin >> Key;
    }

  cout << "Input the key to find:";
  cin >> Key;
  while(strcmp(Key, "#"))
    {
      int Pos = Find(H, Key);
      if(H->CellList[Pos].Info == Empty)
	{
	  cout << "No this key!" << endl;
	}
      else
	{
	  cout << "Key: " << H->CellList[Pos].Key << "\nData: " << H->CellList[Pos].Data << endl;
	}
      cout << "Input the key:";
      cin >> Key;
    }

  cout << "Input the key to delete:";
  cin >> Key;
  while(strcmp(Key, "#"))
    {
      cout << Delete(H, Key) << endl;
      cout << "Input the key:";
      cin >> Key;
    }

  cout << "Input the key to find:";
  cin >> Key;
  while(strcmp(Key, "#"))
    {
      int Pos = Find(H, Key);
      if(H->CellList[Pos].Info == Empty)
	{
	  cout << "No this key!" << endl;
	}
      else
	{
	  cout << "Key: " << H->CellList[Pos].Key << "\nData: " << H->CellList[Pos].Data << endl;
	}
      cout << "Input the key:";
      cin >> Key;
    }

  return 0;
}
