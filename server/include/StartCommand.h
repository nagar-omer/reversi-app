//
// Created by orly on 12/21/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>

#include "Command.h"

using namespace std;
/*****************************************************************************
* Class name: StartCommand inherite from Command
* function name: execute
*               params: vector of string, player socket
*               operation: call the func addNewGame and add the game if not
*               exist
****************************************************************************/

class StartCommand: public Command {
public:
    virtual void execute(vector<string> args, int player) {
        char msg[50]= "-1";

        //check if the game exist- send the game name and player
        if(GameManager::getGameManager()->addNewGame(args[1],player) < 0)
        {
            cout << "the game is already exist- send to player -1" << endl;
            //the game is already exist- send to player -1
            int n = write(player, msg, 50);

        }
    }
};
#endif //SERVER_STARTCOMMAND_H
