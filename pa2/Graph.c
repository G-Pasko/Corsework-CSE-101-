#include <stdio.h>
#include "Graph.h"
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
	new->parentIndex = NULL;
	new->distance = NULL;
	new->order = 0;
	new->order = n + 1;
	new->size = n;
	return new;
}

void freeGraph(Graph* pG){				//Frees all heap memory associated with pG and
	List front;
	for(int i = 0; i < ){
		while(front != NULL){
			;;
		}
	}


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
	return 0;
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
	return 0;
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
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < G->size; i++){
		G->nieghbors[i] = NULL;
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
	append(G->nieghbors[u+1], v);
	append(G->nieghbors[v + 1], u);
}
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: calling addEdge() on invalid integer values");
		exit(EXIT_FAILURE);
	}
}
void BFS(Graph G, int s){
	;;
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	;;
}