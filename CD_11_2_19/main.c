#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "head.h"

int dfs(int i,int j)//深度优先遍历搜索
{
    //递归出口
    if((a[i][j] < a[i-1][j]) && (a[i][j] < a[i][j-1]) && (a[i][j] < a[i+1][j]) && (a[i][j] < a[i][j+1]))
    {
        return dp[i][j] = 1;
    }
    //已经算出来则不需再计算(备忘录)
    else if(dp[i][j] > 0)
    {
        return dp[i][j];
    }
    else
    {
        int k;
        int count = 0;
        int temp = 0;
        for(k = 0; k < 4; k++)
        {
            if(a[i][j] > (a[i + dir[k][0]][j + dir[k][1]]))
            {
                //找到更低的一个点并递归
                temp = dfs(i + dir[k][0],j + dir[k][1]) + 1;
                count = max(count,temp);
                dp[i][j] = count;
                //最大值保存在全局变量
                maxRuslt = max(maxRuslt,count);
                //printf("temp = %d;count = %d;maxResult = %d;\n", temp, count, maxRuslt);
            }
        }
        return count;
    }
}

int main()
{
    int i,j;
    //遍历矩阵每个点计算可以滑行的最长距离
    for(i = 1; i < N-1; i++)
    {
        for(j = 1; j < N-1; j++)
        {
            dfs(i,j);
        }
    }
    printf("最长路径长度为:%d\n",maxRuslt);
    //找到最高点的坐标信息
    int Max = dp[1][1];
    int x, y;
    for(i = 1; i < N-1; i++)
    {
        for(j = 1; j < N-1; j++)
        {
            if(dp[i][j] > Max)
            {
                Max = dp[i][j];
                x = i;
                y = j;
            }
        }
    }
    printf("最高点坐标为:%d %d\n", x, y);
    printf("最长路径为:");
    PrtPath(x, y);
    //从最高点开始寻找最长路径节点并输出
    scanf("输入任意键结束");
    return 0;
}
void PrtPath(int i, int j)
{
    //递归中止条件
    if((dp[i][j] < dp[i-1][j]) && (dp[i][j] < dp[i][j-1]) && (dp[i][j] < dp[i+1][j]) && (dp[i][j] < dp[i][j+1]))
    {
        return;
    }
    int k;
    int x, y;
    int Max = dp[i][j] - 1;
    for(k = 0; k < 4; k++)
    {
        //找到更低的一个点中最大的一个点并递归
        if(dp[i + dir[k][0]][j + dir[k][1]] >= Max)
        {
            if(dp[i + dir[k][0]][j + dir[k][1]] >= dp[i][j])
                continue;
            Max = dp[i + dir[k][0]][j + dir[k][1]];
            x = i + dir[k][0];
            y = j + dir[k][1];
        }
    }
    //控制一下输出格式
    if(dp[i][j] == 1)
    {
        printf("%d",a[i][j]);
        return;
    }
    if(dp[i][j] == 0)
        return;
    printf("%d-",a[i][j]);
    PrtPath(x, y);
}
