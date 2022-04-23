/********************************************************************************* 
* Granger Pasko, gpasko
* 2022 Spring CSE101 PA3 
* Graph.h 
* Declaring all graph functions used in Graph.c
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#define INF -420
#define NIL -69
#define UNDEF -80085
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);