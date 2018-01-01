
a.out: Server.o CommandsManager.o GameManager.o main.o
	g++ Server.o CommandsManager.o GameManager.o main.o -pthread

Server.o: Server.cpp Server.h
	g++ -c Server.cpp -pthread

CommandsManager.o: CommandsManager.cpp CommandsManager.h Game.h StartCommand.h ListCommand.h  JoinCommand.h PlayCommand.h CloseCommand.h Command.h
	g++ -c CommandsManager.cpp -pthread

GameManager.o: GameManager.cpp GameManager.h
	g++ -c GameManager.cpp -pthread

main.o: main.cpp Server.h      
	g++ -c main.cpp -pthread
#-std=c++11
