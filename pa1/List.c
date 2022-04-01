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

typedef struct NodeObj{
	int data;
	struct NodeObj* Prev;
	struct NodeObj* Next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	int length;
	int index = -1;
	Node Back;
	Node Front;
	Node Current;
}ListObj;

// Constructors and Destructors

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	L->Front = L->Back = NULL;
	L->length = 0;
	return(L);
}

void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		while(!isEmpty(*pL)){
			Dequeue(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//Access Functions

int getFront(List L){
	if(L == NULL){
		printf("List Error: calling getFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}

	if(isEmpty(L)){
		printf("List Error: calling getFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return(L->Front->data);
}

int getLength(List L){
	if(L == NULL){
		printf("List Error: calling getLength() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	return(L->length);
}

bool isEmpty(List L){
	if(L == NULL){
		printf("List error: calling isEmpty() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	return(L->length == 0);
}

//Manipulation procedures

void Enqueue(List L, int data){
	if(L == NULL){
		printf("List Error: calling Enqueue() on NULL List reference");
		exit(EXIT_FAILURE);
	}

	Node N = newNode(data);

	if(isEmpty(L)){
		L->Front = L->Back = N;
	}
	else{
		L->Back->Next = N;
		L->Back = N;
	}
	L->length++;
}

void Dequeue(List L){
	if(L == NULL){
		printf("List Error: calling Dequeue() on NULL List reference");
		exit(EXIT_FAILURE);
	}
	if(isEmpty(L)){
		printf("List Error: calling Dequeue() on empty List");
		exit(EXIT_FAILURE);
	}
	N = L->Frot;
	if(getLength(L) > 1){
		L->Front = L->Front->Next;
	}
	else{
		L->Front = L->Back = NULL;
	}
	Q->length--;
	freeNode(&N);
}

//Other Functions


