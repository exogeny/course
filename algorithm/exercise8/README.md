# 习题八

## 描述

给定有向图G：
1. 证明图G的凝聚图是有向无环的。
2. 若图G以邻接表的方式存储，试写出一个算法求图G的转置图。

## 解答

### 问题1

反证法：假设有向图G的凝聚图是有环的，那么凝聚图中将存在**强连通分量**。而凝聚图将会将强连通分量**凝聚**成一个顶点，明显跟之前的假设相冲突。因此有向图的凝聚图是不存在环的，即为有向无环图。

### 问题2

**思路**：
由于邻接表存储了从该点出发的所有信息。而转置图是指将所有边的方向反转。那么也就是图G的邻接表在其转置图中是代表以该顶点为终点边的信息，求转置图的邻接表只需要将原图的顶点作为终点信息添加到原图的终点中即可。

**算法实现**：
定义邻接表存储图的结构：
``` c
/**
 * define the node of edge.
 **/
struct edge_node
{
    int adjvex;
    struct edge_node * next;
};

/**
 * define the node of vertex.
 **/
struct vertex_node
{
    int vex;
    struct edge_node * first;
};

/**
 * define the graph.
 **/
struct graph
{
    struct vertex_node * adj_lists;
};
```

转置的实现：
``` c
void transpose(struct graph * origin, struct graph * transposition)
{
    int num_vertext = g->n, i;
    struct edge_node * gedge, * t_edge, * tmp;
    struct vertex_node * glist;
    struct vertex_node * tlist;

    for (i = 0; i < num_vertext; i++)
    {
        glist = (g->adj_lists + i);
        gedge = glist->first;

        while (gedge)
        {
            tlist = (t->adj_lists + gedge->adjvex - 1);
            t_edge = tlist->first;
            if (t_edge)
            {
                tmp = t_edge->next;
                t_edge->next = (struct edge_node *)malloc(sizeof(struct edge_node));
                t_edge = t_edge->next;
                t_edge->next = tmp;
            }
            else
            {
                tmp = NULL;
                t_edge = (struct edge_node *)malloc(sizeof(struct edge_node));
                tlist->first = t_edge;
            }
            t_edge->adjvex = glist->vex;
            t_edge->next = tmp;
            gedge = gedge->next;
        }
    }
}
```

**测试结果**：
程序请参考[answer.c(https://github.com/TerenceWangh/course/blob/master/algorithm/exercise8/answer.c)
![测试结果](https://github.com/TerenceWangh/course/blob/master/algorithm/exercise8/snap.png)