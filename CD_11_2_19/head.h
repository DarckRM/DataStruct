#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#define N 7
#define max(a,b) ((a>b)?a:b)
//�����ĸ������ϡ����¡���
int dir[4][2] ={{-1,0},{0,-1},{1,0},{0,1}};
//������󳤶�
int maxRuslt = 0;
//�������
int a[N][N]={{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},//�������������ֹ���
                 {INT_MAX,1,2,3,4,5,INT_MAX},
                 {INT_MAX,16,17,18,19,6,INT_MAX},
                 {INT_MAX,15,26,25,20,7,INT_MAX},
                 {INT_MAX,14,23,22,21,8,INT_MAX},
                 {INT_MAX,13,12,11,10,9,INT_MAX},
                 {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX}};
//����dp
int dp[N][N] = {0};//ȫ�־����¼ÿ�����ܹ����е������
int dps(int, int);
void PrtPath(int, int);
#endif // HEAD_H_INCLUDED
