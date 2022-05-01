//-----------------------------------------------------------------------------
// Sparce.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Matrix.h"

extern char *strdup(const char *);



int main(int argc, char* argv[]){
	
	if(argc != 3){
		fprintf(stderr, "Incorrect number of files provided\n");
		return 0;
	}
	char buff[512];
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	fgets(buff, 512, input);
	int size, NNZ1, NNZ2;
	sscanf(buff, "%d %d %d", &size, &NNZ1, &NNZ2);
	fgets(buff, 512, input);
	Matrix A = newMatrix(size);
	int row, col;
	double val;
	while((fgets(buff, 512, input) != NULL) && strcmp(buff, "\n") != 0){
		sscanf(buff, "%d %d %lf",&row, &col, &val);
		changeEntry(A, row, col, val);
	}
	Matrix B = newMatrix(size);
	while((fgets(buff, 512, input) != NULL)){
		sscanf(buff, "%d %d %lf",&row, &col, &val);
		changeEntry(B, row, col, val);
	}
	printMatrix(output, A);
	printMatrix(output, B);




	fclose(input);
	fclose(output);
	freeMatrix(&A);
	freeMatrix(&B);
	
	return 0;
}