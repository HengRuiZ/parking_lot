#include<stdio.h>
#include<stdlib.h> 
#include"iostream"
#define STACK_INIT_SIZE 100
using namespace std;
typedef struct{
	int board;
	int time;
}ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode*next;
}LNode,*LinkList;
typedef LinkList Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
typedef struct{
	ElemType* elem;
	int stacksize;
	int top;
}SqStack;
void InitStack_sq(SqStack &S,int msize)
{
	S.elem=new ElemType[msize];
	S.stacksize=msize;
	S.top=-1;
}
void Increment(SqStack &L)
{
	int i,inc_size=5;
	ElemType* a;
	a=new ElemType[L.stacksize+inc_size];
	if(!a){printf("分配内存错误！");return;}
	for(i=0;i<L.stacksize;i++)a[i]=L.elem[i];//{a[i][0]=L.elem[i][0];a[i][1]=L.elem[i][1];}
	delete []L.elem;
	L.elem=a;
	L.stacksize+=inc_size;
}
void Push_sq(SqStack &S,ElemType e)
{
	//if(S.top==S.stacksize-1)Increment(S);
	S.elem[++S.top]=e;
}
bool Pop_sq1(SqStack &S,int i,ElemType &e)
{
	if(S.top==-1)return 1;
	e=S.elem[i];
	for(;i<S.top;i++)S.elem[i]=S.elem[i+1];
	S.top--;
	return 0;
}
void InitQueue_L(LinkQueue &Q)
{
	Q.front=Q.rear=new LNode;
	Q.front->next=NULL;
}
void EnQueue_L(LinkQueue &Q,ElemType e)
{
	LinkList p;
	p=new LNode;
	p->data=e;p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
bool DeQueue_L(LinkQueue &Q,ElemType &e)
{
	LinkList p;
	if(Q.front==Q.rear)return 1;
	p=Q.front->next;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p)Q.rear=Q.front;
	delete p;
	return 0;
}
bool DeQueue1_L(LinkQueue &Q,int i,ElemType &e)
{
	LinkList p=Q.front,q;
	if(Q.front==Q.rear)return 1;
	for(;i>0;i--)
		p=p->next;
	if(p==Q.front)Q.rear=Q.front;
	q=p->next;
	p->next=p->next->next;
	e=q->data;
	free(q);
}
void PrintStack_sq(SqStack S)
{
	int i;
	for(i=0;i<=S.top;i++)
		printf("号码：%d	时间%d\n",S.elem[i].board,S.elem[i].time);
}
void PrintQueue_L(LinkQueue Q)
{
	LinkList p=Q.front->next;
	for(;p!=NULL;p=p->next)
		printf("号码：%d	时间：%d\n",p->data.board,p->data.time);
}
int lenth(LinkQueue Q)
{
	int i=0;
	LinkList p=Q.front->next;
	for(;p;i++)
		p=p->next;
	return i;
}
int Find_sq(SqStack S,int board)
{
	int i;
	if(S.top==-1)return -1;
	for(i=0;S.elem[i].board!=board;i++)
		if(i==S.top)return -1;
	return i;
}
int Find_L(LinkQueue Q,int board)
{
	int i;
	LinkList p=Q.front->next;
	if(Q.front==Q.rear)return -1;
	for(i=0;p->data.board!=board;p=p->next)
	{
		if(p==Q.rear)return -1;
		i++;
	}
		return i;
}
void Find(ElemType e,SqStack P,LinkQueue W)
{
	int i;
	printf("进入栈搜索\n");
	i=Find_sq(P,e.board);
	if(i==-1)
	{
		i=Find_L(W,e.board);
		printf("进入链表搜索\n");
		if(i==-1)
		{printf("未找到这辆车！\n");return;}
		printf("%d车在便道%d位\n",e.board,i+1);return;
	}
	printf("%d车在停车场%d位\n",e.board,i+1);
}
main()
{
	SqStack P;
	LinkQueue W;
	InitStack_sq(P,3);
	InitQueue_L(W);
	ElemType e,e1;
	char c,c1;
	int i,p=2;
	while(1)
	{
		cout<<"请输入："<<endl;
		scanf("%c,%d,%d",&c,&e.board,&e.time);
		scanf("%c",&c1);
		switch(c){
		case 'E':return 0;
		case 'A':
			{
				if(!(Find_sq(P,e.board)==-1&&Find_L(W,e.board)==-1))
				{printf("车牌号重复！\n");break;}
				if(lenth(W)==4)
				{printf("便道已满！\n");break;}
				if(P.top==P.stacksize-1)
				{
					printf("进入便道\n");
					EnQueue_L(W,e);
					PrintQueue_L(W);
					Find(e,P,W);
				}
				else
				{
					printf("进入停车场\n");
					Push_sq(P,e);
					PrintStack_sq(P);
					Find(e,P,W);
				}
				break;
			};
		case 'D':
			{
				printf("进入栈搜索\n");
				i=Find_sq(P,e.board);
				if(i==-1)
				{
					i=Find_L(W,e.board);
					printf("进入链表搜索\n");
					if(i==-1)
					{printf("未找到这辆车！\n");break;}
					else
					{
						DeQueue1_L(W,i,e1);
						printf("%d停在便道上%d分钟，收费0元\n",e.board,e.time-e1.time);
						break;
					}
				}
				Pop_sq1(P,i,e1);
				printf("%d停车%d分钟，收费%d元\n",e.board,e.time-e1.time,(e.time-e1.time)*p);
				if(W.front->next)
				{DeQueue_L(W,e);
				Push_sq(P,e);}
				break;
			};
		case 'P':{PrintStack_sq(P);break;}
		case 'W':{PrintQueue_L(W);break;}
		case 'F':{Find(e,P,W);break;}
		default:break;
		}
	}
}
