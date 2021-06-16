#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#define N 7
#define max(a,b) ((a>b)?a:b)
//定义四个方向，上、左、下、右
int dir[4][2] ={{-1,0},{0,-1},{1,0},{0,1}};
//保存最大长度
int maxRuslt = 0;
//定义矩阵
int a[N][N]={{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},//四周用最大数防止溢出
                 {INT_MAX,1,2,3,4,5,INT_MAX},
                 {INT_MAX,16,17,18,19,6,INT_MAX},
                 {INT_MAX,15,26,25,20,7,INT_MAX},
                 {INT_MAX,14,23,22,21,8,INT_MAX},
                 {INT_MAX,13,12,11,10,9,INT_MAX},
                 {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX}};
//定义dp
int dp[N][N] = {0};//全局矩阵记录每个点能够滑行的最长长度
int dps(int, int);
void PrtPath(int, int);
#endif // HEAD_H_INCLUDED
