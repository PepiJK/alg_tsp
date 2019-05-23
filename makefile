all: main.o tsp.o
	g++ -o tsp main.o tsp.o

main.o: main.cpp
	g++ -c main.cpp

tsp.o: tsp.cpp
	g++ -c tsp.cpp

clean:
	rm tsp main.o tsp.o