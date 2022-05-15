//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA6
// BigInteger.cpp
// This file defines all the functions declared in BigInteger.h
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<cstdio>
#include<stdexcept>
#include<cmath>
#include<cctype>
#include"List.h"
#include"BigInteger.h"

const int power = 1;
const ListElement base = 10;

//Use stol

// Exported type  -------------------------------------------------------------

   // BigInteger Fields 
   //int signum;    // +1 (positive), -1 (negative), 0 (zero)
   //List digits;   // List of digits in this BigInteger


   // Class Constructors & Destructors ----------------------------------------

   // BigInteger()
   // Constructor that creates a new BigInteger in the zero state: 
   // signum=0, digits=().
	BigInteger::BigInteger(){
		signum = 0;
	}

   // BigInteger()
   // Constructor that creates a new BigInteger from the string s.
   // Pre: s is a non-empty string consisting of (at least one) base 10 digit
   // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
	BigInteger::BigInteger(std::string s){
		if(s.empty()){
			throw std::invalid_argument("BigInteger: Constructor: empty string");
		}
		int j = 0;
		int i;
		if(!isalnum(s[0])){
			if(strcmp(&(s[0]), "-") == 0){
				j = 1;
				signum = -1;
			}
		}
		else{
			signum = 1;
		}
		
		for(i = j; i < s.length(); i++){
			if(!isalnum(s[i])){
				throw std::invalid_argument("BigInteger: Constructor: empty string");
			}
		}
		printf("%lu\n", s.length());
		for(i = s.length(); i >= power; i = i - power){
			digits.insertAfter(stol(s.substr(i - power, power)));
		}
		if(i > 0){
			digits.insertAfter(stol(s.substr(0, i)));
		}

	}

   // BigInteger()
   // Constructor that creates a copy of N.
	
	BigInteger::BigInteger(const BigInteger& N){
		;;
	}

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();


   // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
	int BigInteger::sign() const{
		return signum;
	}

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
	int BigInteger::compare(const BigInteger& N) const{
		return 0;
	}


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
	void BigInteger::makeZero(){
		signum = 0;
		digits.cleanup();
	}

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
	void BigInteger::negate(){
		return;
	}


   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N
	BigInteger BigInteger::add(const BigInteger& N) const{
		return N;
	}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
	BigInteger BigInteger::sub(const BigInteger& N) const{
		return N;
	}

   // mult()
   // Returns a BigInteger representing the product of this and N. 
	BigInteger BigInteger::mult(const BigInteger& N) const{
		return N;
	}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
	std::string BigInteger::to_string(){
		return digits.to_string();
	}


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
   std::ostream& operator<<( std::ostream& stream, BigInteger N );

   // operator==()
   // Returns true if and only if A equals B. 
   bool operator==( const BigInteger& A, const BigInteger& B );

   // operator<()
   // Returns true if and only if A is less than B. 
   bool operator<( const BigInteger& A, const BigInteger& B );

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
   bool operator<=( const BigInteger& A, const BigInteger& B );

   // operator>()
   // Returns true if and only if A is greater than B. 
   bool operator>( const BigInteger& A, const BigInteger& B );

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
   bool operator>=( const BigInteger& A, const BigInteger& B );

   // operator+()
   // Returns the sum A+B. 
   BigInteger operator+( const BigInteger& A, const BigInteger& B );

   // operator+=()
   // Overwrites A with the sum A+B. 
   BigInteger operator+=( BigInteger& A, const BigInteger& B );

   // operator-()
   // Returns the difference A-B. 
   BigInteger operator-( const BigInteger& A, const BigInteger& B );

   // operator-=()
   // Overwrites A with the difference A-B. 
   BigInteger operator-=( BigInteger& A, const BigInteger& B );

   // operator*()
   // Returns the product A*B. 
   BigInteger operator*( const BigInteger& A, const BigInteger& B );

   // operator*=()
   // Overwrites A with the product A*B. 
   BigInteger operator*=( BigInteger& A, const BigInteger& B );
   
