#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

int main() {

    //�����µ��ڽӱ�
    AdjMatrix *G = (AdjMatrix*)malloc(sizeof(AdjMatrix));
    G->e = 0;
    G->n = 0;
    G = createGraph(G);
    printf("\n");
    printf("������ʼ���±���������ȱ���\n");
    int a = DFSTraverse(G, 4, true);
    printf("\n");
    printf("������ʼ���±���������ȱ���\n");
    BFSTraverse(G, 0);
    printf("\n");
    char x;
    printf("������ڵ�����:");
    scanf("%c",&x);
    FindVertex(G, x);
    printf("\n");
    ifAcross(G);
    scanf("");
    return 0;
}

//����DFS�ж�ͼ�Ƿ���ͨ
void ifAcross(AdjMatrix* G) {
    int end = 1;
    for(int i = 0; i < G->e; i++)
    {
        printf("\n");
        end = DFSTraverse(G, i, false);
        if (end)
        {
            return;
        }
        
    }
}

AdjMatrix* createGraph(AdjMatrix* G) {
    
    printf("����������ȡĿ¼��graph.dat�ļ� �����ڽӱ�\n");
    VertexNode *vn = G->adjlist;
    //�Ȱ�G������ж�����Ϊ0�����ж�
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
    //���ļ��� �����ַ������������� ����ָ�����������
    FILE *fp = fopen("graph.dat", "r");
    char strLine[512], *buf;

    while (!feof(fp))
    {
        fgets(strLine, 512, fp);
        buf = strLine;
        int i = 0;
        //nodes����ǰ�����ж��ٸ��ߵ㣬���ں��ڱ����ߵ�
        int nodes = 0;
        while (buf[i]!=']')
        {
            //����ȡ��:ʱ ǰһ���ַ���Ϊ���� ��ӽ��ڽӱ�
            if (buf[i] == ':')
            {
                vn = addVertex(vn, buf[i-1]);
                //��������
                G->e += 1;
                i += 2;
                continue;
            }

            //����ȡ��-ʱ ǰһ���ַ���Ϊ�ߵ�
            if (buf[i] == '-')
            {
                //�߼�1
                G->n += 1;
                //�����ڴ�ռ�
                EdgeNode *edgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));

                EdgeNode *p;
                p=edgeNode;

                int j = 0;
                int value;
                //������values������Ŷ�ȡ���ıߵ��Ȩֵ
                char values[10] = {0};
                //j�����ȡ���ڼ����ַ�
                if (j == 0)
                {
                    edgeNode->adjvex = buf[i-1];
                }
                                
                //����ȡ��,ʱ ������ȡ����ߵ��ѭ��
                while (buf[i]!=',')
                {
                    //��ȡ����-֮���ÿ���ַ����뻺����
                    values[j] = buf[i+1];
                    //����ȡ��,��ǰһ���ַ�ʱ ��values���������ַ�ת��int���͵�value
                    if (buf[i+1] == ',')
                    {
                        value = atoi(values);
                        //printf("��ȡ���ıߵ�%c,����Ȩֵ%d\n", edgeNode->adjvex, value);
                        edgeNode->value = value;
                        //ͷ�巨�����½ڵ�
                        p->next = vn->edgenext;
                        vn->edgenext = p;
                        nodes += 1;
                        break;
                    }
                     
                    j++;
                    i++;
                }

            }
            //????��????? ??????????????��????next??��NULL ????vn??????
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
    //������ �±긳ֵ ��������
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
        printf("����%c�����Ϊ:%d,����Ϊ:%d\n",io[tag].vertex,io[tag].in,io[tag].out);
        tag++;
    }
    
    
    return G;
}

VertexNode* addVertex(VertexNode* vn, char vertex) {

    vn->vertex = vertex;
    return vn;

}
//�ڽӱ�������������
int DFS(AdjMatrix *G, int i, int num)
{
	EdgeNode *p;
	visited[i] = 1;
	printf("%c->", G->adjlist[i].vertex);
    num++;
	p = G->adjlist[i].edgenext;//��pָ��߱�ĵ�һ�����
	while (p)
	{
		if (!visited[p->tag])
		{
			num = DFS(G, p->tag, num);
		}
		p = p->next;
	}
    return num;
}

int DFSTraverse(AdjMatrix *G, int start, bool ismodified)
{
    int num = 0;
    if (ismodified)
    {
       	for (int i = 0; i < G->e; i++)
        {
            if (!visited[start])
            {
                DFS(G, start, num);
            }
        }
    } else 
    {
        for (int i = 0; i < G->e; i++)
        {
            visited[i] = 0;//��ʼ���������Ϊ0
        }
        for (int i = 0; i < G->e; i++)
        {
            if (!visited[start])
            {
                num = DFS(G, start, num);
                if (num < G->e)
                {
                    printf("�Ҳ�����ͨͼŶ");
                    return 1;
                }
                
            }
            
        }
        printf("������ͨͼŶ");
    }
    
    return 0;
}

