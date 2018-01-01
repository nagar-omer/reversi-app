//
// Created by orly on 12/25/17.
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H
#include <list>
#include "Game.h"
using namespace std;
/*****************************************************************************
* Class name: GameManager
* this is a singltone class
*****************************************************************************/
class GameManager {
private:
    list<Game*> *games;
    static GameManager *instance;

public:
    /*****************************************************************************
    * function name: getGameManager
    * return: the only instance of this class
    *****************************************************************************/
    static GameManager *getGameManager()
    {
        if (!instance)
            instance = new GameManager();
        return instance;
    }

    GameManager(){
        games = new list<Game*>();
    }

    list<Game*>* getListOfGames(){
        return this->games;
    }

    int addNewGame(string name, int player);
    string getListOfOnePlayer();
    int closeGame(string name, int player);
    int joinGame(string name ,int player2);
    int getOtherPlayer(int player);
    Game *getGame(string name);

};

#endif //SERVER_GAMEMANAGER_H
