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
typedef Node* CLinkList;

Status InitList(CLinkList *rear){  //为了练习，加强无头节点练习，本次循环链表使用无头节点操作，同时使用尾指针rear
   if(*rear != NULL){               //即尾指针（头指针）开始是指向 NULL;
       *rear = NULL;
   }
   return OK;
}

Status ListEmpty(CLinkList rear){   //判断链表是否为空
    if(rear == NULL){  //尾指针（头指针）指向 NULL，则为空
        return TRUE;
    }
    return FALSE;
}

int ListLength(CLinkList rear){     //返回链表长度
    int i = 0;  //默认 rear 指向第 0 个元素
    if(!ListEmpty(rear)){
        CLinkList p = rear->next;   //p 指向第 1 个元素
        i++;
        while(p != rear){
            p = p->next;
            i++;
        }
    }
    return i;
}

Status ListInsert(CLinkList *rear, int i, ElemType e){   //指定位置 i，插入元素 e
    if(i < 1 || i > ListLength(*rear)+1){   //判断插入位置合法性
        return ERROR;
    }

    CLinkList p, temp;
    temp = (CLinkList)malloc(sizeof(Node));
    temp->data = e;
   

    //第一种插入方法：先判断插入节点是否作为尾节点（若插入位置为尾部，则直接使用 rear进行操作 ———— 效率高，代码复杂点，相对第二种方法难理解一点

   /*  if(i == ListLength(*rear)+1){     //判断插入位置是否为尾部
        if(ListLength(*rear) == 0){   //链表为空，插入尾部
            (*rear) = temp;
            (*rear)->next = temp;   //插入节点指向 自己

        }else{                          //链表不为空，插入尾部（不能改变顺序）
            temp->next = (*rear)->next; //插入节点指向 第一个位置
            (*rear)->next = temp;
            (*rear) = temp;
            
        }
    }else{
         p = *rear;  //p 指向第 0 个元素
        for(int j = 0; j < i-1; j++){   //p 指向第 i-1 元素位置
            p = p->next;
        }      
        temp->next = p->next;
        p->next = temp;
    }
 */
    //第二种插入方法：后判断插入节点是否作为尾节点（一定会指到 i-1 位置）———— 效率低，代码简洁点，容易理解

    if(!ListEmpty(*rear)){  //若链表不为空表
        p =(*rear);     //p 指向尾节点
        for(int j=0; j < i-1; j++){     //p 指向 i-1 位置节点
            p = p->next;
        } 
        temp->next = p->next;
        p->next = temp;
    }else{              //若链表为空表
        (*rear) = temp;
        (*rear)->next = temp;
    }
    if(p == (*rear)){     //判断插入位置是否为尾节点后面的位置（即插入节点是否会作为尾节点）
        *rear = temp;
    }

    return OK;
}

Status ListDelete(CLinkList *rear, int i, ElemType *e){ //按指定位置删除节点
    if(i < 1 || i > ListLength(*rear)){
        return ERROR;
    }

    //使用的是第二种方法：后判断是否为尾节点 ———— 效率低点，代码简洁
    CLinkList p = (*rear);    //临时指针,开始指向尾节点
    for(int j = 0; j < i-1; j++){   //p 指向 i-1 位置
        p = p->next;
    }
    *e = p->next->data;
    if(p->next == (*rear)){ //判断 i-1 位置的下一个节点是否为 尾节点（判断指定删除位置为尾节点）
        *rear = p;
    } 
    p->next = p->next->next;
    return OK;
}

ElemType GetElem(CLinkList rear, int i);    //返回查找指定位置元素(类似单链表)

int LocateElem(CLinkList rear, ElemType e);  //返回查找指定元素的位置（类似单链表）

Status ClearList(CLinkList *rear){  //清空链表
    if(!ListEmpty(*rear)){
        *rear = NULL;
    }
    return OK;
}

int main(){         //单循环链表测试
    CLinkList rear;
    ElemType e;

    InitList(&rear);

    printf("\n\n链表遍历: ");
    for(int i=1; i <=20; i++){
        ListInsert(&rear, i, i);
    }

   // ListDelete(&rear, 20, &e);
    //ClearList(&rear);

    CLinkList p = rear; //p 指向第 0 个元素
    while( rear != NULL && p->next != rear){
        p = p->next;
        printf(" %d ", p->data); 
        if(p->next == rear){
            printf(" %d ", rear->data);
        }
    }
   

    printf("\n链表长度: %d", ListLength(rear));

    printf("\n\n");
    return 0;
}