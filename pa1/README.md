Lex.c:
	The Lex file is meant to read an input file and sort the lines
	in alphabetical order then prints them to the output file.
	Format: ./Lex <input file> <output file> 
List.c:
	List.c is an ADT that holds all of the helper functions used in
	ListTest.c, Lex.c, and List.h
List.h:
	List.h hold the decloration of all functions in List.c so they
	are usable by the client but not accessable.
ListTest.c:
	ListTest is my testing file that utalizes every function in List.c
	to ensure they all work as they should.
	(Based on ListClient with modifications to fufill requirements)
MakeFile:
	Used to create executable files and to compile Lex.c and has
	commands to make ListTest, remove binaries, and check Lex.c and 
	ListTest.c for memory leaks.
