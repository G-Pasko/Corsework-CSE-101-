Arithmetic.cpp:
	Top level client for the project. 

BigInteger.cpp:
	Implementation file for Arithmetic.

BigInteger.h:
	BigInteger header file.

BigIntegerTest.cpp:
	Test file to esnure that all functions in BigInteger.cpp work as intended.

List.cpp:
	List.c is an ADT that holds all of the helper functions used in
	ListTest.cpp, BigInteger.cpp, Arithmetic.cpp and List.h
	
List.h:
	List.h hold the decloration of all functions in List.c so they
	are usable by the client but not accessable.

ListTest.cpp:

MakeFile:
	Used to create executable files and to compile Lex.c and has
	commands to make ListTest, remove binaries, and check Lex.c and 
	ListTest.c for memory leaks.

~~~~~~~~~~~~~~~~~~~~~~~~~IGNORE .gitkeep ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~