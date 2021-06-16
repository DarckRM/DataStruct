#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
void inorderTraverse(bitree bt, int *num, int *deep, int *nodes)
{
    if (bt != NULL)
    {
        *nodes += 1;
        *num += *deep;
        if (bt->lchild != NULL)
        {
            *deep += 1;
            inorderTraverse(bt->lchild, num, deep, nodes);
        }
            
        printf("%d ",bt->data);
        if (bt->rchild != NULL)
        {
            *deep += 1;
            inorderTraverse(bt->rchild, num, deep, nodes);
            
        }
        *deep -= 1;
        
    } else
    {
        printf("树为空树\n");
    }
    
}
//顺序存储中序遍历
void inorderTraverseGroup(int *pobt, int *position)
{
    if (pobt[*position]==0)
    {
        return;
    }
    if (pobt[*position * 2] != 0)
    {
        *position = *position * 2;
        *pobt = pobt[*position];
        inorderTraverseGroup(pobt, position);
    }
    printf("[%d]  ",pobt[*position]);
    if (pobt[*position * 2 + 1]!=0)
    {
        *position = *position * 2 + 1;
        *pobt = pobt[*position];
        inorderTraverseGroup(pobt, position);
    }
    *position = *position / 2;
    
}

//查找节点 参数oprate代表是插入节点还是删除节点
bitree findNode(bitree bt, int value, int operation, int* deep, int* num, int* obt, int *position) {

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
            printf("找到了哦,在第%d层\n",*deep);
            bt = NULL;
            return bt;
        }
        //递归查找
        if (value < bt->data)
        {
            deep++;
            bt->lchild = findNode(bt->lchild,value,1,deep,num,obt,position);
        } else
        {
            deep++;
            bt->rchild = findNode(bt->rchild,value,1,deep,num,obt,position);
        }
    } else if (operation == 0)
    {
        //没找到 插入节点
        if(bt == NULL)
        {
            //链式存储添加
            bitree btn = (bitree)malloc(sizeof(bitree));
            btn->data = value;
            btn->lchild = NULL;
            btn->rchild = NULL;
            //顺序存储添加
            obt[*position] = value;

            return btn;
        }
        else 
        //递归查找
        if (value < bt->data)
        {
            *deep+=1;
            *position *= 2;
            bt->lchild = findNode(bt->lchild,value,0,deep,num,obt,position);
        } else
        {
            deep++;
            *position = *position * 2 + 1;
            bt->rchild = findNode(bt->rchild,value,0,deep,num,obt,position);
        }
    }
}

int main() {

    //读取磁盘文件得到数字序列
    int *o;
    o = creatIntGroup();
    //创建空树 分配内存空间
    int i = 0;
    bitree bt = (bitree)malloc(sizeof(bitree));
    //创建空数组 实现顺序存储二叉树
    int obt[100] = {0};
    int *pobt = obt;
    //节点位置
    int position = 1;
    int *t = &position;
    //插入根节点
    bt->data = o[i];
    bt->lchild = NULL;
    bt->rchild = NULL;
    pobt[1] = bt->data;
    i++;
    //深度信息
    int deep = 1;
    int* q = &deep;
    //总数信息
    int num = 0;
    int* p = &num;
    //节点信息
    int nodes = 0;
    int* u = &nodes;
    int avergeFinds;
    //插入节点
    int max = 0;
    for (; o[i] != 0; i++)
    {
        findNode(bt,o[i],0,q, p, pobt, t);
        
        if (max < deep)
        {
            max = deep;
        }
        deep = 1;
        position = 1;
    }
    num = pow(2, max) - 1;
    //输出顺序存储二叉树
    for (int x = 1; x <= num; x++)
    {
        printf("%d:[%d] ", x, obt[x]);
    }
    printf("\n");
    //中序遍历
    printf("链式存储中序遍历\n");
    inorderTraverse(bt, p, q, u);
    printf("\n");
    printf("顺序存储中序遍历\n");
    inorderTraverseGroup(obt, t);
    //查找成功下的平均长度
    avergeFinds = num/nodes;
    printf("查找成功下的平均长度%d\n",avergeFinds);
    deep = 1;
    num = 0;
    nodes = 0;
    //查找删除操作
    int value;
    printf("请输入你要查找的值:");
    scanf("%d",&value);
    bt = findNode(bt,value,1, q, p, pobt, t);
    //中序遍历
    inorderTraverse(bt, p, q, u);
    //查找成功下的平均长度
    if (nodes == 0)
    {
        return 0;
    }
    
    avergeFinds = num/nodes;
    printf("查找成功下的平均长度%d\n",avergeFinds);
    return 0;
}