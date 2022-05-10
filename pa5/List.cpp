//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA5
// List.cpp
// Implementation file for List.h
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include <climits>
#include"List.h"

//private Constructor

//Node constructor
List::Node::Node(ListElement x){
	data = x;
	prev = nullptr;
	next = nullptr;
}


//Class Constructors & Destructors-------------------------------------

//Creates a new list in the empty state
List::List(){
	frontDummy = new Node(INT_MIN);
	backDummy = new Node(INT_MAX);
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;
}

// Copy constructor
List::List(const List& L){
	// make this an empty List
	frontDummy = new Node(INT_MIN);
	backDummy = new Node(INT_MAX);
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;

	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		insertBefore(N->data);
		N = N->next;
	}
	moveFront();
}

// Destructor
List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
	//pos_cursor = 0;
	//num_elements = 0;
	//beforeCursor = nullptr;
	//afterCursor = nullptr;
}




// Access functions---------------------------------------------------------

// getLength()
// Returns length of List
int List::length() const{
	return(num_elements);
}

//getFront()
//Returns the value at the front of List
//pre: !isEmpty()
ListElement List::front() const{
	if(length() <= 0){
		throw std::length_error("List: front(): empty List");
	}
	return(frontDummy->next->data);
}


//getFront()
//Returns the value at the front of List
//pre: !isEmpty()
ListElement List::back() const{
	if(length() <= 0){
		throw std::length_error("List: back(): empty List");
	}
	return(backDummy->prev->data);
}


// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if(position() >= length()){
		throw std::range_error("List: peekNext(): out of bounds position");
	}
	return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(position() <= 0){
		throw std::range_error("List: peekPrev(): out of bounds position");
	}
	return(beforeCursor->data);
}


//Manipulation procedures----------------------------------------------

void List::clear(){
	moveFront();
	while(length() != 0){
		eraseAfter();
	}

}

void List::moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

void List::moveBack(){
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

ListElement List::moveNext(){
	if(pos_cursor == length()){
		throw std::range_error("List: moveNext(): curser at back");
	}
	Node* N = afterCursor;
	pos_cursor ++;
	beforeCursor = afterCursor;
	afterCursor = N->next;
	return N->data;
}

ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): curser at front");
	}
	Node* N = beforeCursor;
	pos_cursor --;
	afterCursor = afterCursor->prev;
	beforeCursor = N->prev;
	return N->data;
}

void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next = N;
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor = N;
	num_elements++;
}

void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	num_elements++;
	pos_cursor++;
	beforeCursor = N;

}

void List::setAfter(ListElement x){
	if(position() >= length()){
		throw std::range_error("List: setAfter(): called on out of bounds position");
	}
	afterCursor->data = x;
}

void List::setBefore(ListElement x){
	if(position() <= 0){
		throw std::range_error("List: setBefore(): called on out of bounds position");
	}
	beforeCursor->data = x;
}

void List::eraseAfter(){
	if(position() >= length()){
		throw std::range_error("List: eraseAfter(): called on out of bounds position");
	}
	Node* newNext = afterCursor->next;
	newNext->prev = beforeCursor;
	delete(afterCursor);
	afterCursor = newNext;
	beforeCursor->next = newNext;
	newNext->prev = beforeCursor;
	num_elements --;
}

void List::eraseBefore(){
	if(position() <= 0){
		throw std::range_error("List: eraseBefore(): called on out of bounds position");
	}
	Node* newPrev = beforeCursor->prev;
	newPrev->next = afterCursor;
	delete(beforeCursor);
	beforeCursor = newPrev;
	afterCursor->prev = newPrev;
	newPrev->next = afterCursor;
	pos_cursor --;
	num_elements--;
}

//Other Functions---------------------------------------------------------

int List::findNext(ListElement x){
	if(afterCursor->data == x){
		return pos_cursor;
	}
	while(position() < length()){
		if(moveNext() == x){
			return pos_cursor;
		}
	}
	return -1;
}

int List::findPrev(ListElement x){
	if(beforeCursor->data == x){
		return pos_cursor;
	}
	while(position() > 0){
		if(movePrev() == x){
			return pos_cursor;
		}
	}
	return -1;
}

void List::cleanup(){
	Node* N = backDummy;
	Node* M;
	Node* T1 = afterCursor;
	Node* T2 = beforeCursor;
	int temp_pos = pos_cursor;

	for(int i = 0; i < length(); i++){
		N = N->prev;
		M = N->prev;
		for(int j = i; j < length(); j++){
			if(M->data == N->data){
				N->prev->next = N->next;
				N->next->prev = N->prev;
				num_elements--;
				pos_cursor = num_elements;
				delete N;
			}
			else{
				M = M->prev;
			}
		}
	}
	afterCursor = T1;
	beforeCursor = T2;
	pos_cursor = temp_pos;
}

List List::concat(const List& L) const{
	List newList;
	Node* N = frontDummy->next;
	Node* M = L.frontDummy->next;
	while(N != backDummy){
		newList.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		newList.insertBefore(M->data);
		M = M->next;
	}
	newList.pos_cursor = 0;
	newList.beforeCursor = newList.frontDummy;
	newList.afterCursor = newList.frontDummy->next;
	return newList;
}

std::string List::to_string() const{
	Node* N = frontDummy->next;
	std::string s = "(" + std::to_string(N->data);
	for(N=N->next; N!=backDummy; N=N->next){
      s += ", " + std::to_string(N->data);
   }
   s += ")";
   
   return s;
}

bool List::equals(const List& R) const{
	Node* N = frontDummy->next;
	Node* M = R.frontDummy->next;
	bool eq = (num_elements == R.num_elements);
	while(eq && N != backDummy){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
	
}

//Overriden Operations---------------------------------------------------

std::ostream& operator<<( std::ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B){
	return A.List::equals(B);
}

List& List::operator=( const List& L){

	if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;

      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(pos_cursor, temp.pos_cursor);

   }

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}

