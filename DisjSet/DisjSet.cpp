//不相交集 对于按秩合并的代码还有不解

#include <iostream>
#include <cstdlib>
using namespace std;
#define NumSets 60
typedef int DisjSet[NumSets+1];
typedef int ElemType;
typedef int SetType;

void Init(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(ElemType X, DisjSet S);

void Init(DisjSet S)
{
  for(int i = 1; i < NumSets+1; i++)
    {
      S[i] = 0;
    }
}

//按大小初始化
// void Init(DisjSet S)
// {
//   for(int i = 1; i < NumSets+1; i++)
//     {
//       S[i] = -1;
//     }
// }

//基础的setunion
//void SetUnion(DisjSet S, SetType Root1, SetType Root2)
//{
//  S[Root2] = Root1;
//}

//基础的find
// SetType Find(ElemType X, DisjSet S)
// {
//   if(S[X] <= 0)
//     return X;
//   else
//     {
//       return Find(S[X], S);
//     }
// }

//按高度(秩)求并
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
  if(S[Root1] < S[Root2])
    {
      S[Root2] = Root1;
    }
  else
    {
      if(S[Root1] == S[Root2])
	{
	  S[Root1]--;
	}
      S[Root2] = Root1;
    }
}

//路径压缩
SetType Find(ElemType X, DisjSet S)
{
  if(S[X] <= 0)
    {
      return X;
    }
  else
    {
      return S[X] = Find(S[X], S);
    }
}

int main()
{
  DisjSet S;
  
  Init(S);
  SetUnion(S, 5, 6);
  SetUnion(S, 5, 7);
  SetUnion(S, 7, 8);
  cout << Find(4, S) << endl;
  cout << Find(5, S) << endl;
  cout << Find(6, S) << endl;
  cout << Find(8, S) << endl;

  return 0;
}
