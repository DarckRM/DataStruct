#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

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
        
    } else
    {
        printf("树为空树\n");
    }
    
}

//查找节点 参数oprate代表是插入节点还是删除节点
bitree findNode(bitree bt, int value, int operation, int deep, int* num) {

    //查找并删除
    if(operation == 1)
    {
        //没找到 输出信息
        if(bt == NULL)
        {
            printf("没有找到%d哦\n",value);
            return bt;
        }
        //找到节点输出并删除
        else if (bt->data == value)
        {
            printf("找到了哦,在第%d层\n",deep);
            bt = NULL;
            return bt;
        }
        //递归查找
        if (value < bt->data)
        {
            deep++;
            bt->lchild = findNode(bt->lchild,value,1,deep,num);
        } else
        {
            deep++;
            bt->rchild = findNode(bt->rchild,value,1,deep,num);
        }
    } else if (operation == 0)
    {
        //没找到 插入节点
        if(bt == NULL)
        {
            bitree btn = (bitree)malloc(sizeof(bitree));
            btn->data = value;
            btn->lchild = NULL;
            btn->rchild = NULL;
            return btn;
        }
        //找到节点输出
        else 
        //递归查找
        if (value < bt->data)
        {
            deep++;
            bt->lchild = findNode(bt->lchild,value,0,deep,num);
        } else
        {
            deep++;
            bt->rchild = findNode(bt->rchild,value,0,deep,num);
        }
    }
    //查找平均长度 
    else if (operation == 2)
    {
        *num += *num;
        //递归查找
        if (value < bt->data)
        {
            *num = deep * bt->data;
            deep++;
            bt->lchild = findNode(bt->lchild,value,2,deep,num);
        } else
        {
            *num = deep * bt->data;
            deep++;
            bt->rchild = findNode(bt->rchild,value,2,deep,num);
        }
    }
}

//计算查找成功的平均查找次数
void avgFinds(bitree bt, int num) {

    //深度信息
    int deep = 1;
    //当层节点数
    int nodes = 0;

    
    return;

}

int main() {

    //读取磁盘文件得到数字序列
    int *o;
    o = creatIntGroup();
    //创建空数 分配内存空间
    int i = 0;
    bitree bt = (bitree)malloc(sizeof(bitree));
    //插入根节点
    bt->data = o[i];
    bt->lchild = NULL;
    bt->rchild = NULL;
    i++;
    //深度信息
    int deep = 1;
    //总数信息
    int num = 0;
    int* p = 0;
    //插入节点
    for (; o[i] != 0; i++)
    {
        findNode(bt,o[i],0,2,p);
    }
    //查找删除操作
    int value;
    printf("请输入你要查找的值:");
    scanf("%d",&value);
    bt = findNode(bt,value,1,deep,p);
    //中序遍历
    inorderTraverse(bt);
    //查找平均长度
    int num = 0;
    return 0;
}