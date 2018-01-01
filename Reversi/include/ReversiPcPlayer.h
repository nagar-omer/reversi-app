/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#ifndef REVERSI_PC_PLAYER_H
#define REVERSI_PC_PLAYER_H

#include "ReversiPlayer.h"

class ReversiPcPlayer: public ReversiPlayer{
public:
    ReversiPcPlayer(Player *player, bool color): ReversiPlayer(player, color) {};

    /*****************************************************************************
     * Function name: playReversiMove                                            *
     * Input: array for returning result, string for possible options            *
     * Output: computer picking according to possibilities                       *
     ****************************************************************************/
    virtual void playReversiMove(int *result, Board *board) const;

    /*****************************************************************************
     * Function name: default destructor                                         *
     ****************************************************************************/
    virtual ~ReversiPcPlayer() {};

};

#endif //REVERSI_PC_PLAYER_H
