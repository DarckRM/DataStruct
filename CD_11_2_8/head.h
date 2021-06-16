//定义链表结构
typedef struct tnode{

    int data;
    struct  tnode* lchild;
    struct  tnode* rchild;

}*bitree, bitnode;

//分别定义平衡因子数
#define LH +1
#define EH  0
#define RH -1