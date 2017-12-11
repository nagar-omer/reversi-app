/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

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
        void handleClient(int clientSocket1, int clientSocket2);
};


#endif //SERVER_SERVER_H
