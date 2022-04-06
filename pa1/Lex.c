#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <stdlib.h>
#include "List.h"


int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Incorrect number of files provided\n");
		return 0;
	}
	char buff[512];
	int lines = 0;
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	while((fgets(buff, 512, input) != NULL)){
		lines ++;
	}
	rewind(input);
	char buff2[512];
	char** words = (char **)calloc(lines, sizeof(char));
	int i = 0;
	while((fgets(buff2, 512, input) != NULL)){
		words[i] = buff2;
		i++;
	}
	int length = i;
	/*
	for(i = 0; i < length; i++){
		printf("%s", words[i]);
	}*/
	for(i = 0; i < length; i++){
		printf(output, "%s", words[i]);
	}


	fclose(input);
	return 0;
}