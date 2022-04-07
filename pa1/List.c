/********************************************************************************* 
* Granger Pasko, gpasko
* 2022 Spring CSE101 PA1 
* List.c 
* Creating list ADTS, Constructors, and Destructors
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
//Structs
extern char* strdup(const char*);


typedef struct NodeObj{
	ListElement data;
	struct NodeObj* prev;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	int length;
	int index;				//position of curser
	Node back;
	Node front;
	Node curser;
}ListObj;

// Constructors and Destructors

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
List newList(void){
	List L = malloc(sizeof(ListObj));
	L->back = L->front = L->curser = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL){
	if(*pL == NULL){
		printf("List Error: calling freeList() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	clear(*pL);
	//printf("Clear success\n");
	free(*pL);
	//printf("Free success\n");
	*pL = NULL;
}


//Access Functions
int length(List L){
	if(L == NULL){
		printf("List Error: calling getLength() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	return(L->length);
}

int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L->index);
}

int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(L->length == 0){
		printf("List Error: calling front() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

int back(List L){
	if(L == NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(L->length == 0){
		printf("List Error: calling back() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}

int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!(length(L) > 0)){
		printf("List Error: calling get() on an empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: calling get() on a list with an undefined index reference\n");
		exit(EXIT_FAILURE);
	}
	//printf("%d\n", L->front->data);
	//printf("%d\n", L->curser->data);
	return(L->curser->data);
}

bool equals(List A, List B){
	bool eq = 0;

	Node N = NULL;
	Node M = NULL;

	if(A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	while(eq && M != NULL){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}



//Manipulation procedures

void clear(List L){
	if(L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while(length(L) != 0){
		deleteFront(L);
	}
}

void set(List L, int x){
	if(L == NULL){
		printf("List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!(L->length > 0)) {
		printf("List Error: calling set() on empty List reference\n");
		exit(EXIT_FAILURE);
	}
	if(!(index(L) >=0)){
		printf("List Error: calling set() with invalid  List reference\n");
		exit(EXIT_FAILURE);
	}
	L->curser->data = x;
}

void moveFront(List L){
	if(L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		L->index = 0;
		L->curser = L->front;
	}
}

void moveBack(List L){
	if(L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		L->index = L->length - 1;
		L->curser = L->back;
	}
}

void movePrev(List L){
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == 0){
		L->curser = NULL;
		L->index = -1;
	}
	else if(length(L)> 0){
		L->index--;
		L->curser = L->curser->prev;
	}
}

void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == length(L) - 1){
		L->curser = NULL;
		L->index = -1;
	}
	else if(length(L) > 0){
		L->index++;
		L->curser = L->curser->next;
	}
}

void prepend(List L, int x){
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	Node new = malloc(sizeof(NodeObj));
	new->data = x;
	if(length(L) == 0){
		L->front = L->back = new;
		new->prev = new->next = NULL;

	}
	else{
		new->next = L->front;
		L->front->prev = new;
		new->prev = NULL;
		L->front = new;
	}
	if(index(L) != -1){
		L->index ++;
	}
	L->length++;
}


void append(List L, int x){
	if(L == NULL){
		printf("List Error: calling Enqueue() on NULL List reference");
		exit(EXIT_FAILURE);
	}

	Node new = malloc(sizeof(NodeObj));
	new->data = x;

	if(length(L) == 0){
		L->front = L->back = new;
		new->prev = NULL;
		new->next = NULL;
	}
	else{
		new->prev = L->back;
		L->back->next = new;
		L->back = new;
	}
	L->length++;
}

void insertBefore(List L, int x){
	if(L == NULL){
		printf("List Error: calling Enqueue() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	if(L->length == 0){
		printf("List Error: calling insertAfter() on empty List");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: calling insertAfter() on undefined index");
		exit(EXIT_FAILURE);
	}
	if(L->curser == L->front){
		Node new = malloc(sizeof(NodeObj));
		new->data = x;
		L->curser->prev = new;
		new->next = L->front;
		L->front = new;
		new->prev = NULL;
	}

	else if(length(L) > 0 && index(L) > 0){
		Node new = malloc(sizeof(NodeObj));
		new->data = x;
		new->prev = L->curser->prev;
		L->curser->prev->next = new;
		L->curser->prev = new;
		new->next = L->curser;

	}
	L->index ++;
	L->length ++;
}

void insertAfter(List L, int x){
	if(L == NULL){
		printf("List Error: calling Enqueue() on NULL List reference");
		exit(EXIT_FAILURE);
	}

	if(L->length == 0){
		printf("List Error: calling insertAfter() on empty List");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: calling insertAfter() on undefined index");
		exit(EXIT_FAILURE);
	}

	if(length(L) > 0 && L->curser == L->back){
		Node new = malloc(sizeof(NodeObj));
		new->data = x;
		L->back->next = new;
		new->prev = L->back;
		L->back = new;
		new->next = NULL;
	}
	else{
		Node new = malloc(sizeof(NodeObj));
		new->data = x;
		new->next = L->curser->next;
		L->curser->next->prev = new;
		L->curser->next = new;
		new->prev = L->curser;
	}
	//L->curser->next->prev = new;
	//L->curser->next = new;
	//L->index --;
	L->length++;

}

void deleteFront(List L){
	if(L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	if(L->length == 0){
		printf("List Error: calling deleteFront() on empty List");
		exit(EXIT_FAILURE);
	}
	Node del = L->front;

	if(length(L) > 1){
		if(L->curser == L->front){
			L->curser = NULL;
			L->index = -1;
		}
		else{
			L->idex --;
		}
		L->front = L->front->next;
		L->front->prev = NULL;
		//L->index --;

	}
	else if(length(L) == 1){
		L->front = L->back = L->curser = NULL;
		L->index = -1;
	}
	L->length--;
	free(del);
	del = NULL;
}

void deleteBack(List L){
	if(L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	if(L->length == 0){
		printf("List Error: calling deleteBack() on empty List");
		exit(EXIT_FAILURE);
	}
	Node del = L->back;
	if(length(L) > 1){
		if(L->curser == L->back){
			L->curser = NULL;
			L->index = -1;
		}
		L->back = L->back->prev;
		L->back->next = NULL;
	}
	else{
		L->front = L->back = L->curser = NULL;
		L->index = -1;
	}

	L->length--;
	free(del);
	del = NULL;
}


void delete(List L){
	if(L == NULL){
		printf("List Error: calling delete() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	if(L->length == 0){
		printf("List Error: calling delete() on empty List");
		exit(EXIT_FAILURE);
	}
	if(L->curser == L->front){
		Node temp = L->front->next;
		free(L->front);
		L->front = temp;
		L->front->prev = NULL;
	}
	else if(L->curser ==  L->back){
		Node temp = L->back->prev;
		free(L->back);
		L->back = temp;
		L->back->next = NULL;
	}
	else{
		Node left = L->curser->prev;
		Node right = L->curser->next;

		free(L->curser);
		left->next = right;
		right->prev = left;
	}
	L->length --;
	L->curser = NULL;
	L->index = -1;

}


//Other Functions

void printList(FILE* out, List L){
	if(L == NULL){
		printf("List Error: calling printList() on NULL List reference");
		exit(EXIT_FAILURE);
	}

	Node N = NULL;
	for(N = L->front; N != NULL; N = N->next){
		fprintf(out, "%d ", N->data);
	}
}

List copyList(List L){
	List copy = newList();

	for(moveFront(L); index(L)>=0; moveNext(L)){
		append(copy, get(L));
	}
	return(copy);
}
