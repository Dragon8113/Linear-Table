#include<stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20
typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SqList;

Status InitList(SqList *L){ //��ʼ�����Ա�
    L->length = 0;
    return OK;
}

Status ListEmpty(SqList L){ //�ж����Ա��Ƿ�Ϊ��
    if(L.length == 0)
        return TRUE;
    return FALSE;
}

int ListLength(SqList L){   //�������Ա���
    return L.length;
}

Status GetElem(SqList L, int i, ElemType *e){   //��λ�ò���Ԫ�أ���Ԫ�ر�����e��
    if(L.length == 0 || i<1 || i>L.length){ //�ж����Ա��Ƿ�Ϊ�գ��Լ�����λ���Ƿ�Ϸ���
        return ERROR;
    }
    *e = L.data[i-1];   //����Ԫ�ر�����e��
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e){ //��λ�ò���ָ��Ԫ��
    if(L->length == MAXSIZE || i<1 || i>L->length+1){   //�ж����Ա��Ƿ��������Լ�����λ�úϷ���
        return ERROR;
    }   
    if(i<L->length){
        for(int k=L->length+1;k>i;k--){     //�������Ա�֮ǰ����Ԫ�أ��򽫵�iλ���Լ�֮���Ԫ������ƶ�һλ
            L->data[k-1] = L->data[k-2];    
        }
    }
    L->data[i-1] = e;
    L->length++;    //���ȼ� 1
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){   //��ָ��λ��ɾ��Ԫ��
    if(L->length == 0 || i<1 || i>L->length){   //�ж����Ա��Ƿ�Ϊ�գ��Լ�ɾ��λ�õĺϷ���
        return ERROR;
    }
    *e = L->data[i-1];
    if(i<L->length){    
        for(int k = i ;k>L->length;k++){
            L->data[k-1] = L->data[k];  //�������Ա�֮ǰɾ��Ԫ�أ��򽫵�i�Ժ��Ԫ����ǰ�ƶ�һλ
        }
    }
    L->length--;    //���ȼ� 1
    return OK;
}

int LocateElem(SqList L, ElemType e){   //�������Ա����Ƿ������Ԫ��
    for(int i = 1; i <= L.length; i++){
        if(e == L.data[i-1]){
            return i;   //����Ԫ��λ��
        }
    }
    return 0;   //����ʧ�ܣ���������Ԫ��
}

Status ClearList(SqList *L){    //������Ա�
    L->length = 0;
    return OK;
}

int main(void){  //���Ա����
    SqList L;
    ElemType e;
    InitList(&L);   //��ʼ�����Ա�

    ListInsert(&L, 1, 1);   //����Ԫ��
    ListInsert(&L, 2, 8);
    ListInsert(&L, 3, 5);
 
    printf("\n        ���Ա�");
    for(int i=1; i<=L.length;i++){  
        GetElem(L, i, &e);
        printf("%d ", e);
    }

    printf("\n  ���Ա�ĳ��ȣ� %d",ListLength(L));

    printf("\n����Ԫ�ص�λ�ã� %d ", LocateElem(L, 8)); 

    ClearList(&L);  //������Ա�
    printf("\n\n");
    return 0;
}