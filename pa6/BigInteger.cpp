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
const ListElement base = pow(10, power);

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
		List digits;
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
			if(int(s[0])  == 45){			//45 is ascii value of "-"
				j = 1;
				signum = -1;
			}
			else{
				signum = 1;
			}
		}
		else{
			signum = 1;
		}
		
		for(i = j; i < s.length(); i++){
			if(!isalnum(s[i])){
				throw std::invalid_argument("BigInteger: Constructor: non_numeric string");
			}
		}
		for(i = s.length(); i >= power + j; i = i - power){
			digits.insertAfter(stol(s.substr(i - power, power)));
		}
		if(i > j){
			digits.insertAfter(stol(s.substr(j, i-power)));
		}

	}

   // BigInteger()
   // Constructor that creates a copy of N.
	
	BigInteger::BigInteger(const BigInteger& N){
		signum = N.signum;
		digits = N.digits;
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
		if(signum != N.signum){
			if(signum < N.signum){
				return -1;
			}
			else{
				return 1;
			}
		}
		else{
			if(digits.length() > N.digits.length()){
				return 1;
			}
			else if(digits.length() < N.digits.length()){
				return -1;
			}
			else{
				return 0;
			}
		}

	}


   // Manipulation procedures -------------------------------------------------

	void negateList(List& L){
		L.moveFront();
		while(L.position() != L.length()){
			long prev_val = L.moveNext();
			L.setBefore(-1 * prev_val);
		}
	}


	void sumList(List& L, List A, List B, int sign){
		List M;
		A.moveBack();
		B.moveBack();
			
		printf("%ld\n", A.back());
		printf("%ld\n", B.back());


		if(sign < 0){
			negateList(B);
		}
		int large = 0;
		int j = 0;
		
		if(A.length() < B.length()){
			large = 1;
		}
		else if(A.length() > B.length()){
			large = 2;
		}
		
		for(int i = 0; i < fmin(A.length(), B.length()); i++){
			M.insertAfter(A.movePrev() + B.movePrev());
			j = i;
		}
		
		if(large == 1){							//if original number is larger
			for(int i = j + 1; i < B.length(); i++){
				M.insertAfter(B.movePrev());
			}
		}
		else if(large == 2){					//if number being added is larger
			for(int i = j + 1; i < A.length(); i++){
				M.insertAfter(A.movePrev());
			}
		}
		L = M;
	}

	
	//Normalize
	int normalizeList(List& L){
		List M; 
		L.moveBack();
		for(int i = 0; i < L.length() -1; i++){
			if(L.peekPrev() >= base){
				long prev_val = L.movePrev(); 
				M.insertAfter(prev_val - base);
				L.setBefore(L.peekPrev() + 1);
			}
			else if(L.peekPrev() < 0){
				long prev_val = L.movePrev(); 
				M.insertAfter(prev_val + base);
				L.setBefore(L.peekPrev() - 1);
			}
			else{
				M.insertAfter(L.movePrev());
			}
		}
		L = M;
		if(L.front() < 0){
			return -1;
		}
		if(L.front() > 0){
			return 1;
		}
		return 0;
	}

	void shiftList(){
		return;
	}

	void scalarMultList(List& L, ListElement m){
		return;
	}

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
		if(signum == 0){
			return;
		}
		signum *= -1;
	}


   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N
	BigInteger BigInteger::add(const BigInteger& N) const{
		BigInteger sum;

		List A = digits;
		List B = N.digits;
		sumList(sum.digits, A, B, 1);
		/*
		A.moveBack();
		B.moveBack();
		
		int large = 0;
		int j = 0;
		
		if(A.length() < B.length()){
			large = 1;
		}
		else if(A.length() > B.length()){
			large = 2;
		}
		
		for(int i = 0; i < fmin(A.length(), B.length()); i++){
			sum.digits.insertAfter(A.movePrev() + B.movePrev());
			j = i;
		}
		
		if(large == 1){							//if original number is larger
			for(int i = j + 1; i < B.length(); i++){
				sum.digits.insertAfter(B.movePrev());
			}
		}
		else if(large == 2){					//if number being added is larger
			for(int i = j + 1; i < A.length(); i++){
				sum.digits.insertAfter(A.movePrev());
			}
		}
		*/
		normalizeList(sum.digits);
		return sum;
	}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
	BigInteger BigInteger::sub(const BigInteger& N) const{
		BigInteger diff;

		List A = digits;
		List B = N.digits;
		sumList(diff.digits, A, B, -1);
		/*

		A.moveBack();
		B.moveBack();
		int j = 0;
		int large = 0;
		
		if(A.length() < B.length()){
			large = 1;
		}
		else if(A.length() > B.length()){
			large = 2;
		}
		
		for(int i = 0; i < fmin(A.length(), B.length()); i++){
			diff.digits.insertAfter(A.movePrev() - B.movePrev());
			j = i;

		}
		
		if(large == 1){							//if original number is larger
			for(int i = j; i < B.length(); i++){
				diff.digits.insertAfter(B.movePrev());
			}
		}
		else if(large == 2){					//if number being added is larger
			for(int i = j; i < A.length(); i++){
				diff.digits.insertAfter(-1 * A.movePrev());
			}
		}
		*/
		normalizeList(diff.digits);
		return diff;
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
		std::string s;
		if(signum == -1){
			s += "-";
		}
		s += digits.to_string();
		return s;
	}


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
	std::ostream& operator<<( std::ostream& stream, BigInteger N ){
		return stream << N.to_string();
	}

   // operator==()
   // Returns true if and only if A equals B. 
	bool operator==( const BigInteger& A, const BigInteger& B ){
		if(A.compare(B) != 0){
			return false;
		}
		return true;
	}

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
	BigInteger operator+( const BigInteger& A, const BigInteger& B ){
		BigInteger S = A.add(B);
		//normalizeList(S.digits);
		return S;
	}

   // operator+=()
   // Overwrites A with the sum A+B. 
   BigInteger operator+=( BigInteger& A, const BigInteger& B );

   // operator-()
   // Returns the difference A-B. 
	BigInteger operator-( const BigInteger& A, const BigInteger& B ){
		BigInteger D = A.sub(B);
		return D;
	}

   // operator-=()
   // Overwrites A with the difference A-B. 
   BigInteger operator-=( BigInteger& A, const BigInteger& B );

   // operator*()
   // Returns the product A*B. 
   BigInteger operator*( const BigInteger& A, const BigInteger& B );

   // operator*=()
   // Overwrites A with the product A*B. 
   BigInteger operator*=( BigInteger& A, const BigInteger& B );
   
