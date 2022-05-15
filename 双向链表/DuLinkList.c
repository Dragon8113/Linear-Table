#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;

/* 双向链表比单链表多了一个指向前驱节点的指针，操作类似 */

typedef struct Node 
{
    ElemType data;
    struct Node* prior; //指向前驱节点
    struct Node* next;  //指向后继结点
} Node;
typedef struct Node* DulinkList;

Status ClearList(DulinkList L);

//为了简单，统一起来，使用含有头节点的方法操作
//如果还想简便删除与插入操作，让元素节点 prior 与 next 都有指向节点，可采用双向循环链表

Status InitList(DulinkList *L){ 
    if(*L == NULL){         //若链表不存在，则初始化，若存在，则清空链表
        *L = (DulinkList)malloc(sizeof(Node));
        (*L)->prior = NULL;
        (*L)->next = NULL;
    }else{
        ClearList(*L);
    }
    return OK;
}

Status ListEmpty(DulinkList L){     //判断链表是否为空
    if(L->next == NULL){
        return OK;
    }
    return ERROR;
}

int ListLength(DulinkList L){       //返回链表长度
    int i = 0;
    while (L->next != NULL)
    {
        L = L->next;
        i++;
    }
    return i;
}

Status ListInsert(DulinkList L, int i, ElemType e){     //指定位置插入元素
    if(i < 1 || i > ListLength(L)+1){
        return ERROR;
    }

    DulinkList temp;

    for(int j = 0; j < i-1; j++){       //遍历到需要删除节点之前的节点位置，即 i-1 位置
        L = L->next;
    }
    temp = (DulinkList)malloc(sizeof(Node));
    temp->data = e;

    temp->next = L->next;
    temp->prior = L;
    L->next = temp;

    if( i != ListLength(L)+1){      //判断是否插入的节点作为尾节点，因为非循环双向链表的话，是没有 prior 指向尾节点的
        L->next->prior = temp; 
    }
    return OK;
}
Status ListDelete(DulinkList L, int i, ElemType *e){    //指定位置删除节点
    if(ListEmpty(L) || i<1 || i>ListLength(L)){     //判断删除位置合法性
        return ERROR;
    }

    DulinkList head,temp;
    head = L;
    for(int j = 0; j < i-1; j++){ //遍历到需要删除的节点之前的位置 ，即 i-1 位置
        L = L->next;
    }
    temp = L->next; //temp指向删除节点

    if(i != ListLength(head)){     //同理插入
        L->next->next->prior = L;
    }  
    L->next = L->next->next;
    free(temp);
    return OK;
}   

ElemType GetElem(DulinkList L, int i){  //返回指定位置元素
    if(i < 1 || i > ListLength(L)){     //判断查找位置合法性
        return ERROR;
    }

    for(int j = 0; j < i; j++){
        L = L->next;
    }
    return L->data;
}   

int LocateElem(DulinkList L, ElemType e){       //返回指定元素的位置
    int i = 1;
    L = L->next;
    while (L != NULL)
    {
        if(L->data == e){
            return i;
        }
        L = L->next;
        i++;
    }
    return FALSE;
}   

Status ClearList(DulinkList L){     //清空链表
    DulinkList rear;
    rear = L->next;
    while (rear == NULL)
    {
        L = rear->next;
        free(rear);
        rear = L;
    }
    L->prior = NULL;
    L->next = NULL;
    return OK;
}   

Status DestroyList(DulinkList *L){  //销毁链表
    if(!ListEmpty(*L)){ //若链表不为空，则先清空链表
        ClearList(*L);
    }
    *L = NULL;
    return OK;
}  

int main(void){     //双向链表测试
    DulinkList L = NULL ;
    ElemType e;

    InitList(&L);

    for(int i=1; i <= 20; i++){ //先填充 20 个元素
        ListInsert(L, i,i*5-2);
    }

   // ListInsert(L, 10, 50);     //推荐测试 位置 0、1、20、21
   // ListDelete(L, 20, &e);    //推荐测试 位置 0、1、20、21
    //ClearList(L);

    printf("\n\n链表遍历: ");
   
    DulinkList p = L->next;
    while(p != NULL){
        printf(" %d ", p->data);
        p = p->next;
    }

    printf("\n\n链表长度: %d", ListLength(L));

    printf("\n\n位置10的元素: %d", GetElem(L, 10));

    printf("\n\n元素8的位置: %d", LocateElem(L, 8));

    printf("\n\n");
    return 0;
}