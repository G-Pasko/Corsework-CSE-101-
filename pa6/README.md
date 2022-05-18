Arithmetic.cpp:
	Top level client for the project. That performs arithmatic operations on
	BigInterval variables to match the desired outcome provided by the professor

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
	ListTest ensures that all functions created in List.cpp work as intended

MakeFile:
	Used to create executable files and to compile Lex.c and has
	commands to make ListTest, remove binaries, and check Lex.c and 
	ListTest.c for memory leaks.


SIDE NOTE: 
	Sorry this lab never got finished. I ended up being very busy this week and
	got sick towards the end. Also, it was a pretty hard lab.

~~~~~~~~~~~~~~~~~~~~~~~~~IGNORE .gitkeep ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~