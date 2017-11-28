//
// Created by orly on 11/28/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H


class Server {
    public:
        Server(int port);
        void start();
        void stop();
    private:
        int port;
        int serverSocket; // the socket's file descriptor
        void handleClient(int clientSocket1, int clientSocket2);
};


#endif //SERVER_SERVER_H
