//-----------------------------------------------------------------------------
// Granger Pasko, gpasko
// Spring CSE101 PA5
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;


int main(void){
	List L;
	L.insertAfter(5);
	L.insertAfter(4);
	L.insertAfter(3);
	L.moveFront();
	std::cout<<"\nL.moveNext() = " <<L.moveNext() <<std::endl;
	std::cout<<"\nL.moveNext() = " <<L.moveNext() <<std::endl;	
	std::cout<<"\nL.moveNext() = " <<L.moveNext() <<std::endl;
	std::cout<<"\nA.movePrev() = " <<L.movePrev() <<std::endl;	
	L.moveBack();
	std::cout<<"\nA.movePrev() = " <<L.movePrev() <<std::endl;	
	std::cout<<"\nA.movePrev() = " <<L.movePrev() <<std::endl;	
	std::cout<<"\nA.movePrev() = " <<L.movePrev() <<std::endl;
	L.insertBefore(2);
	std::cout<<"\nA.movePrev() = " <<L.movePrev() <<std::endl;	
	L.setAfter(1);
	std::cout<<"\nL.moveNext() = " <<L.moveNext() <<std::endl;
	
	L.moveBack();
	L.setBefore(29);
	std::cout<<"\nL.movePrev() = " <<L.movePrev() <<std::endl;

	exit(EXIT_SUCCESS);
}

/*
int length() const;

   ListElement front() const;

   ListElement back() const;

   int position() const;

   ListElement peekNext() const;

   ListElement peekPrev() const;


   // Manipulation procedures -------------------------------------------------

   void clear();

   void moveFront();

   void moveBack();

   ListElement moveNext();

   ListElement movePrev();

   void insertAfter(ListElement x);

   void insertBefore(ListElement x);

   void setAfter(ListElement x);

   void setBefore(ListElement x);

   void eraseAfter();
   void eraseBefore();


   // Other Functions ---------------------------------------------------------
   int findNext(ListElement x);

   int findPrev(ListElement x);

   void cleanup();

   List concat(const List& L) const;
   
   std::string to_string() const;

   bool equals(const List& R) const;
*/
