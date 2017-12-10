
a.out: Server.o main.o
	g++ Server.o main.o

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

main.o: main.cpp Server.h
	g++ -c main.cpp

