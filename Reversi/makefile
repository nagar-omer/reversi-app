a.out: main.o PlayGround.o Reversi.o ReversiPlayer.o Player.o Board.o ReversiOnlinePlayer.o ReversiLocalPlayer.o ReversiPcPlayer.o
	g++ main.o PlayGround.o Reversi.o ReversiPlayer.o Player.o Board.o ReversiOnlinePlayer.o ReversiLocalPlayer.o ReversiPcPlayer.o

main.o: src/main.cpp include/PlayGround.h
	g++ -c src/main.cpp

PlayGround.o: include/PlayGround.h include/Player.h include/Reversi.h src/PlayGround.cpp
	g++ -c src/PlayGround.cpp

Reversi.o: include/ReversiPlayer.h include/Board.h include/Game.h include/Reversi.h include/ReversiLocalPlayer.h include/ReversiPcPlayer.h include/ReversiOnlinePlayer.h src/Reversi.cpp
	g++ -c src/Reversi.cpp

ReversiOnlinePlayer.o: include/Player.h include/ReversiPlayer.h include/ReversiLocalPlayer.h src/ReversiLocalPlayer.cpp
	g++ -c src/ReversiLocalPlayer.cpp

ReversiLocalPlayer.o: include/Player.h include/ReversiPlayer.h include/ReversiOnlinePlayer.h src/ReversiOnlinePlayer.cpp
	g++ -c src/ReversiOnlinePlayer.cpp

ReversiPcPlayer.o: include/Player.h include/ReversiPlayer.h include/ReversiPcPlayer.h src/ReversiPcPlayer.cpp
	g++ -c src/ReversiPcPlayer.cpp

ReversiPlayer.o: include/Player.h include/ReversiPlayer.h src/ReversiPlayer.cpp
	g++ -c src/ReversiPlayer.cpp

Player.o: include/Player.h src/Player.cpp
	g++ -c src/Player.cpp

Board.o: include/Board.h src/Board.cpp
	g++ -c src/Board.cpp
