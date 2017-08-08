#define STACK_INIT_SIZE 100
#define ElemType int[2];
typedef struct{
	ElemType *elem;
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
	ElemType*a;
	a=new ElemType[L.stacksize+inc_size];
	if(!a){printf("∑÷≈‰ƒ⁄¥Ê¥ÌŒÛ£°");return;}
	for(i=0;i<L.stacksize;i++)a[i]=L.elem[i];
	delete []L.elem;
	L.elem=a;
	L.stacksize+=inc_size;
}
void Push_sq(SqStack &S,ElemType e)
{
	if(top==S.stacksize-1)T=Increment(S);
	S.elem[++S.top]=e;
}
bool Pop_sq(SqStack &S,int i,ElemType &e)
{
	if(S.top==-1)return FALSE;
	e=S.elem[i];
	for(;i<top;i++)S.elem[i]=S.elem[i+1];
	top--;
	return TRUE;
}