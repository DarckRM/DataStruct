#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"


bitree creatBiTree(bitree bt, int i, int *o) {

    
	if (0 == o[i]) 
    {
		bt = NULL;
	} 
    else 
    {
		bt = (bitree)malloc(sizeof(bitnode));
        bt->lchild = NULL;
        bt->rchild = NULL;
		bt->data = o[i];
        i++;
        if (o[i-1] > o[i])
        {
            bt->lchild = creatBiTree(bt->lchild,i,o);
        } else
        {
            bt->rchild = creatBiTree(bt->rchild,i,o);
        }
		
    }
    return bt;

}

int * creatIntGroup()
{
    //打开文件流 声明字符数组做缓冲区 声明指针操作缓冲区
    FILE* fp = fopen("data.dat", "r");
    char strLine[512], *buf;
    char number[12] = {NULL};
    
    fgets(strLine, 512, fp);
    buf = strLine;

    int i = 0;
    int j = 0;
    int o = 0;
    static int nodes[12];

    while (buf[j] != 'E')
    {
        
        while (buf[j]!=' ')
        {
            number[i] = buf[j];
            j++;
            i++;
        }
        nodes[o] = atoi(number);
        o++;
        int k = 0;
        
        while (k < 12)
        {
            number[k] = NULL;
            k++;
        }
        
        
        i = 0;
        j++;

    }
    
    fclose(fp);
    return nodes;
}

//中序遍历
void inorderTraverse(bitree bt)
{
    if (bt != NULL)
    {
        if (bt->lchild != NULL)
            inorderTraverse(bt->lchild);
        printf("%d ",bt->data);
        if (bt->rchild != NULL)
            inorderTraverse(bt->rchild);
        
    }
    
}

int main() {

    //读取磁盘文件得到数字序列
    int *o;
    o = creatIntGroup();
    //创建空数 分配内存空间
    int i = 0;
    bitree bt = (bitree)malloc(sizeof(bitree));
    bt =  creatBiTree(bt, i, o);
    inorderTraverse(bt);
    return 0;
}