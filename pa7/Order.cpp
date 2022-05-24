#include<iostream>
#include<string>
#include <fstream>
#include"Dictionary.h"

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Invalid number of arguments. Use ./Order <input file> <output file>\n");
		return EXIT_FAILURE;
	}
	std::ifstream input;
	input.open(argv[1]);
	int i = 1;
	std::string s;
	Dictionary D;
	while(std::getline(input, s)){
		D.setValue(s, i);
		i++;
	}
	input.close();
	std::ofstream output;
	output.open(argv[2]);
	
	output << D.to_string() << std::endl;
	output << D.pre_string() << std::endl;
	D.clear();
	output.close();
	return EXIT_SUCCESS;

}