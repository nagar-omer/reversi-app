/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef REVERSI_ONLINE_PLAYER_H
#define REVERSI_ONLINE_PLAYER_H

#include "../include/ReversiPlayer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <sstream>

class ReversiOnlinePlayer: public ReversiPlayer{
    int server;
    ostringstream sd;
public:
    ReversiOnlinePlayer(Player *player, bool color, int serverSocket);
    virtual void playReversiMove(int *lastMove, Board &board);
};

#endif //REVERSI_ONLINE_PLAYER_H
