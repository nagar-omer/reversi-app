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
enum {ONLINE_BACK, ONLINE_NEW, ONLINE_LIST, ONLINE_JOIN};


/*****************************************************************************
 * Reversi Class: this class contains reversi game itself                    *
 ****************************************************************************/
class Reversi: public Game {
    ReversiPlayer *player1, *player2;
    Board *board;
    string gameName;
    const vector<Player *> &allPlayers;
    int clientSocket;
    bool playerEndedGame;

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

    /*****************************************************************************
     * Function name: startGame                                                  *
     * Input: override method for Game "Interface" - starting game               *
     ****************************************************************************/
    virtual void startGame();

    /*****************************************************************************
     * Function name: getSettingsFromUser                                        *
     * Output: main menu for reversi game                                        *
     ****************************************************************************/
    bool getSettingsFromUser();

    /*****************************************************************************
     * Function name: isNumber                                                   *
     * Input: string                                                             *
     * Output: true/false -> number/NAN                                          *
     ****************************************************************************/
    bool isNumber(string &s);

    /*****************************************************************************
     * Function name: initLocalPlayer                                            *
     * Input: playerNum = 1/2, color = BLACK/WHITE                               *
     * Output: initiate first/second player as local player                      *
     ****************************************************************************/
    int getLocalPlayerIndex(bool is2PlayersLocal, int id1 = 1, bool isSecondPlayer = false);

    /*****************************************************************************
     * Function name: setOnline                                                  *
     * Output: navigation for online mode                                        *
     ****************************************************************************/
    int getOnlineOption();

    /*****************************************************************************
     * Function name: getBoardSize                                               *
     * Output: get board size from user                                          *
     ****************************************************************************/
    int getBoardSize();

    /*****************************************************************************
     * Function name: getPlayerByID                                              *
     * Output: returns ptr for player by his ID                                  *
     ****************************************************************************/
    Player *getPlayerByID(int id){
        for(vector<Player *>::const_iterator it = allPlayers.begin(); it != allPlayers.end(); ++it)
            if(id == (*it)->getSerial())
                return (*it);
        return NULL;
    };

    /*****************************************************************************
     * Function name: setOnline                                                  *
     * Output: navigation for online mode                                        *
     ****************************************************************************/
    bool setOnline(int option);

    /*****************************************************************************
     * Function name: playReversiMove                                            *
     * Input: opponent last move and current game board                          *
     * Output: the players move according to answer from server                  *
     ****************************************************************************/
    void printExistingGames();

    /*****************************************************************************
     * Function name: startNewOnlineGame                                         *
     * Operation: initiate players board and server connection for online mode   *
     * for starting a new game                                                   *
     ****************************************************************************/
    bool startNewOnlineGame();

    /*****************************************************************************
     * Function name: joinGame                                                   *
     * Operation: initiate players board and server connection for online mode   *
     * for joining existing game                                                 *
     ****************************************************************************/
    bool joinGame();

    /*****************************************************************************
     * Function name: closeConnection                                            *
     * Operation: inform server that the game was over and terinate connection   *
     ****************************************************************************/
    void closeConnection(const ReversiPlayer *closingPlayer) const;
public:
    // funcs for testing
    Board *getBoard() { return board; };
    ReversiPlayer *getPlayer1() { return player1; };
    ReversiPlayer *getPlayer2() { return player2; };
    // end of funcs for testing

    /*****************************************************************************
     * Function name: default constructor - initiate players and board           *
     ****************************************************************************/
    Reversi(const vector<Player *> &players);

    /*****************************************************************************
     * Function name: default destructor - delete players                        *
     ****************************************************************************/
    ~Reversi(){
        delete(player1);
        delete(player2);
        delete(board);
    }

    void go();
};


#endif //REVERSI_H
