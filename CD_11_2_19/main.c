#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "head.h"

int dfs(int i,int j)//������ȱ�������
{
    //�ݹ����
    if((a[i][j] < a[i-1][j]) && (a[i][j] < a[i][j-1]) && (a[i][j] < a[i+1][j]) && (a[i][j] < a[i][j+1]))
    {
        return dp[i][j] = 1;
    }
    //�Ѿ�����������ټ���(����¼)
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
                //�ҵ����͵�һ���㲢�ݹ�
                temp = dfs(i + dir[k][0],j + dir[k][1]) + 1;
                count = max(count,temp);
                dp[i][j] = count;
                //���ֵ������ȫ�ֱ���
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
    //��������ÿ���������Ի��е������
    for(i = 1; i < N-1; i++)
    {
        for(j = 1; j < N-1; j++)
        {
            dfs(i,j);
        }
    }
    printf("�·������Ϊ:%d\n",maxRuslt);
    //�ҵ���ߵ��������Ϣ
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
    printf("��ߵ�����Ϊ:%d %d\n", x, y);
    printf("�·��Ϊ:");
    PrtPath(x, y);
    //����ߵ㿪ʼѰ���·���ڵ㲢���
    scanf("�������������");
    return 0;
}
void PrtPath(int i, int j)
{
    //�ݹ���ֹ����
    if((dp[i][j] < dp[i-1][j]) && (dp[i][j] < dp[i][j-1]) && (dp[i][j] < dp[i+1][j]) && (dp[i][j] < dp[i][j+1]))
    {
        return;
    }
    int k;
    int x, y;
    int Max = dp[i][j] - 1;
    for(k = 0; k < 4; k++)
    {
        //�ҵ����͵�һ����������һ���㲢�ݹ�
        if(dp[i + dir[k][0]][j + dir[k][1]] >= Max)
        {
            if(dp[i + dir[k][0]][j + dir[k][1]] >= dp[i][j])
                continue;
            Max = dp[i + dir[k][0]][j + dir[k][1]];
            x = i + dir[k][0];
            y = j + dir[k][1];
        }
    }
    //����һ�������ʽ
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
