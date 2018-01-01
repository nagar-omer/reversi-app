/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <iterator>

#define MAX_CONNECTED_CLIENTS 50

using namespace std;

/*****************************************************************************
* static function name: splitMsg
* params: msg and container
* return: none
* operation: split the char * msg into vector of string by " " delimeter
*****************************************************************************/
static void splitMsg(char* msg, vector <string>& newLocation)
{
    newLocation.clear();
    std::vector<char*> v;
    char* chars_array = strtok(msg, " ");
    while(chars_array)
    {
        v.push_back(chars_array);
        chars_array = strtok(NULL, " ");
    }

    for(size_t n = 0; n < v.size(); ++n)
    {
        char* subchar_array = strtok(v[n], ":");
        while (subchar_array) {
            newLocation.push_back(string(subchar_array));
            subchar_array = strtok(NULL, ":");
        }
    }
}

/*****************************************************************************
* static function name: clientHandler
* params: void * param
* return: none
* operation: read the msg from client and execute the command requested
*****************************************************************************/
static void* clientHandler(void * param)
{
    //lock the struct param
    struct paramsToThread * ptr = (struct paramsToThread *)param;
    string command = ptr->args[0];
    int clientSocket = ptr->clientSocket1;
    ptr->commandsManager->executeCommand(command, ptr->args ,clientSocket);

    char msg[50];

    //read while clientSocket is open
    while(read(clientSocket, msg, 50) != -1){
        splitMsg(msg,ptr->args);
        if(ptr->args[0].compare("END")==0) {
            //this is msg from client2 to disconnect him and finish all
            close(clientSocket);
            break;
        }
        //execute command
        command = ptr->args[0];
        ptr->commandsManager->executeCommand(command , ptr->args ,clientSocket);
    }
    //deallocate
    delete ptr;
}

/*****************************************************************************
 * Function name: Server
 * Operation: Constructor
 ****************************************************************************/
Server::Server(int port){
    this->port= port;
    this->serverSocket=0;
    this->numOfThreads=0;
    cout << "Server is connect" << endl;
}

/*****************************************************************************
 * Function name: start
 * Operation: wait for clients to connect
 * for every client open a thread to handle it
 ****************************************************************************/
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

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding!";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    // Define the clients socket's structures
    struct sockaddr_in clientAddress1;
    socklen_t clientAddressLen1=0;
    struct sockaddr_in clientAddress2;
    socklen_t clientAddressLen2=0;

    char msg[50];
    vector<pthread_t> threads(MAX_CONNECTED_CLIENTS);

    while (true) {

        cout << "Waiting for client connections..." << endl;
        // Accept a new client 1 connection
        int clientSocket1 = accept(serverSocket, (struct sockaddr *) &clientAddress1, &clientAddressLen1);
        if (clientSocket1 == -1)
            throw "Error on accept";
        cout << "Client 1 connected - get the msg:" << endl;

        //read the msg from client 1
        int n = read(clientSocket1, msg, 50);
        if (n == -1) {
            cout << "Error reading msg" << endl;
            return;
        }

        //split the msg of client into args
        vector <string> args;
        splitMsg(msg, args);

        //check if the request is "list_games" - (no need to create thread)
        if(args[0].compare("list_games")==0) {
            this->commandsManager.executeCommand("list_games", args, clientSocket1);
        }
        else{// send to thread client_handler
            //initial params to thread
            struct paramsToThread * params = new paramsToThread();
            params->args= args;
            params->clientSocket1= clientSocket1;
            params->commandsManager = &this->commandsManager;

            int rc = pthread_create(&threads[this->numOfThreads], NULL, clientHandler, params);
            this->numOfThreads++;
            if (rc) {
                cout << "Error: unable to create thread, " << rc << endl;
                exit(-1);
            }
        }
    }
}

void Server::stop() {
    close(getServerSocket());
}

