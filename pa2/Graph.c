#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#define INF -1;
#define nil 69;


typedef struct GraphObj{
	List neighbors[]= {};
	char color[] = {};		
	int order;				//# of vertices
	int size;				//# of edges (order -1)
	int parentIndex[] = {};
	int distance[] = {};
}GraphObj;


Graph newGraph(int n){
	Graph new = calloc(n, sizeof(GraphObj));
	new->color = NULL;
	new->neighbors[] = NULL;
	new->parentIndex = nil;
	new->distance = inf;
	new->order = n + 1;
	new->size = n;
	return new;
}

void freeGraph(Graph* pG){				//Frees all heap memory associated with pG and
	List front;
	for(int i = 1; i < getSize(G); i++){
		freeList(neighbors[i]);
	}
	free(*pG);
	*pG = NULL;
	return 0;						
}

int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	return G->order;}

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
	for(int i = 1; i < getOrder(g); i++){
		if(color[i] != "b"){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	for(int i = 1; i < getOrder(g); i++){
		if(parentIndex[i] != nil){
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
	if(u < 1 || u > getOrder(g)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(g); i++){
		if(color[i] != "b"){
			printf("Graph Error: calling getParent() before BFS");
			exit(EXIT_FAILURE);
		}
	}
	return parentIndex[u];
}
int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(g)){
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
	if(u < 1 || u > getOrder(g)){
		printf("Graph Error: calling getPath() on out of bounds node");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(g); i++){
		if(color[i] != "b"){
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
	for(int i = 1; i < G->size; i++){
		G->neighbors[i] = NULL;
		G->color[i] = "w";
		G->distance[i] = nil;
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
}

void BFS(Graph G, int s){
	for(Node x; x != x->data != s; x = x->next){
		color[x] = "w";
		distance[x] = inf;
		parentIndex[x] = nil;
	}
	color[s] = "g";
	distance[s] = 0;
	parentIndex[s] = nil;
	List Q = newList();
	append(Q, s);
	moveFront(Q);
	while(Q != NULL){
		x = get(Q);
		deleteFront(Q);
		for(Node y = G->neighbors[x]; y != NULL; y = y->next){
			if(color[y] == "w"){
				color[y] = "g";
				distance[y] = distance[x] + 1;
				parentIndex[y] = x;
				append(Q, y);
			}
		}
		color[x] = "b";
	}
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
		printf(out, "\n");
	}
}