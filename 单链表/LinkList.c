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
 
Status InitList(LinkList *L){   //��ʼ��������
    *L = (LinkList) malloc(sizeof(Node));
    (*L)->next = NULL;
    return OK;
}

void CreateListHead(LinkList *L, int n){    //��������������ͷ�巨
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

void CreateListTail(LinkList *L, int n){    //��������������β�巨
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

Status ListEmpty(LinkList L){   //�жϵ������Ƿ�Ϊ��
    if(L->next == NULL){
        return TRUE;
    }
    return FALSE;
}

int ListLength(LinkList L){     //���ص�������
    int i = 0;
    if(ListEmpty(L)){   //��������Ϊ�գ��򷵻� 0
        return 0;
    }
    LinkList p;
    while (L->next != NULL) //����ǰ�ڵ�Ϊ���һ���ڵ㣬���˳�ѭ��
    {
        i++;
        L = L->next;
    }
    return i;
}

Status ListInsert(LinkList *L, int i, ElemType e){      //�������Ԫ��ָ��λ�� i ����Ԫ��e��
    LinkList p, s;
    int j = 0;
    p = *L;   //pָ��ͷ�ڵ�

    while ( p != NULL && j < i-1)   //��pָ��λ�� i ǰ��Ԫ��
    {
        p = p->next;  
        j++;
    }
    if(!p || j >= i){
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;

    s->next = p->next;  //�� s ָ��λ��i��
    p->next = s;    //�� p ��һ��Ԫ�� ָ��s��
    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *e){     //�������Ԫ��ָ��λ�� i ɾ��Ԫ�أ������Ԫ��e
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
    p->next = p->next->next;    //�� p ����һ��Ԫ�� ָ�� ����һ��Ԫ�أ�Խ�� i λ��Ԫ�أ�
    
}

Status GetElem(LinkList L, int i, ElemType *e){         //ָ��λ�� i �������ӦԪ��e
    if(ListEmpty(L) || i<1 || i > ListLength(L)){
        return ERROR;
    }

    int j = 0;
    while (L->next !=NULL && j < i){    //�� L ָ��λ�� i��
       L = L->next;
       j++;
    }
    *e = L->data;
    return OK;
}

int LocateElem(LinkList L, ElemType e){                 //ָ��Ԫ�� e ������Ԫ�ؽڵ�λ��
    int i = 0;
    L = L->next; //ָ���һ��Ԫ��
    while (L != NULL)   //�ж�ָ���Ƿ�ΪNULL
    {
        i++;
        if(L->data == e){   //�ж�ָ��Ԫ���Ƿ���� e;
            return i;
        }
        L = L->next;
    }
    return FALSE;
}

Status ClearList(LinkList *L){      //��յ�����
    LinkList p, r;
    if(ListEmpty(*L)){  //�жϵ������Ƿ�Ϊ��
        return OK;
    }; 
    r = (*L)->next; //ָ���һ��Ԫ��
    while (r != NULL )  //ָ��Ԫ���Ƿ�ΪNull
    {
        p = r->next;
        free(r);    //�ͷŵ�ǰָ��Ŀռ�
        r = p;
    }
    (*L)->next = NULL;  
    return OK;
}

int main(void){     //���������
    LinkList L;     //����������
    ElemType e;     

    // InitList(&L);
    CreateListTail(&L, 10);

    //printf( "\n %d \n",ListInsert(&L, 0, 20) );
    //ListDelete(&L, 5, &e);

    // ClearList(&L);

    printf(" \n ��������: %d ", ListLength(L));

    printf("\n ���б�Ԫ��: ");
    for(int i = 1; i<=ListLength(L); i++){
        GetElem(L, i, &e);
        printf("%d ", e);
    }

    printf("\nԪ�� 9 λ��: %d", LocateElem(L, 9));

    printf("\n\n");
    return 0;
}