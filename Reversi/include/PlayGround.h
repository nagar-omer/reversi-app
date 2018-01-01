/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef OTHELLO_PLAYGROUND_H
#define OTHELLO_PLAYGROUND_H

#include "../include/Reversi.h"

class PlayGround {

    enum menue {BACK, NEW_PLAYER, NEW_GAME, EXIT};
    enum games {REVERSI = 1};
    vector<Player *> players;
    Reversi *reversi;

    /*****************************************************************************
     * Function name: addPlayer                                                  *
     * Operation: the function asks from the user to enter new Player            *
     ****************************************************************************/
    void addPlayer();

    /*****************************************************************************
     * Function name: startGame                                                  *
     * Operation: asks from user to choose a game and stars the game             *
     ****************************************************************************/
    void startGame();

    /*****************************************************************************
     * Function name: startReversiGame                                           *
     * Operation: creates reversi object and starts the game                     *
     ****************************************************************************/
    void startReversiGame();

    /*****************************************************************************
     * Function name: getPlayerByID                                              *
     * Output: returns ptr for player by his ID                                  *
     ****************************************************************************/
    Player *getPlayerByID(int id);
public:
    /*****************************************************************************
     * Function name: default constructor                                        *
     * operation: creates first player - computer (ID = 1)                       *
     ****************************************************************************/
    PlayGround(){
        // creating Computer User
        // serial number 1
        players.push_back(new Player("PC", Player::PC));
        // serial number 2
        players.push_back(new Player("ONLINE", Player::ONLINE_PLAYER));
        reversi = new Reversi(&players);
    };

    /*****************************************************************************
     * Function name: default destructor                                         *
     ****************************************************************************/
    ~PlayGround();

    /*****************************************************************************
     * Function name: go                                                         *
     * Operation: shows th Main Menu                                             *
     ****************************************************************************/
    void go();

};


#endif //OTHELLO_PLAYGROUND_H