void InitQueue(LinkQueue *q) //���г�ʼ��
{
	//����ͷ��㣬���׶�β��ָ��ͷ���
	Qptr firstnode = (Qptr)malloc(sizeof(Qnode));
	q->front = q->rear = firstnode;
	if (!q->front)
	{
		exit(0);
	}
	q->front->next = NULL;
}
//�����
void PushQueue(LinkQueue *q, int e)
{
	//�ڶ�β����Ԫ��
	Qptr p = (Qptr)malloc(sizeof(Qnode));
	if (!p)
	{
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}
//������
void DetQueue(LinkQueue *q, int &e)
{
	//�������ڶ��׽���
	if (q->front == q->rear)
	{
		printf("��������Ԫ�أ�\n");
		exit(0);
	}
	Qptr p = q->front->next;
	e = p->data;
	q->front->next = p->next;
	if (q->rear == p)
	{
		q->rear = q->front;
	}
	free(p);
}
//�����Ƿ�Ϊ��
int QueueEmpty(LinkQueue *q)
{
	if (q->front == q->rear)
		return 0;
	else
		return 1;
}

//������ȱ���
void BFSTraverse(AdjMatrix *G, int tag)
{
	int k;
	LinkQueue Q;
	EdgeNode *e;
	InitQueue(&Q);
	for (int i = 0; i < G->e; i++)
	{
		visited[i] = 0;//��ʼ���������
	}
	for (int i = 0; i < G->e; i++)
	{
		if (!visited[tag])
		{
			visited[tag] = 1;
			printf("%c->", G->adjlist[tag].vertex);
			PushQueue(&Q, tag);
		}
		while (QueueEmpty(&Q))
		{
			DetQueue(&Q, k);
			e = G->adjlist[k].edgenext;
			while (e)
			{
				if (!visited[e->tag])
				{
					visited[e->tag] = 1;
					printf("%c->", G->adjlist[e->tag].vertex);
					PushQueue(&Q, e->tag);
				}
				e = e->next;
			}
		}
	}
}

//���Ҷ��� �ж��Ƿ���� ������ɾ�����㲢��DFS���� ��������������
void FindVertex(AdjMatrix* G, char key)
{
    VertexNode *p = G->adjlist;
    EdgeNode *pf = p->edgenext;
    EdgeNode *ps;

    while (p->vertex != 0)
    {
        if(p->vertex == key)
        {
            //��������һ
            G->e--;
            //ɾ���ڵ�������Ϣ��ɾ����
            for (int i = p->tag; G->adjlist[i].vertex != 0; i++)
            {
                //����ǰ��
                G->adjlist[i] = G->adjlist[i+1];
                G->adjlist[i].tag = i;
                //�޸ķ�������
                for (int j = 0; j < G->e; j++)
                {
                    visited[j] = 0;//��ʼ���������Ϊ0
                }
                visited[i] = 1;
            }
            printf("�Ѿ��ɹ�ɾ���ڵ�%c,�±�Ϊ%d\n", key, p->tag);

            //����ָ�� ָ��ͼ��ͷ�ڵ�
            p = G->adjlist;
            while (p->vertex != 0)
            {
                //����ö����ޱߵ�
                if(p->edgenext == NULL)
                {
                    p++;
                    continue;
                }
                pf=p->edgenext;
                ps=pf->next;
                //����һ���ڵ������Ҫɾ���Ľڵ�ʱ
                if(pf->adjvex == key)
                {
                    pf->next = ps->next;
                    printf("ɾ��%c---->%c��\n", p->vertex, key);
                    free(ps);
                    p++;
                    continue;
                }
                //���м�ڵ���Ҫ��ɾ��ʱ
                while (ps != NULL)
                {
                    if(ps->adjvex == key)
                    {
                        pf->next = ps->next;
                        printf("ɾ��%c---->%c��\n", p->vertex, key);
                        free(ps);
                        break;
                    }
                    pf = pf->next;
                    ps = ps->next;
                }
                p++;
                
            }
            //ɾ���ڵ㵼��tag�ı�
            p = G->adjlist;
            VertexNode *v = p;
            int tag = 0;
            while (p->vertex != 0)
            {
                EdgeNode *o = p->edgenext;
                while (o)
                {
                    v = G->adjlist;
                    while (v)
                    {
                        if (v->vertex == o->adjvex)
                        {
                            o->tag = v->tag;
                            v = p;
                            break;
                        }
                        v++;
                    }
                    o=o->next;
                }
                tag++;
                p++;
            }
            //��DFS����

            DFSTraverse(G, 0, true);
            return;
        }
        p++;
    }
    printf("û���ҵ��ڵ�%cŶ",key);
    return;
}