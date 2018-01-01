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
public:
    ReversiOnlinePlayer(Player *player, bool color, int serverSocket);
    /*****************************************************************************
     * Function name: playReversiMove                                            *
     * Input: opponent last move and current game board                          *
     * Output: the players move according to answer from server                  *
     ****************************************************************************/
    virtual void playReversiMove(int *lastMove, Board *board) const;

    /*****************************************************************************
     * Function name: sendLastMove                                               *
     * Operation: send to the server the opponents last move                     *
     ****************************************************************************/
    virtual void sendLastMove(int *move) const;

    /*****************************************************************************
     * Function name: default destructor                                         *
     ****************************************************************************/
    virtual ~ReversiOnlinePlayer() {};
};

#endif //REVERSI_ONLINE_PLAYER_H
