all: main
all:main-1

main: bst.o main.o
	g++ -std=c++11 bst.o test_bst.o -o test

main.o: bst.o test_bst.cpp
	g++ -std=c++11 -c test_bst.cpp

main-1: bst.o main-1.o
	g++ -std=c++11 bst.o main.o -o usecase

main-1.o: bst.h main.cpp
	g++ -std=c++11 -c main.cpp

bst.o: bst.cpp bst.h
		g++ -std=c++11 -c bst.cpp

clean:
	rm -f all *.o
