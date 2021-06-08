#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int main() {

    //创建新的邻接表
    AdjMatrix *G = (AdjMatrix*)malloc(sizeof(AdjMatrix));
    G->e = 0;
    G->n = 0;
    G = createGraph(G);
    //根据起始点下标做深度优先遍历
    int a = DFSTraverse(G, 2);

    return 0;
}

AdjMatrix* createGraph(AdjMatrix* G) {
    
    printf("程序启动读取目录下graph.dat文件 生成邻接表\n");
    VertexNode *vn = G->adjlist;
    //先把G里的所有顶点置为0便于判断
    while (true)
    {        
        vn->vertex = 0;
        vn++;
        if (vn->vertex == NULL)
        {
            break;
        }
    }
    vn = G->adjlist;
    //打开文件流 声明字符数组做缓冲区 声明指针操作缓冲区
    FILE *fp = fopen("graph.dat", "r");
    char strLine[512], *buf;

    while (!feof(fp))
    {
        fgets(strLine, 512, fp);
        buf = strLine;
        int i = 0;
        //nodes代表当前顶点有多少个边点，便于后期遍历边点
        int nodes = 0;
        while (buf[i]!=']')
        {
            //当读取到:时 前一个字符则为顶点 添加进邻接表
            if (buf[i] == ':')
            {
                vn = addVertex(vn, buf[i-1]);
                //顶点数加
                G->e += 1;
                i += 2;
                continue;
            }

            //当读取到-时 前一个字符则为边点
            if (buf[i] == '-')
            {
                //边加1
                G->n += 1;
                //分配内存空间
                EdgeNode *edgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));

                EdgeNode *p;
                p=edgeNode;

                int j = 0;
                int value;
                //缓冲区values用来存放读取到的边点的权值
                char values[10] = {0};
                //j代表读取到第几个字符
                if (j == 0)
                {
                    edgeNode->adjvex = buf[i-1];
                }
                                
                //当读取到,时 跳出读取这个边点的循环
                while (buf[i]!=',')
                {
                    //读取到的-之后的每个字符进入缓冲区
                    values[j] = buf[i+1];
                    //当读取到,的前一个字符时 把values缓冲区的字符转成int类型的value
                    if (buf[i+1] == ',')
                    {
                        value = atoi(values);
                        //printf("读取到的边点%c,它的权值%d\n", edgeNode->adjvex, value);
                        edgeNode->value = value;
                        //头插法插入新节点
                        p->next = vn->edgenext;
                        vn->edgenext = p;
                        nodes += 1;
                        break;
                    }
                     
                    j++;
                    i++;
                }

            }
            //��ǰ�б����� �ڱ�����һ��֮ǰ��β����next��λNULL ����vnָ�����
            if (buf[i]=='*')
            {
                EdgeNode *h = vn->edgenext;
                if(nodes == 0)
                {
                    vn->edgenext = NULL;
                    break;
                }
                while(nodes!=1 && vn->edgenext!=NULL)
                {
                    h = h->next;
                    nodes -= 1;
                }
                h->next = NULL;
                nodes = 0;
                vn += 1;
                break;
            }

            i++;           
            
        };
           
    }
    
    fclose(fp);
    
    VertexNode *p = G->adjlist;
    InOutInfo io[MaxVertices] = {NULL};
    //遍历表 下标赋值 计算出入度
    int tag = 0;
    while (p->vertex != 0)
    {
        p->tag = tag;
        io[tag].vertex = p->vertex;
        p++;
        tag++;
    }
    tag = 0;
    p = G->adjlist;
    VertexNode *v = p;
    
    while (p->vertex != 0)
    {
        int ins = 0;
        int outs = 0;
        EdgeNode *o = p->edgenext;
        while (o)
        {
            v = G->adjlist;
            while (v)
            {
                if (v->vertex == o->adjvex)
                {
                    o->tag = v->tag;
                    io[o->tag].in++;
                    v = p;
                    break;
                }
                v++;
            }
            outs++;
            o=o->next;
        }
        io[tag].out = outs;
        tag++;
        p++;
    }
    tag = 0;
    while (io[tag].vertex != 0)
    {
        printf("顶点%c的入度为:%d,出度为:%d\n",io[tag].vertex,io[tag].in,io[tag].out);
        tag++;
    }
    
    
    return G;
}

VertexNode* addVertex(VertexNode* vn, char vertex) {

    vn->vertex = vertex;
    return vn;

}
//邻接表的深度优先搜索
int DFS(AdjMatrix *G, int i)
{
	EdgeNode *p;
	visited[i] = 1;
	printf("%c->", G->adjlist[i].vertex);
	p = G->adjlist[i].edgenext;//让p指向边表的第一个结点
	while (p)
	{
		if (!visited[p->tag])
		{
			DFS(G, p->tag);
		}
		p = p->next;
	}
    return 0;
}

int DFSTraverse(AdjMatrix *G, int start)
{
	for (int i = 0; i < G->e; i++)
	{
		visited[i] = 0;//初始化标记数组为0
	}
	for (int i = 0; i < G->e; i++)
	{
		if (!visited[start])
		{
			DFS(G, start);
		}
	}
    return 0;
}