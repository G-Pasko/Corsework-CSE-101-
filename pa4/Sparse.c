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
	fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(output, A);

	fprintf(output, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(output, B);

	fprintf(output, "(1.5)*A =\n");
	Matrix C = scalarMult(1.5, A);
	printMatrix(output, C);

	fprintf(output, "A+B =\n");
	Matrix D = sum(A, B);
	printMatrix(output, D);

	fprintf(output, "A+A =\n");
	Matrix E =sum(A, A);
	printMatrix(output, E);

	fprintf(output, "B-A =\n");
	Matrix F = diff(B, A);
	printMatrix(output, F);

	fprintf(output, "A-A =\n");
	Matrix J = diff(A, A);
	printMatrix(output, J);

	fprintf(output, "Transpose(A) =\n");
	Matrix G = transpose(A);
	printMatrix(output, G);

	fprintf(output, "A*B =\n");
	Matrix H = product(A,B);
	printMatrix(output, H);

	fprintf(output, "B*B =\n");
	Matrix I = product(B,B);
	printMatrix(output, I);

	fclose(input);
	fclose(output);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);

	
	return 0;
}