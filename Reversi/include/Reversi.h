/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef REVERSI_H
#define REVERSI_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream>
#include <stdlib.h>
#include "Game.h"
#include "ReversiPlayer.h"
#include "Board.h"
#include "ReversiLocalPlayer.h"
#include "ReversiPcPlayer.h"
#include "ReversiOnlinePlayer.h"

/*****************************************************************************
 * Reversi Class: this class contains reversi game itself                    *
 ****************************************************************************/
class Reversi: public Game {
    ReversiPlayer *player1, *player2;
    Board *board;
    int rows, cols;
    const vector<Player *> *allPlayers;
    int clientSocket;

    /*****************************************************************************
     * Function name: getPlayerByID                                              *
     * Output: returns ptr for player by his ID                                  *
     ****************************************************************************/
    Player *getPlayerByID(int id){
        for(vector<Player *>::const_iterator it = allPlayers->begin(); it != allPlayers->end(); ++it)
            if(id == (*it)->getSerial())
                return (*it);
        return NULL;
    }
    /*****************************************************************************
     * Function name: play                                                       *
     * Input: RevesiPlayer - player (not Player)                                 *
     * Output: play move for requested player                                    *
     ****************************************************************************/
    bool play(ReversiPlayer *player, int lastMove[2]);

    /*****************************************************************************
     * Function name: initPlayer                                                 *
     * operation: the function initiate a reversiPlayer object acording to       *
     * player type                                                               *
     ****************************************************************************/
    void initPlayer(int playerNum, Player *player, bool color);

    /*****************************************************************************
     * Function name: connectServer                                              *
     * operation: the function establishes a connection with the game's server   *
     ****************************************************************************/
    void connectServer();

    void setOnline();
public:
    // funcs for testing
    Board *getBoard() { return board; };
    ReversiPlayer *getPlayer1() { return player1; };
    ReversiPlayer *getPlayer2() { return player2; };
    // end of funcs for testing

    /*****************************************************************************
     * Function name: default constructor - initiate players and board           *
     ****************************************************************************/
    Reversi(const vector<Player *> *players);

    /*****************************************************************************
     * Function name: default destructor - delete players                        *
     ****************************************************************************/
    ~Reversi(){
        delete(player1);
        delete(player2);
        delete(board);
    }
    /*****************************************************************************
     * Function name: startGame                                                  *
     * Input: override method for Game "Interface" - starting game               *
     ****************************************************************************/
    virtual void startGame();
    bool getSettingsFromUser();
};


#endif //REVERSI_H
