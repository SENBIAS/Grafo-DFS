#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXV 105
#define infinite 2147483647
#define NIL -1
#define WHITE 2
#define GRAY 1
#define BLACK 0

using namespace std;

struct edge
{
    int vertex;
    int weight;
    struct edge *next;
};

typedef struct
{
    struct edge *edges[MAXV + 1];
    int nvertex;
    int nedges;
}graph;

graph G;
int timee=0;

void freeMemoryGraph()
{
    int idVertex;
    struct edge *nodeLeft, *nodeRight;
    for(idVertex=1; idVertex<=G.nvertex; idVertex++)
    {
        nodeLeft=G.edges[idVertex];
        while(nodeLeft != NULL)
        {
            nodeRight=nodeLeft->next;
            free(nodeLeft);
            nodeLeft=nodeRight;
        }
        G.edges[idVertex]=NULL;
    }
}

void DFS_Visit(int u, int phi[], int d[], int f[], int color[])
{
    int v;
    struct edge *actualNode;
    color[u]=GRAY;
    timee++;
    d[u]=timee;
    actualNode=G.edges[u];
    while(actualNode != NULL)
    {
        v=actualNode->vertex;
        if(color[v]==WHITE)
        {
            phi[v]=u;
            DFS_Visit(v, phi, d, f, color);
        }
        actualNode=actualNode->next;
    }
    color[u]=BLACK;
    timee++;
    f[u]=timee;
}

void DFS(int phi[], int d[], int f[]) //Depth First Search
{
    int idVertex, u, color[MAXV];
    for(idVertex=1; idVertex<=G.nvertex; idVertex++)
    {
        color[idVertex]=WHITE;
        phi[idVertex]=NIL;
    }
    timee=0;
    for(idVertex=1; idVertex<=G.nvertex; idVertex++)
    {
        if(color[idVertex] == WHITE)
        {
            DFS_Visit(idVertex, phi, d, f, color);
        }
    }
}

void printGraph()
{
    int idVertex;
    struct edge *actualNode;
    printf("\nGraph by adjacency lists:\n\n");
    for(idVertex=1; idVertex<=G.nvertex; idVertex++)
    {
        printf("[Vertex: %d]", idVertex);
        actualNode=G.edges[idVertex];
        while(actualNode != NULL)
        {
            printf("-> (%d, %d)", actualNode->vertex, actualNode->weight);
            actualNode=actualNode->next;
        }
        printf("->NULL\n");
    }
}

void solver()
{
    int phi[MAXV], d[MAXV], f[MAXV], idVertex;
    DFS(phi, d, f);
    printf("Array of Discovers:\n");
    for(idVertex=1; idVertex <= G.nvertex; idVertex++)
    {
        printf("%d ", d[idVertex]);
    }
    printf("\n");
    printf("Array of Finalization:\n");
    for(idVertex=1; idVertex <= G.nvertex; idVertex++)
    {
        printf("%d ", f[idVertex]);
    }
    printf("\n");
    printf("Array of Phi:\n");
    for(idVertex=1; idVertex <= G.nvertex; idVertex++)
    {
        printf("%d ", phi[idVertex]);
    }
    printf("\n");
}

int main()
{
    int idCase, totalCases, n, m, u, v, w=1;
    int idEdge, idVertex;
    struct edge *newNode, *actualNode;
    scanf("%d", &totalCases);
    for(idCase=1; idCase<=totalCases; idCase++)
    {
        scanf("%d %d", &n, &m);
        G.nvertex=n;
        G.nedges=m;
        for(idVertex=1; idVertex<=n; idVertex++)
            G.edges[idVertex]=NULL;
        for(idEdge=1; idEdge<=m; idEdge++)
        {
            scanf("%d %d", &u, &v);

            newNode=(struct edge *)malloc(sizeof(struct edge));
            newNode->vertex=v;
            newNode->weight=w;
            newNode->next=G.edges[u];
            G.edges[u]=newNode;

            newNode=(struct edge *)malloc(sizeof(struct edge));
            newNode->vertex=u;
            newNode->weight=w;
            newNode->next=G.edges[v];
            G.edges[v]=newNode;
        }
        printGraph();
        solver();
        freeMemoryGraph();
        //printGraph();
    }
    return 0;
}
