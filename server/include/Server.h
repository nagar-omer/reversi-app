/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "CommandsManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iterator>
#include <stdio.h>

using namespace std;

struct paramsToThread {
    vector<string> args;
    int clientSocket1;
    CommandsManager * commandsManager;
};

/*****************************************************************************
 * Class name: Server
 * Function: connect between two clients
 ****************************************************************************/
class Server {
    public:
        Server(int port);
        void start();
        void stop();
        int getServerSocket(){return serverSocket;}


    private:
        int port;
        int serverSocket; // the socket's file descriptor
        int numOfThreads;
        CommandsManager commandsManager;

};


#endif //SERVER_SERVER_H
