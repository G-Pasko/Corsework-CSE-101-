//-----------------------------------------------------------------------------
// Granger Pasko, gpasko
// Spring CSE101 PA5
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include"List.h"

using namespace std;

void shuffle(List& D){
	List A;
	List B;
	D.moveFront();
	while(D.position() != D.length() / 2){
		A.insertBefore(D.moveNext());
	}
	while(D.position() != D.length()){
		B.insertBefore(D.moveNext());
	}
	D.clear();
	A.moveFront();
	B.moveFront();
	if(A.length() == B.length()){
		while(A.position() != A.length()){
			D.insertBefore(B.moveNext());
			D.insertBefore(A.moveNext());
		}
	}
	else{
		D.insertBefore(B.moveNext());
		while(A.position() != A.length()){
			D.insertBefore(A.moveNext());
			D.insertBefore(B.moveNext());
		}
	}

}


int main(int argc, char* argv[]){
	if(argc != 2){
		cout << "Invalid number of arguments" << endl;
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[1]);
	if(size <= 0){
		cout << "Invalid size of list" << endl;
	}
	List L;
	int count = 0;
	printf("deck size\t\tshuffle count\n");
	printf("------------------------------\n");
	for(int i= 0; i < size; i++){
		//printf("deck size\t\tshuffle count\n");
		L.insertBefore(i);
		List C = L;
		shuffle(L);
		count++;
		while(!(C.equals(L))){
			shuffle(L);
			count++;
		}
		printf("%d\t\t\t%d\n", i + 1, count);
		count = 0;
	}

	//add 0 to a new list
	//run shuffle until the list is the same
	//add next element 
	//re shuffle


	return 0;
}

