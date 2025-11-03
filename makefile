all: main

main: bst.o main.o
	g++ -std=c++11 bst.o test_bst.o -o test


main.o: bst.o test_bst.cpp
	g++ -std=c++11 -c test_bst.cpp 

bst.o: bst.cpp bst.h
		g++ -std=c++11 -c bst.cpp

clean:
	rm -f all *.o
