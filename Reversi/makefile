a.out: main.o PlayGround.o Reversi.o ReversiPlayer.o Player.o Board.o
	g++ main.o PlayGround.o Reversi.o ReversiPlayer.o Player.o Board.o

main.o: main.cpp PlayGround.h
	g++ -c main.cpp

PlayGround.o: PlayGround.h Player.h Reversi.h PlayGround.cpp
	g++ -c PlayGround.cpp

Reversi.o: ReversiPlayer.h Board.h Game.h Reversi.h Reversi.cpp
	g++ -c Reversi.cpp

ReversiPlayer.o: Player.h ReversiPlayer.h ReversiPlayer.cpp
	g++ -c ReversiPlayer.cpp

Player.o: Player.h Player.cpp
	g++ -c Player.cpp

Board.o: Board.h Board.cpp
	g++ -c Board.cpp

