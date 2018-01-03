/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/


#ifndef REVERSI_PLAYER_H
#define REVERSI_PLAYER_H

#define PLAYER_ENDED_GAME (-2)
#include "../include/Player.h"
#include "../include/Board.h"
#include <vector>

/*****************************************************************************
 * Board Class: this class contains the board of the game                    *
 ****************************************************************************/
class ReversiPlayer {
protected:
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

    Player *playerRef;
    bool color;
    char flag;
    /*****************************************************************************
     * Function name: stringOptionToVector                                       *
     * Input: string representing move options                                   *
     * Output: vector containing Points for all possible options                 *
     ****************************************************************************/
    vector<Point *> *stringOptionToVector(const string &options) const;
    /*****************************************************************************
     * Function name: PressKeyToContinue - waiting for ENTER                     *
     ****************************************************************************/
    void pressKeyToContinue() {
        // clearing buffer
        cin.get();
        cin.ignore();
    }

    bool checkMoveInput(const string &input) const;

    void deletePoints(vector<Point *> *points) const;
public:
    /*****************************************************************************
     * Function name: ReversiPlayer constructor                                  *
     * Input: player and color(BLACK / WHITE                                     *
     * Output: initialize player reference and save the color                    *
     ****************************************************************************/
    ReversiPlayer(Player *player, bool color):playerRef(player) {
        this->color = color;
        if(color)
            flag = 'X';
        else
            flag = 'O';
    }
    /*****************************************************************************
     * Function name: getPlayer - return player reference                        *
     ****************************************************************************/
    Player *getPlayer() const { return playerRef; };
    /*****************************************************************************
     * Function name: getColor - returs color (BLACK/WHITE)                      *
     ****************************************************************************/
    bool getColor() const { return color; };
    /*****************************************************************************
     * Function name: playReversiMove                                            *
     * Input: array to return result, string representing the move options       *
     * Output: initialize player reference and save the color                    *
     ****************************************************************************/
    virtual void playReversiMove(int result[2], Board *board) = 0;
    virtual void sendLastMove(int move[2]) {};
    virtual ~ReversiPlayer() {};
};



#endif //REVERSI_PLAYER_H
