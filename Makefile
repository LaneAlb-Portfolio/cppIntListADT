#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListTest       make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListTest
#  make check2         runs valgrind on Shuffle with command line argument 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
	g++ -std=c++11 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++11 -Wall -c Shuffle.cpp

ListTest : ListTest.o List.o
	g++ -std=c++11 -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.cpp
	g++ -std=c++11 -Wall -c -g ListTest.cpp

List.o : List.h List.cpp
	g++ -std=c++11 -Wall -c -g List.cpp

clean :
	rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35