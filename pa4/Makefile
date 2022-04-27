#-------------------------------------------------------------------------------
# Granger Pasko, gpasko
# 2022 Spring CSE101 PA4 
# 
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes FindComponents
#  make MatrixTest           makes MatrixTest
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in7
#  make checkTest         	tests MatrixTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Matrix.c List.c
BASE_OBJECTS   = Matrix.o List.o
HEADERS        = Matrix.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

MatrixTest : MatrixTest.o $(BASE_OBJECTS)
	$(LINK) MatrixTest MatrixTest.o $(BASE_OBJECTS)

ListTest : ListTest.o $(BASE_OBJECTS)
	$(LINK) ListTest ListTest.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

MatrixTest.o : MatrixTest.c $(HEADERS)
	$(COMPILE) MatrixTest.c

ListTest.o : ListTest.c $(HEADERS)
	$(COMPILE) ListTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents MatrixTest FindComponents.o MatrixTest.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in7 junk7

checkTest : MatrixTest
	$(MEMCHECK) MatrixTest