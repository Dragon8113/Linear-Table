#include<stdio.h>

#define ERROR 0
#define OK 1
#define FALSE 0 
#define TRUE 1 
#define MAXSIZE 1000

typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType data;
    int cur;
} Component, StaticLinklist[MAXSIZE];

Status InitList(StaticLinklist space){  //初始化静态链表

    for(int i = 0; i < MAXSIZE-1; i++){
        space[i].cur = i + 1;  //下标为 i 的游标指向 i+1
        space[i+1].data = 0;
    }
    space[MAXSIZE-1].cur = 0;   //最后一个的游标指向 0，表示当前为空表

    return OK;
}

Status ListEmpty(StaticLinklist L){ //判断静态链表是否为空
    if(L[MAXSIZE-1].cur){
        return TRUE;
    }
    return FALSE;
}

int ListLength(StaticLinklist L){   //返回链表长度
    int i = 0;
    
    int cur = MAXSIZE - 1;  //指向数组最后一个元素（类似于动态链表指向第 0 个元素）
    while(L[cur].cur){ //判断当前 cur 的后一个元素是否为 第一个元素
        cur = L[cur].cur;
        i++;
    }

    return i;
}

int Malloc_SLL(StaticLinklist L){   //模拟动态链表申请空间
    int i = L[0].cur;
    if(i){  //判断是否已满
        L[0].cur = L[i].cur;
    }
    return i;   //返回申请的第一个备用链表下标
}

Status ListInsert(StaticLinklist L, int i, ElemType e){     //按指定位置插入元素 e
    if(i < 1 || i > ListLength(L)+1 ){  //判断插入位置合法性
        return ERROR;
    }

    // j 类似于头指针
    int j = MAXSIZE - 1;   //指向插入元素之前元素(默认指向数组最后一个元素)

    int cur = Malloc_SLL(L);   //指向第一个备用链表（类似于动态链表申请一个空间）
    if(cur){  //判断链表是否已满（类似于动态链表申请空间是否成功）
        L[cur].data = e;

        for(int l = 0; l < i-1; l++){   //指向插入元素前一个元素
            j = L[j].cur;
        } 
        
        L[cur].cur = L[j].cur;   //插入元素 cur 指向 原来 i 位置元素
        L[j].cur = cur;   //插入位置前一个元素 指向插入元素
    }

    return OK;
}

Status Free_SLL(StaticLinklist L, int cur){
    L[cur].cur = L[0].cur;  //需要释放的空间cur指向第一个备用链表下标（地址）
    L[0].cur = cur; //数组第一个空间 cur 指向需要释放空间的下标（地址）
    return OK;
}

Status ListDelete(StaticLinklist L, int i, ElemType *e){    //删除指定位置链表元素，并返回删除的元素 e
    if(ListEmpty(L) || i < 1 || i > ListLength(L)){
        return ERROR;
    }
    //j 类似于头指针
    int j = MAXSIZE-1;  //指向数组最后一个元素（类似于动态链表指向头节点)
                        
    for(int l=0; l < i-1; l++){ //j 指向删除元素的前一个元素
        j = L[j].cur;
    }
    int cur = L[j].cur; // cur 指向需要删除的元素
    *e = L[cur].data;   //保存 e
    L[j].cur = L[cur].cur; //删除元素前一个元素的 cur 指向删除元素的后一个元素（p->next = p->next)

    Free_SLL(L, cur);   //类似于动态链表的释放空间

    return OK;
}

Status GetElem(StaticLinklist L, int i, int *e);    //按位置查找元素(与单链表类似)

int LocateElem(StaticLinklist L, int e);    //按元素查找位置（与单链表类似）

Status ClearList(StaticLinklist L){     //清空静态链表
    int cur;
    int r = L[MAXSIZE-1].cur;  //指向静态链表第一个元素
    while(r){
        cur = r;
        r = L[r].cur;
        Free_SLL(L, cur);
    }
    L[MAXSIZE-1].cur = 0;   //将数组最后一个元素的 cur 指向第一个元素
    return OK;
}

int main(void){     //静态链表测试
    printf("\n");
    StaticLinklist L;
    ElemType e;

    InitList(L); //初始化静态链表
    
    for(int i = 1; i <= 20; i++){   //1~20 赋值
        ListInsert(L, i, i);
    }

    //ListInsert(L, 5, 50);
    //ListInsert(L, 21, 100);

    //ListDelete(L, 8, &e);
    //ListDelete(L, 20, &e);

    //ClearList(L);

    int length = ListLength(L);
    printf("\n 静态链表的长度：%d", length);

    int j = L[MAXSIZE-1].cur;
    printf("\n 遍历静态链表的元素：");
    while(j){
        printf(" %d ",L[j].data);
        j = L[j].cur;
    }

    printf("\n\n");
    return 0;
}