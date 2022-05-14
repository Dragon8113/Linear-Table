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

Status InitList(SqList *L){ //初始化线性表
    L->length = 0;
    return OK;
}

Status ListEmpty(SqList L){ //判断线性表是否为空
    if(L.length == 0)
        return TRUE;
    return FALSE;
}

int ListLength(SqList L){   //返回线性表长度
    return L.length;
}

Status GetElem(SqList L, int i, ElemType *e){   //按位置查找元素，将元素保存在e中
    if(L.length == 0 || i<1 || i>L.length){ //判断线性表是否为空，以及查找位置是否合法性
        return ERROR;
    }
    *e = L.data[i-1];   //将该元素保存在e中
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e){ //按位置插入指定元素
    if(L->length == MAXSIZE || i<1 || i>L->length+1){   //判断线性表是否已满，以及插入位置合法性
        return ERROR;
    }   
    if(i<L->length){
        for(int k=L->length+1;k>i;k--){     //若在线性表之前插入元素，则将第i位置以及之后的元素向后移动一位
            L->data[k-1] = L->data[k-2];    
        }
    }
    L->data[i-1] = e;
    L->length++;    //长度加 1
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e){   //按指定位置删除元素
    if(L->length == 0 || i<1 || i>L->length){   //判断线性表是否为空，以及删除位置的合法性
        return ERROR;
    }
    *e = L->data[i-1];
    if(i<L->length){    
        for(int k = i ;k>L->length;k++){
            L->data[k-1] = L->data[k];  //若在线性表之前删除元素，则将第i以后的元素向前移动一位
        }
    }
    L->length--;    //长度减 1
    return OK;
}

int LocateElem(SqList L, ElemType e){   //查找线性表中是否包含该元素
    for(int i = 1; i <= L.length; i++){
        if(e == L.data[i-1]){
            return i;   //返回元素位置
        }
    }
    return 0;   //查找失败，不包含该元素
}

Status ClearList(SqList *L){    //清空线性表
    L->length = 0;
    return OK;
}

int main(void){  //线性表测试
    SqList L;
    ElemType e;
    InitList(&L);   //初始化线性表

    ListInsert(&L, 1, 1);   //插入元素
    ListInsert(&L, 2, 8);
    ListInsert(&L, 3, 5);
 
    printf("\n        线性表：");
    for(int i=1; i<=L.length;i++){  
        GetElem(L, i, &e);
        printf("%d ", e);
    }

    printf("\n  线性表的长度： %d",ListLength(L));

    printf("\n查找元素的位置： %d ", LocateElem(L, 8)); 

    ClearList(&L);  //清空线性表
    printf("\n\n");
    return 0;
}