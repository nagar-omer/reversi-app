//
// Created by orly on 11/28/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server is connect" << endl;
}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    // Define the clients socket's structures
    struct sockaddr_in clientAddress1;
    socklen_t clientAddressLen1;
    struct sockaddr_in clientAddress2;
    socklen_t clientAddressLen2;

    while (true) {
        cout << "Waiting for client1 connections..." << endl;
        // Accept a new client 1 connection
        int clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress1, &clientAddressLen1);
        cout << "Client 1 connected" << endl;
        if (clientSocket1 == -1)
            throw "Error on accept";

        //send to client 1 - "wait for" msg:
        int n = write(clientSocket1, "wait for client 2 to connect", sizeof("wait for client 2 to connect"));
        if (n == -1) {
            cout << "Error writing to socket1" << endl;
            return;
        }

        cout << "Waiting for client2 connections..." << endl;
        // Accept a new client 2 connection
        int clientSocket2 = accept(serverSocket, (struct sockaddr *) &clientAddress2, &clientAddressLen2);
        cout << "Client 2 connected" << endl;
        if (clientSocket2 == -1)
            throw "Error on accept";

        //send to the clients their number to start
        n = write(clientSocket1, "1", sizeof("1"));
        if (n == -1) {
            cout << "Error writing to socket1" << endl;
            return;
        }

        n = write(clientSocket2, "2", sizeof("2"));
        if (n == -1) {
            cout << "Error writing to socket1" << endl;
            return;
        }

        handleClient(clientSocket1, clientSocket2);
        // Close communication with the client
        close(clientSocket1);
        close(clientSocket2);
    }
}

void Server::handleClient(int clientSocket1, int clientSocket2) {
    char move[6];

    while (true) {
        // Read new move argument from client 1
        int n = read(clientSocket1, &move, sizeof(move));
        if (n == -1) {
            cout << "Error reading move" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        cout << "Got Move: " << move << endl;

        //send the move to other player
        if (move[0] != 'N') {//“NoMove”
            n = write(clientSocket2, &move, sizeof(move));
            if (n == -1) {
                cout << "Error writing to socket" << endl;
                return;
            }
            if (move[0] == 'E')// end the game
                break;
            //the first client tha see that the board is full, send a msg "End" to sever
            //and the server sent it to the other client

            // Read new move argument from client 2
            n = read(clientSocket2, &move, sizeof(move));
            if (n == -1) {
                cout << "Error reading move" << endl;
                return;
            }
            if (n == 0) {
                cout << "Client disconnected" << endl;
                return;
            }
            cout << "Got Move: " << move << endl;
            //send the move to other player
            n = write(clientSocket1, &move, sizeof(move));
            if (n == -1) {
                cout << "Error writing to socket" << endl;
                return;
            }
            if (move[0] == 'E')// end the game
                break;
            //the first client tha see that the board is full, send a msg "End" to sever
            //and the server sent it to the other client
        }
        cout << "close server" << endl;
        //TODO
    }

}
void Server::stop() {
    close(serverSocket);
}