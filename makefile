all: main.o file.o
	g++ -o tsp main.o file.o

main.o: main.cpp
	g++ -c main.cpp

file.o: file.cpp
	g++ -c file.cpp

clean:
	rm tsp main.o file.o