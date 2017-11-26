/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#ifndef REVERSIPLAYER_H
#define REVERSIPLAYER_H

#include "Player.h"
#include "Board.h"
#include <vector>

/*****************************************************************************
 * Board Class: this class contains the board of the game                    *
 ****************************************************************************/
class ReversiPlayer {
    /*****************************************************************************
     * Inner Class Point: makes it easier to store x,y in a vector   (mutable)   *
     ****************************************************************************/
    class Point{
        int x,y;
    public:
        // simple constructor and get functions
        Point(int inX,int inY): x(inX), y(inY){};
        int getX() const { return x; };
        int getY() const { return y; };
    };

    Player &playerRef;
    bool color;
    char flag;
    /*****************************************************************************
     * Function name: stringOptionToVector                                       *
     * Input: string representing move options                                   *
     * Output: vector containing Points for all possible options                 *
     ****************************************************************************/
    vector<Point *> *stringOptionToVector(const string &options) const;
    /*****************************************************************************
     * Function name: userMove                                                   *
     * Input: array for returning result, string for possible options            *
     * Output: user picking according to user input                              *
     ****************************************************************************/
    void userMove(int result[2], Board &bord);
    /*****************************************************************************
     * Function name: computerMove                                               *
     * Input: array for returning result, string for possible options            *
     * Output: computer picking according to possibilities                       *
     ****************************************************************************/
    void computerMove(int result[2], Board &board);
    /*****************************************************************************
     * Function name: PressKeyToContinue - waiting for ENTER                     *
     ****************************************************************************/
    void pressKeyToContinue() {
        // clearing buffer
        cin.ignore();
        string junk;
        getline(cin, junk);
    }

    bool checkMoveInput(const string &input) const;

    void deletePoints(vector<Point *> *points) const;
public:
    /*****************************************************************************
     * Function name: ReversiPlayer constructor                                  *
     * Input: player and color(BLACK / WHITE                                     *
     * Output: initialize player reference and save the color                    *
     ****************************************************************************/
    ReversiPlayer(Player &player, bool color):playerRef(player) {
        this->color = color;
        if(color)
            flag = 'X';
        else
            flag = 'O';
    }
    /*****************************************************************************
     * Function name: getPlayer - return player reference                        *
     ****************************************************************************/
    Player &getPlayer() const { return playerRef; };
    /*****************************************************************************
     * Function name: getColor - returs color (BLACK/WHITE)                      *
     ****************************************************************************/
    bool getColor() const { return color; };
    /*****************************************************************************
     * Function name: playReversiMove                                            *
     * Input: array to return result, string representing the move options       *
     * Output: initialize player reference and save the color                    *
     ****************************************************************************/
    void playReversiMove(int result[2], Board &board);
};



#endif //REVERSIPLAYER_H
