/********************************************************************************* 
* Granger Pasko, gpasko
* 2022 Spring CSE101 PA4 
* Matrix.c 
* Creating matrix ADTS, Constructors, and Destructors
*********************************************************************************/
#include <stdio.h>
#include "List.h"
#include "Matrix.h"

typedef struct MatrixObj{
	List* rows;
	int size;
}MatrixObj;

typedef struct EntryObj* Entry;

typedef struct EntryObj{
	int col;
	double val;
}EntryObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix new = calloc(1, sizeof(MatrixObj));
	new->size = n;
	new->rows = calloc(n + 1, sizeof(List));
	for(int i = 1; i <= n; i++){
		new->rows[i] = newList();
	}
	return new;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if(*pM == NULL){
		printf("Matrix Error: calling freeMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	makeZero(*pM);
	for(int i = 1; i <= size(*pM); i++){
		freeList(&(*pM)->rows[i]);
	}
	free(*pM);
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	int count = 0;
	for(int i = 1; i <= size(M); i++){
		count += length(M->rows[i]);
	}
	
	return count;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(A == B){
		return 1;
	}

	if(size(A) != size(B) || NNZ(A) != NNZ(B)){
		return 0;
	}

	for(int i = 1; i <= size(A); i++){
		if(length(A->rows[i]) == length(B->rows[i])){
			if(length(A->rows[i]) != 0){
				moveFront(A->rows[i]);
				moveFront(B->rows[i]);
				while(index(B->rows[i]) != -1 && index(A->rows[i]) != -1){
					if(((Entry)get(A->rows[i]))->val == ((Entry)get(B->rows[i]))->val){
						moveNext(A->rows[i]);
						moveNext(B->rows[i]);
					}
					else{
						return 0;
					}
				}
			}
		}
		else{
			return 0;
		}
	}
	return 1;
	
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= size(M); i++){
		if(length(M->rows[i]) != 0){
			while(length(M->rows[i]) != 0){
				deleteFront(M->rows[i]);
			}

		}
		clear(M->rows[i]);
	}
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if(M == NULL){
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(i < 1 || i > size(M)){
		printf("Matrix Error: calling changeEntry() on out of bounds row index\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1 || j > size(M)){
		printf("Matrix Error: calling changeEntry() on out of bounds collumn index\n");
		exit(EXIT_FAILURE);
	}
	if(length(M->rows[i]) == 0){
		if(x == 0){
			return;
		}
		Entry new = malloc(sizeof(EntryObj));
		new->col = j;
		new->val = x;
		append(M->rows[i], new);
		return;
	}
	moveFront(M->rows[i]);
	while(index(M->rows[i]) != -1){
		if(((Entry)get(M->rows[i]))->col == j){
			if(x == 0.0){
				delete(M->rows[i]);
				return;
			}
			Entry new = malloc(sizeof(EntryObj));
			new->col = j;
			new->val = x;
			insertAfter(M->rows[i], new);
			delete(M->rows[i]);
			return;
		}
		if(((Entry)get(M->rows[i]))->col > j && x != 0.0){
			Entry new = malloc(sizeof(EntryObj));
			new->col = j;
			new->val = x;
			insertBefore(M->rows[i], new);
			return;
		}
		moveNext(M->rows[i]);
	}
	if(x != 0.0){
		Entry new = malloc(sizeof(EntryObj));
		new->col = j;
		new->val = x;
		append(M->rows[i], new);
	}
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix new = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1 && length(A->rows[i]) != 0){
			changeEntry(new, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val);
			moveNext(A->rows[i]);
		}
	}
	return new;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	return A;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1 && length(A->rows[i]) != 0){
			((Entry)get(A->rows[i]))->val = x * ((Entry)get(A->rows[i]))->val;
			moveNext(A->rows[i]);
		}
	}

	return A;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling sum() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix sum = newMatrix(size(A));
	/*
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1 && length(A->rows[i]) != 0){
			Entry E = malloc(sizeof(EntryObj));
			E->col = ((Entry)get(A->rows[i]))->col;
			E->val = ((Entry)get(A->rows[i]))->val;
			append(sum->rows[i], E);
			moveNext(A->rows[i]);
		}
	}
	for(int i = 1; i <= size(B); i++){
		moveFront(B->rows[i]);
		while(index(B->rows[i]) != -1 && length(B->rows[i]) != 0){
			if(((Entry)get(A->rows[i]))->col){
				//if col is same as targetadd val to node in sum
			}
			else{
				Entry E = malloc(sizeof(EntryObj));
				E->col = ((Entry)get(A->rows[i]))->col;
				E->val = ((Entry)get(A->rows[i]))->val;
				//insert sort
			}
			moveNext(A->rows[i]);
		}
	}*/
	return sum;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling diff() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix diff = newMatrix(size(A));
	return diff;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling product() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix prod = newMatrix(1);
	return prod;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i  <= size(M); i++){
		if(length(M->rows[i]) != 0){
			fprintf(out, "%d: ", i);
			moveFront(M->rows[i]);
			while(index(M->rows[i]) != -1){
				if(((Entry)get(M->rows[i]))->val != 0.0){
					fprintf(out, "(%d, %.1f) ", ((Entry)get(M->rows[i]))->col, ((Entry)get(M->rows[i]))->val);
				}
				moveNext(M->rows[i]);
			}
			fprintf(out, "\n");
		}

	}
	return;;
}