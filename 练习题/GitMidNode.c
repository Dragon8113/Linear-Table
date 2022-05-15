/* 题目：快速找到未知长度单链表的中间结点。 */


#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node* next;
} Node;
typedef Node* LinkList;

Status InitList(LinkList *L){
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;

    LinkList p, r;
    r = *L;
    for(int i = 0; i < 10; i++){
        p = (LinkList)malloc(sizeof(Node));
        p->data = i;
        r->next = p;
        r = p;
    }
    r->next = NULL;
    return OK;
}

int ListLength(LinkList L){
    int i = 0;
    while(L->next){
        L = L->next;
        i++;
    }
    return i;
}

//普通方法：确认链表长度，遍历到中间节点，返回该节点
/* LinkList GetMidNode(LinkList L){
    LinkList p = L;
    for(int i = 0; i < ListLength(L)/2; i++){
        p = p->next;
    }
    return p;
} */

//快慢指针：设置 慢指针与快指针 ，快指针的移动速度是满指针的两倍，如果快指针到最后一个元素，则慢指针到达中间
LinkList GetMidNode(LinkList L){
    LinkList mid, search;  //mid为慢指针，search 为快指针
    mid = L;
    search = L;
    while(search->next){
        if(search->next->next == NULL){ //判断 search 指向的下一个元素是否为最后一个元素
            search = search->next;  
            break;
        }else{
            search = search->next->next;
        }
        mid = mid->next;
    }
    return mid;
}

int main(void){
    printf("\n\n");
    LinkList L;

    InitList(&L);

    printf("遍历链表:");
    LinkList p = L;
    for(int i=0; i < 10; i++){
        p = p->next;
        printf(" %d ", p->data);
    }

    printf("\n链表长度: %d",ListLength(L));

    printf("\n中间节点: %d",GetMidNode(L)->data);

    printf("\n\n");
    return 0;
}