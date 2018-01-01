//
// Created by orly on 12/21/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H
#include "StartCommand.h"
#include "ListCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"
#include <map>
#include "Command.h"
#include "Game.h"
#include <list>
#include <vector>

/*****************************************************************************
* Class name: CommandsManager
*****************************************************************************/

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command, vector<string> args, int clientAdddress);
private:
    map<string, Command *> commandsMap;

};

#endif //SERVER_COMMANDSMANAGER_H
