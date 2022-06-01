//-----------------------------------------------------------------------------
// Granger Pasko, gpasko
// Spring CSE101 PA8
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include"Dictionary.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

   size_t begin, end, len;
   std::ifstream in;
   std::ofstream out;
   std::string line;
   std::string token;
   std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
   //string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if(!out.is_open()){
      std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 
   Dictionary D;
   while(getline(in, line)){
      len = line.length();
      
      // get tokens in this line
      //tokenBuffer = "";

      // get first token
      begin = std::min(line.find_first_not_of(delim, 0), len);
      end   = std::min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
      	std::for_each(token.begin(), token.end(), [](char &c){
      		c = ::tolower(c);
      	});
        if(D.contains(token)){
        	D.getValue(token) += 1;
        }
      	else{
    		D.setValue(token, 1);
    	 	//token_count++;
        }
         
         

         // get next token
         begin = std::min(line.find_first_not_of(delim, end+1), len);
         end   = std::min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
         

      }
      

      // print tokens in this line
      //out << "line " << line_count << " contains " << token_count;
      //out << " token" << (token_count==1?"":"s") << endl;
      //out << tokenBuffer << endl;
      
   }
   
   out << D << std::endl;
   //out << D.pre_string() << endl;



   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
