//定义邻接表基本结构
//最大顶点数

#define MaxVertices 100
int visited[MaxVertices]; //访问标志数组

//边表
typedef struct node { 

    //边点
    char adjvex;
    //下标
    int tag;
    //权值
    int value;

    node* next;

}EdgeNode;  

//顶点表  
typedef struct {

    //顶点
    char vertex;
    //下标
    int tag;
    EdgeNode* edgenext;

}VertexNode;  
  
typedef VertexNode AdjList[MaxVertices];//顶点表数组

typedef struct {
    //顶点
    char vertex;
    //入度
    int in;
    //出度
    int out;
}InOutInfo;
  
typedef struct {

    AdjList adjlist;  
    int n,e;

}AdjMatrix;

AdjMatrix* createGraph(AdjMatrix*);
VertexNode* addVertex(VertexNode* vn, char vertex);
int DFS(AdjMatrix *G, int i);
int DFSTraverse(AdjMatrix *G, int start);