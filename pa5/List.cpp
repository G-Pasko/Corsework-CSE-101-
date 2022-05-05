//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA5
// List.h
// Implementation file for List.h
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

#define DUMMY -69

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
	frontDummy = new Node(DUMMY);
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy = new Node(DUMMY);
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
	frontDummy = new Node(DUMMY);
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy = new Node(DUMMY);
	backDummy->next = nullptr;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;

	Node* N = L.frontDummy->next;
	while(N->next != L.backDummy){
		this->insertAfter(N->data);
		pos_cursor ++;
		N = N->next;
	}
}

// Destructor
List::~List(){
	pos_cursor = length;
	while(num_elements > 0){
		eraseBefore();
	}
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
	if(num_elements == 0){
		throw std::length_error("List: getFront(): empty List");
	}
	return(frontDummy->data);
}


//getFront()
//Returns the value at the front of List
//pre: !isEmpty()
ListElement List::back() const{
	if(num_elements == 0){
		throw std::length_error("List: getFront(): empty List");
	}
	return(backDummy->data);
}


// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int position() const{
	return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement peekNext() const{
	if(position() >= length()){
		throw std::length_error("List: peekNext(): out of bounds position");
	}
	return(afterCursor);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement peekPrev() const{
	if(position() <= 0){
		throw std::length_error("List: peekPrev(): out of bounds position");
	}
	return(beforeCursor);
}


//Manipulation procedures----------------------------------------------

void clear(){
	if(length() == 0){
		throw std::length_error("List: Clear(): empty List");
	}

	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	while(length() != 0){
		eraseBefore();
	}

	
}

void moveFront(){
	pos_cursor = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
}

void moveBack(){
	pos_cursor = length();
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
}

ListElement moveNext(){
	if(this == nullptr){
		throw std::length_error("List: movePrev(): NULL list");
	}
	if(pos_cursor == length){
		throw std::length_error("List: movePrev(): curser at back");
	}
	if(length == 0){
		throw std::length_error("List: movePrev(): called on empty list");
	}
	Node* N = afterCursor;
	pos_cursor ++;
	beforeCursor = afterCursor;
	afterCursor = N->next;
	return N;
}

ListElement movePrev(){
	if(this == nullptr){
		throw std::length_error("List: movePrev(): NULL list");
	}
	if(pos_cursor == 0){
		throw std::length_error("List: movePrev(): curser at front");
	}
	if(num_elements == 0){
		throw std::length_error("List: movePrev(): called on empty list");
	}
	Node* N = beforeCursor;
	pos_cursor --;
	afterCursor = afterCursor->prev;
	beforeCursor = N->prev;
	return N;
}

void insertAfter(ListElement x){
	Node N = new Node(x);
	beforeCursor->next = N;
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor = N;
	num_elements++;
}

void insertBefore(ListElement x){
	Node N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
}

void setAfter(ListElement x){
	afterCursor->data = x;
}

void setBefore(ListElement x){
	beforeCursor->data = x;
}

void eraseAfter(){
	if(position() >= length()){
		throw std::length_error("List: eraseBefore(): called on out of bounds position\n");
	}
	if(position() == 0){
		
	}
	Node* newNext = afterCursor->next;
	newNext->next = afterCursor->next->next;
	delete(afterCursor);
	beforeCursor->next = newNext;
	newNext->prev = beforeCursor;
	num_elements --;
}

void eraseBefore(){
	if(position() <= 0){
		throw std::length_error("List: eraseBefore(): called on out of bounds position\n");
	}
	Node* newPrev = beforeCursor->prev;
	newPrev->next =
	delete(beforeCursor);
	afterCursor->prev = newPrev;
	newPrev->next = afterCursor;
	num_elements--;
}

//Other Functions---------------------------------------------------------

int findNext(ListElement x){
	while(position() != length()){
		if(afterCursor->data != x){
			pos_cursor++;
		}
		else{
			return pos_cursor;
		}
	}
	return -1;
}

int findPrev(ListElement x){
	while(position() != 0){
		if(beforeCursor->data != x){
			pos_cursor--;
		}
		else{
			return pos_cursor;
		}
	}
	return -1;
}

void cleanup(){
	;;
}

List concat(const List& L) const{
	List L;
	Node* N = this->frontDummy;
	Node* M = L->frontDummy;
}

std::string to_string() const{
	;;
}

bool equals(const List& R) const{
	;;
}

//Overriden Operations---------------------------------------------------

friend std::ostream& operator<<( std::ostream& stream, const List& L ){
	;;
}

friend bool operator==( const List& A, const List& B){
	;;
}

List& operator=( cosnt List& L){
	;
}













