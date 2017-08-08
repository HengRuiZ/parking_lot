#include<LinkList.h>
typedef LinkList Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
void InitQueue_L(LinkQueue &Q)
{
	Q.front=Q.rear=new LNode;
	Q.front->next=NULL;
}
void EnQueue_L(LinkQueue &Q,ElemType e)
{
	p=new LNode;
	p->data
}
bool DeQueue_L(LinkQueue &Q,ElemType &e)
{
	if(Q.front=Q.rear)return FALSE;
	p=Q.front->next;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p)Q.rear=Q.front;
	delete p;
	return TRUE;
}