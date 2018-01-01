//
// Created by orly on 12/21/17.
//

#include "CommandsManager.h"
/*****************************************************************************
* function name: CommandsManager()
* operation: constructor
*****************************************************************************/
CommandsManager::CommandsManager() {
    this->commandsMap["start"] = new StartCommand();
    this->commandsMap["list_games"] = new ListCommand();
    this->commandsMap["join"] = new JoinCommand();
    this->commandsMap["play"] = new PlayCommand();
    this->commandsMap["close"] = new CloseCommand();
}

/*****************************************************************************
* function name: executeCommand
* params: command, args, client socket
* operation: execute spesific command
*****************************************************************************/
void CommandsManager::executeCommand(string command, vector<string> args, int clientAddress) {
    Command *commandObj = this->commandsMap[command];
    commandObj->execute(args, clientAddress);
}

/*****************************************************************************
* function name: ~CommandsManager()
* operation: destructor
*****************************************************************************/
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}