//-----------------------------------------------------------------------------
// Granger Pasko, gpasko 
// Spring CSE101 PA6
// Arithmetic.cpp
// Top level client file utalizing the functions built in BigIntegral to
// perform large number arithmetic.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<fstream>
#include"BigInteger.h"


int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Invalid number of arguments. Use ./Arithmetic <input file> <output file>\n");
		return EXIT_FAILURE;
	}
	std::ifstream input;
	input.open(argv[1]);
	std::string num1;
	std::string num2;
	std::ifstream output;
	output.open(argv[2]);
	if(input.is_open()){
		std::getline(input, num1);
		std::getline(input, num2);
		std::getline(input, num2);
	}
	input.close();
	BigInteger A = BigInteger(num1);
	BigInteger B = BigInteger(num2);
	std::cout << "A = " << A << std::endl;
	std::cout << std::endl;
	std::cout << "B = " << B << std::endl;
	std::cout << std::endl;
	std::cout << "A + B = " << A+B << std::endl;
	std::cout << std::endl;
	std::cout << "A - B = " << A-B << std::endl;
	std::cout << std::endl;
	std::cout << "A - A = " << A-A << std::endl;
	std::cout << std::endl;
	std::string c1 = "3";
	std::string c2 = "2";
	BigInteger C1 = BigInteger(c1);
	BigInteger C2 = BigInteger(c2);
	std::cout << "3A - 2B = " << C1*A - C2*B << std::endl;
	std::cout << std::endl;
	std::cout << "A*B = " << A*B << std::endl;
	std::cout << std::endl;
	std::cout << "A*A = " << A*A << std::endl;
	std::cout << std::endl;
	std::cout << "B*B = " << B*B << std::endl;
	std::cout << std::endl;

	c1 = "9";
	C1 = BigInteger(c1);
	c2 = "16";
	C2 = BigInteger(c2);
	std::cout << "9(A^4) + 16(B^5) = " << C1*A*A*A*A + C2*B*B*B*B*B << std::endl;
	std::cout << std::endl;


}