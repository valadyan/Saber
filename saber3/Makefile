all: main

main: main.o List.o
	g++ -o main main.o List.o

List.o: List.cpp
	gcc -c List.cpp

main.o: main.cpp
	gcc -c main.cpp

clean:
	rm -f *.o main
