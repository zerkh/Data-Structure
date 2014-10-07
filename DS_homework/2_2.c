#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

typedef struct Node
{
  ElemType Data;
  struct Node *next;
}Node, *LinkList;

LinkList CreateList(LinkList L);
LinkList Insert(LinkList head, ElemType Elem);
LinkList Delete(LinkList head, ElemType Elem);
void Display(LinkList head);

LinkList CreateList(LinkList L)
{ 
  L = NULL;

  return L;
}

LinkList Insert(LinkList head, ElemType Elem)
{
  Node *p;
  Node *p1;
  
  p = (Node*)malloc(sizeof(Node));
  
  if(p == NULL)
    {
      printf("Out of space!\n");
      exit(-1);
    }

  p->next = NULL;
  p->Data = Elem;

  if(head == NULL)
    {
      head = p; 
    }
  else
    {
      p1 = head;
      
      while(p1->next != NULL)
	{
	  p1 = p1->next;
	}
      p1->next = p;
    }

  return head;
}

LinkList Delete(LinkList head, ElemType Elem)
{
  Node *p1, *p2;
  
  p1 = p2 = head;
  
  if(head == NULL)
    {
      printf("Empty!\n");
    }
  else
    {
      while(head->Data == Elem && head != NULL)
	{
	  p2 = head;
	  head = head->next;
	  free(p2);
	}

      if(head == NULL)
	return head;

      p2 = p1->next;
      while(p2 != NULL)
	{
	  if(p2->Data == Elem)
	    {
	      p1->next = p2->next;
	      free(p2);
	      p2 = p1->next;
	    }
	  p1 = p1->next;
	  p2 = p2->next;
	}
    }

  return head;
}

void Destroy(LinkList head)
{
  Node *p, *p1;

  if(head == NULL)
    return;

  p = head;
  p1 = head->next;
  while(p1 != NULL)
    {
      free(p);
      p = p1;
      p1 = p1->next;
    }
  free(p);
}

void Display(LinkList head)
{
  Node *p;

  p = head;
  while(p != NULL)
    {
      printf("%d ", p->Data);
      p = p->next;
    }

  printf("\n");
}

int main()
{
  LinkList L;
  int i = 0;
  
  L = CreateList(L);

  for(i = 0; i < 20; i++)
    {
      L = Insert(L, i);
    }
  printf("原链表:\n");
  Display(L);

  printf("删除3:\n");
  L = Delete(L, 3);
  Display(L);

  printf("删除8:\n");
  L = Delete(L, 8);
  Display(L);

  printf("删除16:\n");
  L = Delete(L, 16);
  Display(L);

  Destroy(L);

  return 0;
}
