/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
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
    virtual void playReversiMove(int *result, Board &board);
};

#endif //REVERSI_LOCAL_PLAYER_H
