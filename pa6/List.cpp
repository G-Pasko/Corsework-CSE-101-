//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA6
// List.cpp
// Implementation file for List.h
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<climits>
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
	//create two new nodes
	frontDummy = new Node(INT_MIN);
	backDummy = new Node(INT_MAX);
	//set prev and next for both dummy's making them the extremes by
	// setting the outsides to null
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
	backDummy->prev = frontDummy;
	//set the cursor to be between the pointers
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	//set int properties to 0
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
	//for each node, append a node w the value
	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		insertBefore(N->data);
		N = N->next;
	}
	//move to front as default
	moveFront();
}

// Destructor
List::~List(){
	//clear to remove al but the dummys...
	clear();
	//then delete the dummys
	delete frontDummy;
	delete backDummy;
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
	moveFront();

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
	//set a pointer to be afterCurser
	Node* N = afterCursor;
	//incriment the pos
	pos_cursor ++;
	//set before to be the old after curser and set after to be afterCursor's next
	beforeCursor = N;
	afterCursor = N->next;
	return N->data;
}

ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): curser at front");
	}
	//set pointer to beforeCurser
	Node* N = beforeCursor;
	//derease pos of curser
	pos_cursor --;
	//set before to be two before
	afterCursor = afterCursor->prev;
	//set after to be the old before
	beforeCursor = N->prev;
	return N->data;
}

void List::insertAfter(ListElement x){
	//create a new node
	Node* N = new Node(x);
	//set the after prev and before next to be new node
	beforeCursor->next = N;
	afterCursor->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	afterCursor = N;
	num_elements++;
}

void List::insertBefore(ListElement x){
	//same as insert after but everything is one node before instead of after
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
	//erase node in question and connect the two halfs of the list
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
	//from the position were at, do moveNext() until we get the same data or reach
	//the end of the list
	while(position() < length()){
		if(moveNext() == x){
			return pos_cursor;
		}
	}
	return -1;
}

int List::findPrev(ListElement x){
	//from the position were at, do movePrev() until we get the same data or reach
	//the front of the list
	while(position() > 0){
		if(movePrev() == x){
			return pos_cursor;
		}
	}
	return -1;
}

void List::cleanup(){
	//Clean up attempt 2
	// set N to front dummy
	Node* N = frontDummy;
	Node* M;
	for(int i = 0; i < length(); i++){
		//set N to the next node and M to the node after that. on first pass,
		// this sets N to the first node and M to the second
		N = N->next;
		M = N->next;

		for(int j = i; j < length(); j++){
			//for every node, check if the data is equal
			if(N->data == M->data){
				//if data is equal...
				//...if M is also before curser, set before Curser to M's prev
				// to avoid losing integrety of original list
				if(M == beforeCursor){
					beforeCursor = M->prev;
				}
				//...if M is also afterCurser, set afterCurser to M's next
				// to avoid losing integrety of original list
				if(M == afterCursor){
					afterCursor = M->next;
				}
				//..if we remove a node that lies before the original curser pos,
				// lower pos_cursor to make up for change in length
				if(j < position()){
					pos_cursor--;
				}
				//set M's surrounding nodes to be connected to eachother
				M->next->prev = M->prev;
				M->prev->next = M->next;
				//to avoid seg fault, set a temp to M and delete the temp
				Node* temp = M;
				delete(temp);
				//decrease num elements
				num_elements--;
			}
			//set M to be be M->next
			M=M->next;
		}
	}

//IGNORE
	//Clean up attempt 1
	/*
	Node* N = backDummy;
	Node* M;
	for(int i = 0; i < length(); i++){
		N = N->prev;
		M = N->prev;
		for(int j = i; j < length(); j++){
			if(M->data == N->data){
				N->prev->next = N->next;
				N->next->prev = N->prev;
				num_elements--;
				if(pos_cursor >= j){
					pos_cursor--;
				}
				delete N;
			}
			else{
				M = M->prev;
			}
		}
	}*/
}

List List::concat(const List& L) const{
	//create new list
	List newList;
	//set two nodes to be the front of each list
	Node* N = frontDummy->next;
	Node* M = L.frontDummy->next;
	//add all elements of list 1 to the new list
	while(N != backDummy){
		newList.insertBefore(N->data);
		N = N->next;
	}
	//add all elements of list 2 to the new list
	while(M != L.backDummy){
		newList.insertBefore(M->data);
		M = M->next;
	}
	//move front on the new list
	newList.pos_cursor = 0;
	newList.beforeCursor = newList.frontDummy;
	newList.afterCursor = newList.frontDummy->next;
	//return new list
	return newList;
}

std::string List::to_string() const{
	Node* N = frontDummy->next;
	
	if(N->data == backDummy->data){
		std::string s = "0";
		return s;
	}
	std::string s = std::to_string(N->data);
	for(N=N->next; N!=backDummy; N=N->next){
      s += std::to_string(N->data);
   }
   
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

