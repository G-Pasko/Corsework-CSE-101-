#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#define INF -420
#define NIL -69


typedef struct GraphObj{
	List *neighbors;
	char *color;
	int order;				//# of vertices
	int size;				//# of edges (order -1)
	int *parentIndex;
	int *distance;
}GraphObj;

//typedef GraphObj* Graph;


Graph newGraph(int n){
	Graph new = calloc(n + 1, sizeof(GraphObj));
	new->color = NULL;
	for(int i = 1; i < n + 1; i++){
		new->neighbors[i] = newList();
	}
	new->parentIndex[n] = NIL;
	new->distance[n] = INF;
	new->order = n + 1;
	new->size = 0;
	return new;
}

void freeGraph(Graph* pG){				//Frees all heap memory associated with pG and
	if(*pG == NULL || pG == NULL){
		printf("Graph Error: calling freeGraph() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getSize(*pG); i++){
		freeList((*pG)->neighbors[i]);
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
		if(G->color[i] != "b"){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->parentIndex[i] != NIL){
			return i;
		}
	}
}
int getParent(Graph G, int u){
	//if BFS not been called: return error
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(G); i++){
		if(G->color[i] != "b"){
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
		if(G->color[i] != "b"){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getSize(G); i++){
		G->neighbors[i] = NULL;
		G->color[i] = "w";
		G->distance[i] = NIL;
	}
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
	for(int i = 1; i < getOrder(G); i++){
		moveFront(G->neighbors[i]);
		while(G->neighbors[i] != NULL){
			x = get(G->neighbors[i]);
			G->color[x] = "w";
			G->distance[x] = INF;
			G->parentIndex[x] = NIL;
		}
		moveNext(G->neighbors[i]);


	}

	G->color[s] = "g";
	G->distance[s] = 0;
	G->parentIndex[s] = NIL;
	List Q = newList();
	append(Q, s);
	moveFront(Q);
	while(Q != NULL){
		x = get(Q);
		deleteFront(Q);
		moveFront(G->neighbors[x]);
		while(get(G->neighbors[x]) != NULL){
			y = get(G->neighbors[x]);
			if(G->color[y] == "w"){
				G->color[y] = "g";
				G->distance[y] = G->distance[x] + 1;
				G->parentIndex[y] = x;
				append(Q, y);
			}
			moveNext(G);
		}
		G->color[x] = "b";
	}
	freeList(*Q);
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i = 1; i < getSize(G); i++){
		fprintf(out, "%d: ", i);
		moveFront(G->neighbors[i]);
		int j = get(G->neighbors[i]);
		while(get(G->neighbors[i]) != NULL){
			fprintf(out, "%d ", j);
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
	}
}