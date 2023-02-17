#include<stdio.h>
#include"MyMalloc.h"

int main()
{
    int *p=(int*)MyMalloc(100);
    int *q=(int*)MyMalloc(200);
    int *s=(int*)MyMalloc(150);
    MyFree(q);
    int *r=(int*)MyMalloc(10);
}