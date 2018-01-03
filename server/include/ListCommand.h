//
// Created by orly on 12/27/17.
//

#ifndef SERVER_LISTCOMMAND_H
#define SERVER_LISTCOMMAND_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>

#include "Command.h"

using namespace std;
/*****************************************************************************
* Class name: ListCommand inherite from Command
* function name: execute
*               params: vector of string, player socket
*               operation: call the func getListOfOnePlayer, send to client
*               the list
****************************************************************************/

class ListCommand : public Command {
public:
    virtual void execute(vector<string> args, int player) {
        char msg[50] = "-1";

        cout << "execute command list ! :)" << endl;
        //get the list from manager
        string str = GameManager::getGameManager()->getListOfOnePlayer();

        //copy the string into msg
        strncpy(msg, str.c_str(), sizeof(msg));
        msg[sizeof(msg) - 1] = 0;

        //send msg to client
        int n = write(player, msg, 50);
        close(player);
    }
};

#endif //SERVER_LISTCOMMAND_H
