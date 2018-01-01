//
// Created by orly on 12/28/17.
//
#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include "Command.h"
using namespace std;
/*****************************************************************************
* Class name: JoinCommand inherite from Command
* function name: execute
*               params: vector of string, player socket
*               operation: call the func JoinGame, send to client their turns
****************************************************************************/

class JoinCommand : public Command{
public:
    virtual void execute(vector<string> args, int player) {
        char msg[50] = "-1";
        //check if the game exist- send the game name and player
        int otherPlayer = GameManager::getGameManager()->joinGame(args[1], player);
        if (otherPlayer > 0) {
            cout << "start a game - send to both players their colors" << endl;
            char msg1[50] = "1";
            char msg2[50] = "2";

            write(otherPlayer, msg1, 50);
            write(player, msg2, 50);
        } else {
            //the game is not exist- send to player -1
            write(player, msg, 50);
        }
        cout << "game name: "<< args[1] << "has started " <<endl;
        cout << "with players:" << GameManager::getGameManager()->getGame(args[1])->getPlayer1()
                <<" ," << GameManager::getGameManager()->getGame(args[1])->getPlayer2() << endl;
    }
};

#endif //SERVER_JOINCOMMAND_H