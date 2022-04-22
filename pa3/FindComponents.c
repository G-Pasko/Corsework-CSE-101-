//FindComponents.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

extern char *strdup(const char *);

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Incorrect number of file arguments. Run 'Find Path <input file> <output file>'\n");
		exit(EXIT_FAILURE);
	}
	char buff[512];
	int lines = 0;
	FILE *input = fopen(argv[1], "r");
	if(input == NULL){
		printf("Input file is NULL'\n");
		exit(EXIT_FAILURE);
	}

	FILE *output = fopen(argv[2], "w");
	while((fgets(buff, 512, input) != NULL)){
		lines ++;
	}
	rewind(input);
	char** words = (char **)calloc(lines, sizeof(char*));
	int i = 0;
	char buff2[512];
	while((fgets(buff2, 512, input) != NULL)){
		words[i] = strdup(buff2);
		i++;
	}
	//Create our graph
	int num_vertices, v1, v2;
	sscanf(words[0], "%d", &num_vertices);
	Graph G = newGraph(num_vertices);
	//Add arcs to graph G
	for(i = 1; i < lines; i++){
		//fprintf(output, "%s\n", words[i]);
		sscanf(words[i], "%d %d",&v1, &v2);
		//printf("grabbed vertices %d and %d\n", v1, v2);
		if(v1 == 0 && v2 == 0){
			break;
		}
		if(v1 != 0 && v2 != 0){
			addArc(G, v1, v2);
		}
	}
	//Print adjacency lists
	printGraph(output, G);
	//Create list for runtime (initiated in numerical order)
	List L = newList();
	for(int i = 1; i <= num_vertices; i++){
		append(L, i);
	}
	//Run DFS on OG
	DFS(G, L);
	//Create transpose of G
	Graph T = transpose(G);
	//Run DFS with transpose graph and new List
	DFS(T, L);

	//Determine strong components
	moveBack(L);
	int component_num = 1;
	List temp = newList();
	while(index(L) != -1){
		append(temp, get(L));
		if(getParent(T, get(L)) == NIL){
			fprintf(output, "Component %d: ", component_num);
			//print temp in reverse order
			moveBack(temp);
			index(temp != -1){
				fprintf(output, "%d ", get(temp));
				moveNext(temp);
			}

			fprintf(output, "\n");
			while(length(temp) != 0){
				deleteFront(temp);
			}
		}
		movePrev(L);
	}

	return 0;
}