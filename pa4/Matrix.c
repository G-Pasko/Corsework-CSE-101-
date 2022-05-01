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
	int NNZ;
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
	new->NNZ = 0;
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
		freeList(&((*pM)->rows[i]));
	}
	free((*pM)->rows);
	(*pM)->rows = NULL;
	free(*pM);
	*pM = NULL;
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
	if(M == NULL){
		printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	/*
	int count = 0;
	for(int i = 1; i <= size(M); i++){
		moveFront(M->rows[i]);
		while(index(M->rows[i]) != -1){
			count ++;
			moveNext(M->rows[i]);
		}
		
		
		if(M->rows[i] != NULL){
			count += length(M->rows[i]);
		}
		
	}*/
	
	return M->NNZ;
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
				if(index(B->rows[i]) != index(A->rows[i])){
					return 0;
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
		while(length(M->rows[i]) != 0){
			moveFront(M->rows[i]);
			free(get(M->rows[i]));
			deleteFront(M->rows[i]);
			M->NNZ--;
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
		if(x == 0.0){
			return;
		}
		Entry new = malloc(sizeof(EntryObj));
		new->col = j;
		new->val = x;
		append(M->rows[i], new);
		M->NNZ ++;
		return;
	}
	moveFront(M->rows[i]);
	while(index(M->rows[i]) != -1){
		if(((Entry)get(M->rows[i]))->col == j){
			if(x == 0.0){
				free(get(M->rows[i]));
				//delete(M->rows[i]);
				M->NNZ --;
				return;
			}
			else{
				((Entry)get(M->rows[i]))->val = x;
				return;
			}
			
		}
		else if(((Entry)get(M->rows[i]))->col > j && x != 0.0){
			Entry new = malloc(sizeof(EntryObj));
			new->col = j;
			new->val = x;
			insertBefore(M->rows[i], new);
			M->NNZ ++;
			return;
		}
		else if(((Entry)get(M->rows[i]))->col > j && x == 0.0){
			return;
		}	
		moveNext(M->rows[i]);
	}
	if(index(M->rows[i]) == -1 && x != 0.0){
		Entry new = malloc(sizeof(EntryObj));
		new->col = j;
		new->val = x;
		M->NNZ ++;
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
	//do list copy w switched i and j values
	if(A == NULL){
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix new = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1 && length(A->rows[i]) != 0){
			changeEntry(new, ((Entry)get(A->rows[i]))->col, i, ((Entry)get(A->rows[i]))->val);
			moveNext(A->rows[i]);
		}
	}
	return new;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix scalar = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1 && length(A->rows[i]) != 0){
			changeEntry(scalar, i, ((Entry)get(A->rows[i]))->col, x * ((Entry)get(A->rows[i]))->val);
			moveNext(A->rows[i]);
		}
	}

	return scalar;
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
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
			if(((Entry)get(A->rows[i]))->col == ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(A->rows[i]))->val + ((Entry)get(B->rows[i]))->val;
				changeEntry(sum, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val + ((Entry)get(B->rows[i]))->val);
				moveNext(A->rows[i]);
				moveNext(B->rows[i]);
			}
			else if(((Entry)get(A->rows[i]))->col < ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(A->rows[i]))->val;
				changeEntry(sum, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val);
				moveNext(A->rows[i]);
			}
			else if(((Entry)get(A->rows[i]))->col > ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(B->rows[i]))->val;
				changeEntry(sum, i, ((Entry)get(B->rows[i]))->col, ((Entry)get(B->rows[i]))->val);
				moveNext(B->rows[i]);
			}
		}
		if(index(A->rows[i]) == -1 && index(B->rows[i]) >= 0){
			while(index(B->rows[i]) != -1){
				changeEntry(sum, i, ((Entry)get(B->rows[i]))->col, ((Entry)get(B->rows[i]))->val);
				moveNext(B->rows[i]);
			}
		}
		else if(index(B->rows[i]) == -1 && index(A->rows[i]) >= 0){
			while(index(A->rows[i]) != -1){
				changeEntry(sum, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val);
				moveNext(A->rows[i]);
			}
		}
	}	

	return sum;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling sum() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix diff = newMatrix(size(A));
	if(A == B){
		return diff;
	}
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
			if(((Entry)get(A->rows[i]))->col == ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(A->rows[i]))->val + ((Entry)get(B->rows[i]))->val;
				changeEntry(diff, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val - ((Entry)get(B->rows[i]))->val);
				moveNext(A->rows[i]);
				moveNext(B->rows[i]);
			}
			else if(((Entry)get(A->rows[i]))->col < ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(A->rows[i]))->val;
				changeEntry(diff, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val);
				moveNext(A->rows[i]);
			}
			else if(((Entry)get(A->rows[i]))->col > ((Entry)get(B->rows[i]))->col){
				//Entry new = malloc(sizeof(EntryObj));
				//new->col = i;
				//new->val = ((Entry)get(B->rows[i]))->val;
				changeEntry(diff, i, ((Entry)get(B->rows[i]))->col, -1 * ((Entry)get(B->rows[i]))->val);
				moveNext(B->rows[i]);
			}
		}
		if(index(A->rows[i]) == -1 && index(B->rows[i]) >= 0){
			while(index(B->rows[i]) != -1){
				changeEntry(diff, i, ((Entry)get(B->rows[i]))->col, -1 * ((Entry)get(B->rows[i]))->val);
				moveNext(B->rows[i]);
			}
		}
		else if(index(B->rows[i]) == -1 && index(A->rows[i]) >= 0){
			while(index(A->rows[i]) != -1){
				changeEntry(diff, i, ((Entry)get(A->rows[i]))->col, ((Entry)get(A->rows[i]))->val);
				moveNext(A->rows[i]);
			}
		}
	}	

	return diff;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
double dotProd(List A, List B){
	double total = 0;
	moveFront(A);
	moveFront(B);
	while(index(A) != -1 && index(B) != -1){
		if(((Entry)get(A))->col == ((Entry)get(B))->col){
			total += ((Entry)get(A))->val * ((Entry)get(B))->val;
			moveNext(A);
			moveNext(B);
		}
		else if(((Entry)get(A))->col < ((Entry)get(B))->col){
			moveNext(A);
		}
		else if(((Entry)get(A))->col > ((Entry)get(B))->col){
			moveNext(B);
		}
	}
	return total;

}

Matrix product(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling product() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}

	Matrix prod = newMatrix(size(A));
	Matrix BT = transpose(B);
	for(int i = 1; i <= size(A); i++){
		if(length(A->rows[i]) > 0){
			for(int j = 1; j <= size(BT); j++){
				if(length(BT->rows[j]) > 0){
					double x = dotProd(A->rows[i], BT->rows[j]);
					//printf("%.1f\n", x);
					changeEntry(prod, i, j, x);
				}
			}
		}
	}
	//freeMatrix(&BT);
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
	if(NNZ(M) == 0){
		fprintf(out, "\n");
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