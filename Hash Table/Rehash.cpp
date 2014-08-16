#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

typedef unsigned Index;
typedef Index Position;
enum Info{Full, Empty, Delete};

struct TableCell
{
  char Key[255];
  int Data;
  enum Info Info;
};
typedef TableCell Cell;

typedef struct HashTbl
{
  int TableSize;
  Cell *TheCells;
}*HashTable;

int Hash(char *Key, HashTable H);
HashTable InitTable(int TableSize);
HashTable ReHash(HashTable H);
void Insert(char *Key, HashTable H);
Position Find(char *Key, HashTable H);
int NextPrime(int TableSize);
void Retrieve(char Key[], HashTable H);

int Hash(char *Key, HashTable H)
{
  int HashVal = 0;
  
  while(*Key != '\0')
    {
      HashVal = (HashVal>>5) + *Key++;
    }

  return HashVal%H->TableSize;
}

int NextPrime(int TableSize)
{
  int num;
  bool flag = false;

  for(num = TableSize;; num++)
    {
      for(int i = 2; i < num; i++)
	{
	  if(num % i == 0)
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
      cerr << "Out of space." << endl;
    }
  
  for(int i = 0; i < H->TableSize; i++)
    {
      H->TheCells[i].Info = Empty;
    }

  return H;
}



void Insert(char *Key, HashTable H)
{
  Position Pos;

  Pos = Find(Key, H);
  
  if(H->TheCells[Pos].Info != Full)
    {
      H->TheCells[Pos].Info = Full;
      strcpy(H->TheCells[Pos].Key, Key);
      cout << "Input the data:";
      cin >> H->TheCells[Pos].Data;
    }
}

Position Find(char *Key, HashTable H)
{
  int CurrentPos, Temp;

  Temp = 0;
  CurrentPos = Hash(Key, H);
  
  while(H->TheCells[CurrentPos].Info != Empty && strcmp(H->TheCells[CurrentPos].Key, Key))
    {
      CurrentPos += 2*(++Temp) -1;

      if(CurrentPos >= H->TableSize)
	{
	  CurrentPos -= H->TableSize;
	}
    }

  return CurrentPos;
}

void Retrieve(char Key[], HashTable H)
{
  Position Pos;
  Pos = Find(Key, H);

  if(H->TheCells[Pos].Info == Empty)
    {
      cout << "No the key." << endl;
    }
  else if(H->TheCells[Pos].Info == Delete)
    {
      cout << "The key is deleted." << endl;
    }
  else
    {
      cout << "The data is " << H->TheCells[Pos].Data << "." << endl;
    }
}

HashTable ReHash(HashTable H)
{
  int OldSize;
  Cell *OldCells;
  
  OldCells = H->TheCells;
  OldSize = H->TableSize;

  H = InitTable(2*OldSize);

  for(int i = 0; i < OldSize; i++)
    {
      if(OldCells[i].Info == Full)
	{
	  int Pos, Temp;
	  
	  Pos = Hash(OldCells[i].Key, H);
	  Temp = 0;
	  
	  while(H->TheCells[Pos].Info != Empty && strcmp(H->TheCells[Pos].Key, OldCells[i].Key))
	    {
	      Pos += 2*(++Temp) -1;

	      if(Pos >= H->TableSize)
		{
		  Pos -= H->TableSize;
		}
	    }
	  
	  if(H->TheCells[Pos].Info != Full)
	    {
	      H->TheCells[Pos].Info = Full;
	      strcpy(H->TheCells[Pos].Key, OldCells[i].Key);
	      H->TheCells[Pos].Data = OldCells[i].Data;
	    }
	}
    }

  free(OldCells);

  return H;
}

int main()
{
  HashTable H;
  int TableSize;
  char Key[255];

  cout << "Input the tablesize:";
  cin >> TableSize;

  H = InitTable(TableSize);
  
  cout << "Input the key:";
  cin >> Key;
  while(*Key != '#')
    {
      Insert(Key, H);
      cout << "Input the key:";
      cin >> Key;
    }

  cout << "Input the search key:";
  cin >> Key;
  while(*Key != '#')
    {
      Retrieve(Key, H);
      cout << "Input the key:";
      cin >> Key;
    }

  cout << "Rehash the table." << endl;
  H = ReHash(H);
  cout << "Input the search key:";
  cin >> Key;
  while(*Key != '#')
    {
      Retrieve(Key, H);
      cout << "Input the key:";
      cin >> Key;
    }

  return 0;
}
