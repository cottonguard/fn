build: main.o string_util.o
	clang++ -std=c++17 -o main main.o string_util.o

main.o: main.cpp
	clang++ -std=c++17 -c main.cpp

string_util.o: string_util.cpp
	clang++ -std=c++17 -c string_util.cpp
