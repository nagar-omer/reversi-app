//
// Created by orly on 12/21/17.
//

#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H
#include <string>
#include <list>
#include <vector>
#include "Game.h"
#include "GameManager.h"

using namespace std;
/*****************************************************************************
* Class name: interface Command
****************************************************************************/
class Command {
public:
    virtual void execute(vector<string> args, int clientAddress) = 0;
    virtual ~Command() {}
};

#endif //SERVER_COMMAND_H
