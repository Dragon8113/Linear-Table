#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node* next;
} Node;
typedef struct Node* LinkList;
 
Status InitList(LinkList *L){   //初始化单链表
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;
    return OK;
}

void CreateListHead(LinkList *L, int n){    //单链表整表创建，头插法
    LinkList p;

    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;

    for(int i = 0; i < n; i++){
        p = (LinkList) malloc(sizeof(Node));
        p->data = i;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}

void CreateListTail(LinkList *L, int n){    //单链表整表创建，尾插法
    LinkList p , r;

    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;
    r = *L;

    for (int i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node));
        p->data = i;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

Status ListEmpty(LinkList L){   //判断单链表是否为空
    if(L->next == NULL){
        return TRUE;
    }
    return FALSE;
}

int ListLength(LinkList L){     //返回单链表长度
    int i = 0;
    if(ListEmpty(L)){   //若单链表为空，则返回 0
        return 0;
    }
    LinkList p;
    while (L->next != NULL) //若当前节点为最后一个节点，则退出循环
    {
        i++;
        L = L->next;
    }
    return i;
}

Status ListInsert(LinkList *L, int i, ElemType e){      //单链表的元素指定位置 i 插入元素e，
    LinkList p, s;
    int j = 0;
    p = *L;   //p指向头节点

    while ( p != NULL && j < i-1)   //将p指向位置 i 前的元素
    {
        p = p->next;  
        j++;
    }
    if(!p || j >= i){
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;

    s->next = p->next;  //将 s 指向位置i；
    p->next = s;    //将 p 下一个元素 指向s；
    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *e){     //单链表的元素指定位置 i 删除元素，保存该元素e
    LinkList p;
    int j = 0;
    p = (*L);

    while (p != NULL && j < i-1)
    {
        p = p->next;
        j++;
    }
    if(!p || j >= i){
        return ERROR;
    }
    *e = p->next->data;
    p->next = p->next->next;    //将 p 的下一个元素 指向 下下一个元素（越过 i 位置元素）
    
}

Status GetElem(LinkList L, int i, ElemType *e){         //指定位置 i ，保存对应元素e
    if(ListEmpty(L) || i<1 || i > ListLength(L)){
        return ERROR;
    }

    int j = 0;
    while (L->next !=NULL && j < i){    //将 L 指向位置 i；
       L = L->next;
       j++;
    }
    *e = L->data;
    return OK;
}

int LocateElem(LinkList L, ElemType e){                 //指定元素 e ，返回元素节点位置
    int i = 1;
    L = L->next; //指向第一个元素
    while (L != NULL)   //判断指向是否为NULL
    {
        if(L->data == e){   //判断指向元素是否等于 e;
            return i;
        }
        L = L->next;
        i++;
    }
    return FALSE;
}

Status ClearList(LinkList *L){      //清空单链表
    LinkList p, r;
    if(ListEmpty(*L)){  //判断单链表是否为空
        return OK;
    }; 
    r = (*L)->next; //指向第一个元素
    while (r != NULL )  //指向元素是否为Null
    {
        p = r->next;
        free(r);    //释放当前指向的空间
        r = p;
    }
    (*L)->next = NULL;  
    return OK;
}

int main(void){     //单链表测试
    LinkList L;     //单链表声明
    ElemType e;     

    // InitList(&L);
    CreateListTail(&L, 10);

    //printf( "\n %d \n",ListInsert(&L, 0, 20) );
    //ListDelete(&L, 5, &e);

    // ClearList(&L);

    printf(" \n 单链表长度: %d ", ListLength(L));

    printf("\n 单列表元素: ");
    for(int i = 1; i<=ListLength(L); i++){
        GetElem(L, i, &e);
        printf("%d ", e);
    }

    printf("\n元素 9 位置: %d", LocateElem(L, 9));

    printf("\n\n");
    return 0;
}