#include <stdio.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char argv[]){
	if(argc != 3){
		pritnf("Incorrect number of file arguments. Run 'Find Path <input file> <output file>'\n");
		exit(EXIT_FAILURE);
	}
	char buff[512];
	int lines = 0;
	FILE *input = fopen(argv[1], "r");
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
	for(i = 0; i < lines; i++){
		fprintf("%s\n", words[i]);
	}

	//freeList(&new);

	for(i = 0; i < length; i++){
		free(words[i]);
	}
	free(words);
	fclose(input);
	fclose(output);


	return 0;
}