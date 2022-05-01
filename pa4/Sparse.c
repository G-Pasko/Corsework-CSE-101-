//-----------------------------------------------------------------------------
// Sparce.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

extern char *strdup(const char *);



int main(int argc, char* argv[]){
	/*
	if(argc != 3){
		fprintf(stderr, "Incorrect number of files provided\n");
		return 0;
	}
	char buff[512];
	int lines = 0;
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	fgets(buff, 512, input);
	sscanf(buff, "%d %d %d", &size, &NNZ1, &NNZ2);
	Matrix A = newMatrix(size);
	while((fgets(buff, 512, input) != NULL) && strcmp(buff, "\n") != 0){
		sscanf(buff, "%d %d %f",&row, &col, &val);
		changeEntry(A, row, col, val);
	}
	Matrix B = newMatrix(size);
	while((fgets(buff, 512, input) != NULL)){
		sscanf(buff, "%d %d %f",&row, &col, &val);
		changeEntry(B, row, col val);
	}
	//Add arcs to graph G
	for(i = 3; i <= 3 + NNZ1; i++){
		//fprintf(output, "%s\n", words[i]);
		sscanf(words[i], "%d %d %f",&row, &col, &val);
		//printf("grabbed vertices %d and %d\n", v1, v2);
		changeEntry(A, row, col, val);
	}
	int stop = i;
	for(i = stop; i <= stop + NNZ2; i++){
		sscanf(words[i], "%d %d %f",&row, &col, &val);
		//printf("grabbed vertices %d and %d\n", v1, v2);
		changeEntry(B, row, col, val);
	}
	printMatrix(output, A);
	printMatrix(output, B);




	free(words);
	fclose(input);
	fclose(output);
	freeMatrix(&A);
	freeMatrix(&B);
	*/
	return 0;
}