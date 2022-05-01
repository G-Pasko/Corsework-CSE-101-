/********************************************************************************* 
* Brandon Lau, blau7
* 2022 Spring CSE101 PA4
* List.c 
* Implementation File for List ADT 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

// structs --------------------------------------------------------------------
typedef struct NodeObj* Node;

typedef struct NodeObj {
    ListElement val;
    Node previous;
    Node next;
} NodeObj;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){ 
    List newList = calloc(1, sizeof(ListObj));
    newList->front = NULL;
    newList->back = NULL;
    newList->cursor = NULL;
    newList->length = 0;
    newList->index = -1;
    return newList;
}

void freeList(List* pL){
    if (*pL == NULL){
        printf("freeList() called on NULL list\n");
        exit(EXIT_FAILURE);
    }
    clear(*pL);
    free(*pL);
    *pL = NULL;
}

// Access functions -----------------------------------------------------------
int length(List L){
    if (L == NULL){
        printf("length() called on NULL list\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
} 

int index(List L){
    if (L == NULL){
        printf("index() called on NULL list\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL){
        return -1;
    }
    return L->index;
}

ListElement front(List L){
    if( L == NULL ){
        printf("front() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("front() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->val);
} 

ListElement back(List L){
    if( L == NULL ){
        printf("back() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("back() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->val);
}

ListElement get(List L){
    if( L == NULL ){
        printf("get() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        printf("get() called on index < 0\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("get() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->val);
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if (L == NULL){
        printf("clear() called on NULL list\n");
        exit(EXIT_FAILURE);
    }
    // delete the front of the list until the list is empty
    while (length(L) != 0){
        deleteFront(L);
    }
}

void set(List L, ListElement x){
    if( L == NULL ){
        printf("set() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0){
        printf("set() called on index < 0\n");
    }
    if(length(L) <= 0){
        printf("set() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->val = x;
} 

void moveFront(List L){
    if( L == NULL ){
        printf("moveFront() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0){
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L){
    if( L == NULL ){
        printf("moveBack() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L){
    if( L == NULL ){
        printf("movePrev() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    //set cursor to the element before it if it isnt the front
    if (L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->previous;
        L->index --;
    }
    // set cursor to null if it is at the front already
    else if (L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    } 
}

void moveNext(List L){
    if( L == NULL ){
        printf("moveNext() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    // if cursor isnt at the back, move it next
    if (L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
        L->index ++;
    }
    // if the cursor is already at the back, set it to null
    else if (L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    } 
}

void prepend(List L, ListElement x){
    if( L == NULL ){
        printf("prepend() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = calloc(1, sizeof(NodeObj));
    newNode->val = x;
    newNode->previous = NULL;
    newNode->next = NULL;
    // set front and back to the new node if the list is empty
    if (length(L) == 0){
        L->front = L->back = newNode;
        L->length ++;
    }
    // add it before the front if it is not
    else{
        L->front->previous = newNode;
        newNode->next = L->front;
        L->front = newNode;
        L->length ++;
        if (L->index >= 0){
            L->index ++;
        }
    }
}

void append(List L, ListElement x){
    if( L == NULL ){
        printf("append() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = calloc(1, sizeof(NodeObj));
    newNode->val = x;
    newNode->previous = NULL;
    newNode->next = NULL;
    // set front and back to the new node if the list is empty
    if (length(L) == 0){
        L->front = L->back = newNode;
        L->length ++;
    }
    // add it after the back if it is not
    else{
        L->back->next = newNode;
        newNode->previous = L->back;
        L->back = newNode;
        L->length ++;
    }
}

void insertBefore(List L, ListElement x){
    if( L == NULL ){
        printf("insertBefore() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("insertBefore() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("insertBefore() called on missing cursor\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = calloc(1, sizeof(NodeObj));
    newNode->val = x;
    newNode->previous = NULL;
    newNode->next = NULL;
    // if the cursor is at the front
    if (L->cursor == L->front){
        newNode->next = L->front;
        L->front->previous = newNode;
        L->front = newNode;
    }
    // if cursor is between 2 nodes or at the back
    else{
        L->cursor->previous->next = newNode;
        newNode->previous = L->cursor->previous;
        L->cursor->previous = newNode;
        newNode->next = L->cursor;
    }
    L->index ++;
    L->length ++;
} 

void insertAfter(List L, ListElement x){
    if( L == NULL ){
        printf("insertAfter() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("insertAFter() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("insertAFter() called on missing cursor\n");
        exit(EXIT_FAILURE);
    }
    Node newNode = calloc(1, sizeof(NodeObj));
    newNode->val = x;
    newNode->previous = NULL;
    newNode->next = NULL;
    // if the cursor is at the back
    if (L->cursor == L->back){
        newNode->previous = L->back;
        L->back->next = newNode;
        L->back = newNode;
    }
    // if cursor is between 2 nodes or at the front
    else{
        L->cursor->next->previous = newNode;
        newNode->next = L->cursor->next;
        L->cursor->next = newNode;
        newNode->previous = L->cursor;
    }
    L->length ++;
}

void deleteFront(List L){
    if( L == NULL ){
        printf("deleteFront() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("deleteFront() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node delete = L->front;
    //set cursor to null if theres only one thing to delete
    if (length(L) == 1){
        L->front = L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        //check if the cursor is at the front, set cursor to null if it is
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
        L->front->next->previous = NULL;
        L->front = L->front->next;
        L->index --;
    }
    free(delete);
    delete = NULL;
    L->length --;
}

void deleteBack(List L){
    if( L == NULL ){
        printf("deleteBack() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("deleteBack() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    Node delete = L->back;
    //set cursor to null if theres only one thing to delete
    if (length(L) == 1){
        L->front = L->back = NULL;
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        //check if the cursor is at the back, set cursor to null if it is
        if (L->cursor == L->back){
            L->cursor = NULL;
            L->index = -1;
        }
        L->back->previous->next = NULL;
        L->back = L->back->previous;
    }
    free(delete);
    delete = NULL;
    L->length --;
}

void delete(List L){
    if( L == NULL ){
        printf("delete() called on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("delete() called on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0){
        printf("delete() called on missing cursor\n");
        exit(EXIT_FAILURE);
    }
    //call deletefront instead if we want to delete front
    if (L->cursor == L->front){
        deleteFront(L);
    }
    //call deleteback instead if we want to delete back
    else if (L->cursor == L->back){
        deleteBack(L);
    }
    else{
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        free(L->cursor);
        L->cursor = NULL;
        L->index = -1;
        L->length --;
    }
}