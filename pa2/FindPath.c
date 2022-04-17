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
	int num_vertices, v1, v2;
	int start;
	sscanf(words[0], "%d", &num_vertices);
	Graph G = newGraph(num_vertices);
	for(i = 1; i < lines; i++){
		//fprintf(output, "%s\n", words[i]);
		sscanf(words[i], "%d %d",&v1, &v2);
		//printf("grabbed vertices %d and %d\n", v1, v2);
		if(v1 == 0 && v2 == 0){
			start = i + 1;
			break;
		}
		if(v1 != 0 && v2 != 0){
			addEdge(G, v1, v2);
		}
	}

	printGraph(output, G);
	for(i = start; i < lines -1; i++){
		//find path
		sscanf(words[i], "%d %d", &v1, &v2);
		//printf("fidning path from %d to %d\n", v1, v2);
		BFS(G, v1);
		List L = newList();
		getPath(L, G, v2);
		//cehck for inf dinstance and NIL path
		if(getDist(G, v2) == INF){
			fprintf(output, "The distance from %d to %d is infinity\n", v1, v2);
			fprintf(output, "No %d-%d path exists\n", v1, v2);
		}
		else{
			fprintf(output, "The distance from %d to %d is %d\n", v1, v2, getDist(G, v2));
			fprintf(output, "A shortest %d-%d path is: ", v1, v2);
			printList(output, L);
			fprintf(output, "\n\n");
		}
		freeList(&L);
		
	}

	//freeList(&new);

	for(i = 0; i < lines; i++){
		free(words[i]);
	}
	freeGraph(&G);
	free(words);
	fclose(input);
	fclose(output);


	return 0;
}