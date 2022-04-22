#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"


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
	int *discoverTime;
	int *finishTime;
	//int source;
}GraphObj;

//typedef GraphObj* Graph;


Graph newGraph(int n){
	Graph new = calloc(n + 1, sizeof(GraphObj));
	new->color = (int *)calloc(n + 1, sizeof(int));
	new->parentIndex = (int *)calloc(n + 1, sizeof(int));
	new->distance = (int *)calloc(n + 1, sizeof(int));
	new->discoverTime = (int *)calloc(n + 1, sizeof(int));
	new->finishTime = (int *)calloc(n + 1, sizeof(int));
	new->neighbors = calloc(n + 1, sizeof(List));
	for(int i = 1; i < n + 1; i++){
		new->neighbors[i] = newList();
	}
	//new->source = NIL;
	new->order = n;
	new->size = 0;
	return new;
}

void freeGraph(Graph* pG){				//Frees all heap memory associated with pG and
	if(*pG == NULL || pG == NULL){
		printf("Graph Error: calling freeGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(*pG); i++){
		freeList(&(*pG)->neighbors[i]);	
	}
	free((*pG)->finishTime);
	(*pG)->finishTime = NULL;
	free((*pG)->discoverTime);
	(*pG)->discoverTime = NULL;
	free((*pG)->neighbors);
	(*pG)->neighbors = NULL;
	free((*pG)->parentIndex);
	(*pG)->parentIndex = NULL;
	free((*pG)->color);
	(*pG)->color = NULL;
	free((*pG)->distance);
	(*pG)->distance = NULL;
	free(*pG);
	*pG = NULL;
}

int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
/*
int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->source;

}
*/
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() on out of bounds node\n");
		exit(EXIT_FAILURE);
	}
	/*if(G->source == NIL){
		return NIL;
	}*/
	
	return G->parentIndex[u];
}
int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDist() on out of bounds node\n");
		exit(EXIT_FAILURE);
	}
	/*if(G->source == NIL){
		return INF;
	}*/
	return G->distance[u];
}

int getDiscover(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDiscover() on out of bounds node\n");
		exit(EXIT_FAILURE);
	}

	return G->discoverTime[u];
}

int getFinish(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getFinish() on out of bounds node\n");
		exit(EXIT_FAILURE);
	}
	return G->finishTime[u];
}
void getPath(List L, Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on out of bounds node\n");
		exit(EXIT_FAILURE);
	}
	/*if(G->source == NIL){
		printf("Graph Error: calling getPath() before BFS\n");
		exit(EXIT_FAILURE);
	}
	if(u == G->source){
		append(L, u);
		return;
	}*/
	else if(G->parentIndex[u] == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, G->parentIndex[u]);
		append(L, u);
	}

	//appends path to List
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getSize(G); i++){
		G->neighbors[i] = NULL;

	}
	G->color = NULL;
	G->distance = NULL;
	G->order = 0;
	G->size = 0;
}
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: calling addEdge() on invalid integer values\n");
		exit(EXIT_FAILURE);
	}
	if(u > getOrder(G) || v > getOrder(G)){
		printf("Graph Error: calling addEdge() on invalid integer values\n");
		exit(EXIT_FAILURE);
	}
	if(length(G->neighbors[u]) == 0){
		append(G->neighbors[u], v);
	}
	else{
		moveFront(G->neighbors[u]);	
		while(index(G->neighbors[u]) >= 0){
			if(get(G->neighbors[u]) > v){
				insertBefore(G->neighbors[u], v);
				break;
			}
			else{
				moveNext(G->neighbors[u]);
			}
		}
		if(index(G->neighbors[u]) < 0){
			append(G->neighbors[u], v);
		}
	}
	if(length(G->neighbors[v]) == 0){
		append(G->neighbors[v], u);
	}
	else{
		moveFront(G->neighbors[v]);	
		while(index(G->neighbors[v]) >= 0){
			if(get(G->neighbors[v]) > u){
				insertBefore(G->neighbors[v], u);
				break;
			}
			else{
				moveNext(G->neighbors[v]);
			}
		}
		if(index(G->neighbors[v]) < 0){
			append(G->neighbors[v], u);
		}
	}


	//append(G->neighbors[u], v);
	//append(G->neighbors[v], u);

	G->size ++;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: calling addArc() on invalid integer values\n");
		exit(EXIT_FAILURE);
	}
	if(u > getOrder(G) || v > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid integer values\n");
		exit(EXIT_FAILURE);
	}
	for(moveFront(G->neighbors[u]); index(G->neighbors[u]) != -1; moveNext(G->neighbors[u])){
		if(get(G->neighbors[u]) == v){
			return;
		}
	}
	if(length(G->neighbors[u]) == 0){
		append(G->neighbors[u], v);
	}

	else{
		moveFront(G->neighbors[u]);	
		while(index(G->neighbors[u]) >= 0){
			if(get(G->neighbors[u]) > v){
				insertBefore(G->neighbors[u], v);
				break;
			}
			else{
				moveNext(G->neighbors[u]);
			}
		}
		if(index(G->neighbors[u]) < 0){
			append(G->neighbors[u], v);
		}
	}
	G->size ++;
}

