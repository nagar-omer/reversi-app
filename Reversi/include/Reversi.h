/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#ifndef REVERSI_H
#define REVERSI_H


#include "Game.h"
#include "ReversiPlayer.h"
#include "Board.h"

/*****************************************************************************
 * Reversi Class: this class contains reversi game itself                    *
 ****************************************************************************/
class Reversi: public Game {
    ReversiPlayer player1, player2;
    Board board;

    /*****************************************************************************
     * Function name: play                                                       *
     * Input: RevesiPlayer - player (not Player)                                 *
     * Output: play move for requested player                                    *
     ****************************************************************************/
    bool play(ReversiPlayer player);

public:
    /*****************************************************************************
     * Function name: default constructor - initiate players and board           *
     ****************************************************************************/
    Reversi(Player &firstPlayer, Player &seconedPlayer, int rowSize = 8, int colSize = 8):
            player1(firstPlayer,Board::WHITE), player2(seconedPlayer,Board::BLACK), board(rowSize,colSize) {};

    /*****************************************************************************
     * Function name: startGame                                                  *
     * Input: override method for Game "Interface" - starting game               *
     ****************************************************************************/
    virtual void startGame();
};


#endif //REVERSI_H