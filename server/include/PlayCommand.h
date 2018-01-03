
//
// Created by orly on 12/28/17.
//
#ifndef SERVER_PLAYCOMMAND_H
#define SERVER_PLAYCOMMAND_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include "Command.h"
using namespace std;
/*****************************************************************************
* Class name: PlayCommand inherite from Command
* function name: execute
*               params: vector of string, player socket
*               operation: send to other player the move
****************************************************************************/

class PlayCommand : public Command{
public:
    virtual void execute(vector<string> args, int player) {
        char msg[50] = "-1";
        //check if the game exist- send the game name and player
        int otherPlayer = GameManager::getGameManager()->getOtherPlayer(player);
        if (otherPlayer > 0) {
            char msg1[50];
            strcpy(msg1, args[1].c_str());
            write(otherPlayer, msg1, 50);
        } else {
            //the game is not exist- send to player -1
            write(player, msg, 50);
        }
    }
};

#endif //SERVER_PLAYCOMMAND_H