void Visit(Graph G, int x, int* time, List S){
	//printf("time = %d\n", *time);
	*time = *time + 1;
	//printf("time = %d\n", *time);
	G->discoverTime[x] = *time; 
	//printf("distance from x is  %d\n", (*pG)->discoverTime[x]);
	G->color[x] = 1;
	moveFront(G->neighbors[x]);
	int y;
	while(index(G->neighbors[x]) != -1){
		y = get(G->neighbors[x]);
		if(G->color[y] == 0){
			G->parentIndex[y] = x;
			Visit(G, y, time, S);
		}
		moveNext(G->neighbors[x]);
	}
	G->color[x] = 2;
	*time = *time + 1;
	G->finishTime[x] = *time;
	prepend(S, x);
}

void DFS(Graph G, List S){
	if(length(S) != getOrder(G)){
		printf("Graph Error: Calling DFS with incompatable list\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = 0;
		G->parentIndex[i] = NIL;
	}
	int time = 0;
	moveFront(S);
	int len = length(S);
	for(int i = 0; i < len; i++){
		if(G->color[get(S)] == 0){
			Visit(G, get(S), &time, S);
		}
		moveNext(S);
	}
	for(int i = 0; i < len; i ++){
		deleteBack(S);
	}
}


/*
void BFS(Graph G, int s){
	//moveFront(G->neighbors[s]);
	int x;
	G->source = s;
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parentIndex[i] = NIL;
		//moveNext(G->neighbors[i]);
	}
	//printf("finished initialization\n");

	G->color[s] = 1;
	G->distance[s] = 0;
	G->parentIndex[s] = NIL;
	List Q = newList();
	append(Q, s);
	while(length(Q) != 0){
		moveFront(Q);
		x = get(Q);
		//printf("got q\n");
		deleteFront(Q);
		moveFront(G->neighbors[x]);
		while(index(G->neighbors[x]) != -1){
			int y = get(G->neighbors[x]);
			if(G->color[y] == 0){
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
*/
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	//fprintf(out, "pre-for loop\n");
	for(int i = 1; i <= getOrder(G); i++){
		//fprintf(out, "for loop #%d\n", i);
		fprintf(out, "%d: ", i);
		moveFront(G->neighbors[i]);
		int j;
		while(index(G->neighbors[i]) >= 0){
			j = get(G->neighbors[i]);
			fprintf(out, "%d ", j);
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
		//printf("finished first nieghbors\n");
	}
}

Graph copyGraph(Graph G){
	Graph copy = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) != -1){
			addArc(copy, i, get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
	}
	copy->size = G->size;
	return copy;
}

Graph transpose(Graph G){
	Graph T = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) != -1){
			addArc(T, get(G->neighbors[i]), i);
			moveNext(G->neighbors[i]);
		}
	}
	T->size = G->size;
	return T;
}
