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

const int power = 9;
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
		int i;
		//int j = 0;
		if(!isalnum(s[0])){
			if(int(s[0])  == 45){			//45 is ascii value of "-"
				signum = -1;
			}
			//j = 1;
		}
		signum = 1;
		
		for(i = abs(signum); i < s.length(); i++){
			if(!isalnum(s[i])){
				throw std::invalid_argument("BigInteger: Constructor: non_numeric string");
			}
		}
		//std::string zero = "0";
		while(s.length() % 9 != 0){
			s.insert(0, "0");
		}
		for(i = s.length(); i >= power; i = i - power){
			digits.insertAfter(stol(s.substr(i - power, power)));
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
		if(this->signum != N.signum){
			if(this->signum < N.signum){
				return -1;
			}
			else{
				return 1;
			}
		}
		else{
			List A = digits;
			List B = N.digits;
			if(signum == -1){
				if(A.length() < B.length()){
					return 1;
				}
				else if(A.length() > B.length()){
					return -1;
				}
			}
			else{
				if(A.length() > B.length()){
					return 1;
				}
				else if(A.length() < B.length()){
					return -1;
				}
			}
			
			A.moveFront();
			B.moveFront();
			for(int i = 0; i < A.length(); i++){
				int x = A.moveNext();
				int y = B.moveNext();
				if(x > y){
					return 1;
				}
				if(x < y){
					return -1;
				} 
			}
			return 0;
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
		for(int i = 0; i < L.length(); i++){
			if(L.position() > 1){
				if(L.peekPrev() >= base){
					long new_val = L.movePrev(); 
					while(new_val >= base){ 
						L.setAfter(new_val - base);
						L.setBefore(L.peekPrev() + 1);
						new_val = L.peekNext();
					}
					M.insertAfter(new_val);
				}
				else if(L.peekPrev() < 0){
					long new_val = L.movePrev(); 
					while(new_val < 0){ 
						L.setAfter(new_val + base);
						L.setBefore(L.peekPrev() - 1);
						new_val = L.peekNext();
					}
					M.insertAfter(new_val);
				}
				else{
					M.insertAfter(L.movePrev());
				}
			}
			else{
				if(L.peekPrev() >= base){
					L.movePrev();
					int front = 1;
					L.setAfter(L.peekNext() - base);
					int new_val = L.peekNext();
					while(L.peekNext() >= base){
						front++;
						L.setAfter(L.peekNext() - base);
						new_val = L.peekNext();
					}
					M.insertAfter(new_val);
					M.insertBefore(front);
				}
				else if(L.peekPrev() < 0){
					L.movePrev();
					int front = -1;
					L.setAfter(L.peekNext() + base);
					int new_val = L.peekNext();
					while(L.peekNext() < base){
						front--;
						L.setAfter(L.peekNext() + base);
						new_val = L.peekNext();
					}
					M.insertAfter(new_val);
					M.insertBefore(front);
				}
				
				else{
					M.insertAfter(L.movePrev());
				}
			}
			
		}
		M.moveFront();
		while(M.moveNext() == 0 && (M.position() != M.length())){
			M.eraseBefore();
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

	void shiftList(List& L, int p){
		List A = L;
		A.moveBack();
		for(int i = 0; i < p; i++){
			A.insertAfter(0);
		}
		L = A;
	}

	void scalarMultList(List& L, ListElement m){
		List A;
		L.moveFront();
		for(int i = 0; i < A.length(); i++){
			A.insertBefore(L.moveNext() * m);
		}
		L = A;
	}	

   // makeZero()
   // Re-sets this BigInteger to the zero state.
	void BigInteger::makeZero(){
		signum = 0;
		digits.clear();
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
		normalizeList(sum.digits);
		if(sum.digits.length() == 0){
			sum.makeZero();
		}

		return sum;
	}

   // sub()
   // Returns a BigInteger representing the difference of this and N.
	BigInteger BigInteger::sub(const BigInteger& N) const{
		BigInteger diff;
		List A = digits;
		List B = N.digits;
		
		sumList(diff.digits, A, B, -1);
		normalizeList(diff.digits);
		if(diff.digits.length() == 0){
			diff.makeZero();
		}
		return diff;
	}

   // mult()
   // Returns a BigInteger representing the product of this and N. 
	BigInteger BigInteger::mult(const BigInteger& N) const{
		BigInteger sum;
		if(sign() == 0 || N.sign() == 0 || N.digits.to_string() == "0"){
			return sum;
		}
		List N_digits = N.digits;
		if(N.signum < 0){
			negateList(N_digits);
		}
		N_digits.moveBack();
		for(int i = 0; i < N_digits.length(); i++){
			long num = N_digits.movePrev();
			List scaled = digits;
			scalarMultList(scaled, num);
			shiftList(scaled, i);
			sumList(sum.digits, N_digits, scaled, 1);
			sum.signum = normalizeList(sum.digits);
		}
		if(sum.digits.length() == 0){
			sum.makeZero();
		}
		return sum;

	}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
	std::string BigInteger::to_string(){
		std::string s;
		if(sign() == -1){
			s += "-";
		}/*
		if(sign() == 0){
			s += "0";
			return s;
		}*/
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
		if(A.compare(B) == 0){
			return true;
		}
		return false;
	}

   // operator<()
   // Returns true if and only if A is less than B. 
	bool operator<( const BigInteger& A, const BigInteger& B ){
		if(A.compare(B) < 0){
			return true;
		}
		return false;
	}

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
	bool operator<=( const BigInteger& A, const BigInteger& B ){
		if(A.compare(B) <= 0){
			return true;
		}
		return false;
	}

   // operator>()
   // Returns true if and only if A is greater than B. 
	bool operator>( const BigInteger& A, const BigInteger& B ){
		if(A.compare(B) > 0){
			return true;
		}
		return false;
	}

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
	bool operator>=( const BigInteger& A, const BigInteger& B ){
		if(A.compare(B) >= 0){
			return true;
		}
		return false;
	}

   // operator+()
   // Returns the sum A+B. 
	BigInteger operator+( const BigInteger& A, const BigInteger& B ){
		BigInteger S = A.add(B);
		//normalizeList(S.digits);
		return S;
	}

   // operator+=()
   // Overwrites A with the sum A+B. 
	BigInteger operator+=( BigInteger& A, const BigInteger& B ){
		BigInteger S = A.add(B);
		std::swap(A.digits, S.digits);
		std::swap(A.signum, S.signum);
		return A;
	}

   // operator-()
   // Returns the difference A-B. 
	BigInteger operator-( const BigInteger& A, const BigInteger& B ){
		BigInteger D = A.sub(B);
		return D;
	}

   // operator-=()
   // Overwrites A with the difference A-B. 
	BigInteger operator-=( BigInteger& A, const BigInteger& B ){
		BigInteger D = A.sub(B);
		std::swap(A.digits, D.digits);
		std::swap(A.signum, D.signum);
		return A;
	}

   // operator*()
   // Returns the product A*B. 
	BigInteger operator*( const BigInteger& A, const BigInteger& B ){
		BigInteger M = A.mult(B);
		return M;
	}

   // operator*=()
   // Overwrites A with the product A*B. 
	BigInteger operator*=( BigInteger& A, const BigInteger& B ){
		BigInteger M = A.mult(B);
		std::swap(A.digits, M.digits);
		std::swap(A.signum, M.signum);
		return A;
	}
   
