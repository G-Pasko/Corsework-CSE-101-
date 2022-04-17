List.c:
	List.c is an ADT that holds all of the helper functions used in
	ListTest.c, Lex.c, and List.h
List.h:
	List.h hold the decloration of all functions in List.c so they
	are usable by the client but not accessable.
Graph.c:
	Graph.c is an ADT that holds all of the helper functios used in GraphTest.c,
	Graph.h, and FindComponents.c
Graph.h:
	Graph.h holds the decloration of all functions in Graph.c so they are usable
	by the client but not accessable.
GraphTest.c: 
	GraphTest is meant to be a script that uses all of the functions in Graph.c to
	ensure that they work as intended. 
FindComponents.c: 
	Find components is the script meant for grading and will create a graph using
	functions from Graph.c and inputs given by an input file. It will the print the 
	adjacency list of the new Graph to the specified output file. It will run DFS on
	the Graph and transpose of Graph
MakeFile:
	Used to create executable files and to compile Lex.c and has
	commands to make ListTest, remove binaries, and check Lex.c and 
	ListTest.c for memory leaks.

~~~~~~~~~~~~~~~~~~~~~~~~~IGNORE .gitkeep ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
