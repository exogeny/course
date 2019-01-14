#include <stdio.h>
#include <stdlib.h>

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
    int n;  // the number of vertext
    struct vertex_node * adj_lists;
};

void destory(struct graph * g)
{
    int num_vertext = g->n, i;
    struct edge_node   * current_edge, * tmp_e;
    struct vertex_node * currentlist = g->adj_lists, * tmp_v;
    for (i = 0; i < num_vertext; i++)
    {
        currentlist = (g->adj_lists + i);
        current_edge = currentlist->first;
        while (current_edge)
        {
            tmp_e = current_edge->next;
            free(current_edge);
            current_edge = tmp_e;
        }
    }
    free(g->adj_lists);
    free(g);
}

void print_graph(struct graph * g)
{
    int num_vertext = g->n, i;
    struct edge_node   * current_edge;
    struct vertex_node * currentlist = g->adj_lists;
    for (i = 0; i < num_vertext; i++)
    {
        currentlist = (g->adj_lists + i);
        printf("%d -> ", currentlist->vex);

        current_edge = currentlist->first;
        while (current_edge)
        {
            printf("%d -> ", current_edge->adjvex);
            current_edge = current_edge->next;
        }
        printf(" nil\n");
    }
    printf("\n");
}

struct graph * build_graph(int num_vertext)
{
    int i;
    struct graph * g = (struct graph *)malloc(sizeof(struct graph));
    g->n = num_vertext;
    g->adj_lists = (struct vertex_node *)malloc(sizeof(struct vertex_node) * num_vertext);

    for (i = 0; i < num_vertext; i++)
    {
        g->adj_lists[i].vex = i + 1;
        g->adj_lists[i].first = NULL;
    }

    return g;
}

void transpose(struct graph * g, struct graph * t)
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

int main(int argc, char const *argv[])
{
    int i, num_vertext, tmp;

    printf("Please enter the number of vertext:");
    scanf("%d", &num_vertext);
    while (num_vertext < 0)
    {
        printf("Invalid, Please enter again:");
        scanf("%d", &num_vertext);
    }

    struct edge_node * tmp_node = NULL, * current;
    struct graph * g = build_graph(num_vertext);
    struct graph * t = build_graph(num_vertext);

    for (i = 0; i < num_vertext; i++)
    {
        printf("Now, enter the %dth vertext(0 to finish): \n", i + 1);
        current = NULL;

        scanf("%d", &tmp);
        while(tmp != 0)
        {
            if (tmp < 1 || tmp > num_vertext)
            {
                printf("The range is from 1 to %d!\n", num_vertext);
                continue;
            }

            tmp_node = (struct edge_node *)malloc(sizeof(struct edge_node));
            tmp_node->adjvex = tmp;
            if (current)
            {
                current->next = tmp_node;
                current = current->next;
            }
            else
            {
                g->adj_lists[i].first = tmp_node;
                current = tmp_node;
            }
            current->next = NULL;
            scanf("%d", &tmp);
        }
    }

    transpose(g, t);

    print_graph(g);
    print_graph(t);
    destory(g);
    destory(t);

    return 0;
}

