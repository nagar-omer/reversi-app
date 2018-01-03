//
// Created by orly on 12/28/17.
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include "Command.h"
using namespace std;
/*****************************************************************************
* Class name: CloseCommand inherite from Command
* function name: execute
*               params: vector of string, player socket
*               operation: call the func closeGame, close socket
****************************************************************************/

class CloseCommand : public Command{
public:
    virtual void execute(vector<string> args, int player) {
        //get the list from manager
        int otherPlayer = GameManager::getGameManager()->closeGame(args[1], player);
        if (otherPlayer > 0) {
            char msg[50] = "END";
            //send msg to other client
            int n = write(otherPlayer, msg, 50);
            close(player);
            cout << "game" << args[1]  << "has ended" << endl;
        }
    }
};


#endif //SERVER_CLOSECOMMAND_H