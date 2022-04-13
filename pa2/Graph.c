#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#define INF -420
#define NIL -69


//white = 0
//grey = 1
//black = 2


typedef struct GraphObj{
	List *neighbors;
	int *color;
	int order;				//# of vertices
	int size;				//# of edges (order -1)
	int *parentIndex;
	int *distance;
	int source;
}GraphObj;

//typedef GraphObj* Graph;


Graph newGraph(int n){
	Graph new = calloc(n + 1, sizeof(GraphObj));
	//printf("Calloced\n");
	new->color = (int *)calloc(n + 1, sizeof(int));
	//printf("Calloced\n");
	new->parentIndex = (int *)calloc(n + 1, sizeof(int));
	//printf("Calloced\n");
	new->distance = (int *)calloc(n + 1, sizeof(int));
	//printf("Calloced\n");
	for(int i = 1; i < n + 1; i++){
		new->neighbors[i];
		new->neighbors[i] = newList();
		printf("Calloced %d lists\n", i);
	}
	printf("Calloced all lists\n");
	new->source = NIL;
	new->order = n + 1;
	new->size = 0;
	return new;
}

void freeGraph(Graph* pG){				//Frees all heap memory associated with pG and
	if(*pG == NULL || pG == NULL){
		printf("Graph Error: calling freeGraph() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(*pG); i++){
		freeList(&(*pG)->neighbors[i]);
	}
	free(*pG);
	*pG = NULL;
}

int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->color[i] != 2 ){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->parentIndex[i] == NIL){
			return i;
		}
	}
	return G->source;

}
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->color[i] != 2){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	return G->parentIndex[u];
}
int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	if(G->source == 0){
		return INF;
	}
	return G->distance[u];
}
void getPath(List L, Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->color[i] != 2){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	if(G->distance[u] == INF){
		append(L, NIL);
	}
	else{
		append(L, u);
		u = getParent(G, u);
		getPath(L, G, u);
	}

	//appends path to List
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getSize(G); i++){
		G->neighbors[i] = NULL;
		G->color[i] = 0;
		G->distance[i] = NIL;
	}
	G->order = 0;
	G->size = 0;
}
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: calling addEdge() on invalid integer values");
		exit(EXIT_FAILURE);
	}
	if(u > getOrder(G) || v > getOrder(G)){
		printf("Graph Error: calling addEdge() on invalid integer values");
		exit(EXIT_FAILURE);
	}
	append(G->neighbors[u+1], v);
	append(G->neighbors[v + 1], u);

	G->size ++;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: calling addArc() on invalid integer values");
		exit(EXIT_FAILURE);
	}
	if(u > getOrder(G) || v > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid integer values");
		exit(EXIT_FAILURE);
	}
	append(G->neighbors[u+1], v);
	G->size ++;
}

void BFS(Graph G, int s){
	//moveFront(G->neighbors[s]);
	int x;
	G->source = s;
	for(int i = 1; i < getOrder(G); i++){
		moveFront(G->neighbors[i]);
		while(G->neighbors[i] != NULL){
			x = get(G->neighbors[i]);
			G->color[x] = 0;
			G->distance[x] = INF;
			G->parentIndex[x] = NIL;
		}
		moveNext(G->neighbors[i]);
	}

	G->color[s] = 1;
	G->distance[s] = 0;
	G->parentIndex[s] = NIL;
	List Q = newList();
	append(Q, s);
	moveFront(Q);
	while(Q != NULL){
		x = get(Q);
		deleteFront(Q);
		moveFront(G->neighbors[x]);
		while(index(G->neighbors[x]) != -1){
			int y = get(G->neighbors[x]);
			if(G->color[y] != 0){
				G->color[y] = 1;
				G->distance[y] = G->distance[x] + 1;
				G->parentIndex[y] = x;
				append(Q, y);
			}
			moveNext(G->neighbors[x]);
		}
		G->color[x] = 2;
	}
	freeList(&Q);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i = 1; i < getSize(G); i++){
		fprintf(out, "%d: ", i);
		moveFront(G->neighbors[i]);
		int j = get(G->neighbors[i]);
		while(get(G->neighbors[i]) < getOrder(G)){
			fprintf(out, "%d ", j);
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
	}
}