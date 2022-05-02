List.c:
	List.c is an ADT that holds all of the helper functions used in
	ListTest.c, Lex.c, and List.h
List.h:
	List.h hold the decloration of all functions in List.c so they
	are usable by the client but not accessable.
Matrix.c:
	Matrix.c is an ADT that holds all of the helper functios used in MatrixTest.c,
	Matrix.h, and Sparce.c
Matrix.h:
	Matrix.h holds the decloration of all functions in Matrix.c so they are usable
	by the programmer but not the client.
MatrixTest.c: 
	MatrixTest is meant to be a script that uses all of the functions in Matrix.c to
	ensure that they work as intended. 
Sparce.c: 
	Sparce is the script meant for grading and will create a graph using
	functions from Matrix.c and inputs given by an input file. It will the print two
	matrices and various arithmatic operations on them and print the result.
	to the specified output file.
MakeFile:
	Used to create executable files and to compile Lex.c and has
	commands to make ListTest, remove binaries, and check Lex.c and 
	ListTest.c for memory leaks.

~~~~~~~~~~~~~~~~~~~~~~~~~IGNORE .gitkeep ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
