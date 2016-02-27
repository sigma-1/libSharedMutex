.PHONY: all
all:
	clang++ -std=c++14 -c shared_mutex.cpp -o shared_mutex.o
	clang++ -std=c++14 shared_mutex.o -dynamiclib -o $(realpath ./)/libshared_mutex.dylib
