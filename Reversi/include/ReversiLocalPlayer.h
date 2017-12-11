/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef REVERSI_LOCAL_PLAYER_H
#define REVERSI_LOCAL_PLAYER_H

#include "../include/ReversiPlayer.h"
class ReversiLocalPlayer: public ReversiPlayer {
public:
    ReversiLocalPlayer(Player *player, bool color): ReversiPlayer(player, color) {};

    /*****************************************************************************
     * Function name: userMove                                                   *
     * Input: array for returning result, string for possible options            *
     * Output: user picking according to user input                              *
     ****************************************************************************/
    virtual void playReversiMove(int *result, Board *board);

    /*****************************************************************************
     * Function name: default destructor                                         *
     ****************************************************************************/
    virtual ~ReversiLocalPlayer() {};
};

#endif //REVERSI_LOCAL_PLAYER_H
