//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA5
// List.h
// Implementation file for List.h
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
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
	frontDummy = new Node;
	backDummy = new Node;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;
}

// Copy constructor
List::List(const List& L){
	// make this an empty List
	frontDummy = backDummy = afterCursor = beforeCursor = nullptr;
	num_elements = pos_cursor = 0;

	Node* N = L.frontDummy;
	while(N != nullptr){
		this->Enqueue(N->data);
		N = N->next;
	}
}

// Destructor
List::~List(){
	while(num_elements > 0){
		Dequeue();
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
	if(position <= 0){
		throw std::length_error("List: peekPrev(): out of bounds position");
	}
	return(beforeCursor);
}


//Manipulation procedures----------------------------------------------

void clear(){
	if( length == 0){
		throw std::length_error("List: Clear(): empty List");
	}

	pos_cursor = length;
	while(length != 0){
		this.eraseBefore();
	}

	
}

void moveFront(){
	;;
}

void moveBack(){
	;;
}

ListElement moveNext(){
	;;
}

ListElement movePrev(){
	;
}

void insertAfter(ListElement x){
	;;
}

void insertBefore(ListElement x){
	;;
}

void setAfter(ListElement x){
	;;
}

void setBefore(){
	;;
}

void eraseAfter(){
	;;
}

void eraseBefore(){
	;;
}

//Other Functions---------------------------------------------------------

int findNext(ListElement x){
	;;
}

int findPrev(ListElement x){
	;;
}

void cleanup(){
	;;
}

List concat(const List& L) const{
	;;
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













