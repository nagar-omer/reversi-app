/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

static int serialAssign = 1;

class Player {
    string nickName;
    int serialNumber, totalwin, totalLoss;
    bool computer;
public:
    /*****************************************************************************
     * Function name: constructor                                                *
     * Input: player nick name, boolean val for Comp user initialized to false   *
     * Output: initiate name, wins losses to 0, giving the player an Id num      *
     ****************************************************************************/
    Player(const string &nick, bool isComp = false){
        nickName = nick;
        serialNumber = serialAssign++;
        totalwin = 0;
        totalLoss = 0;
        computer = isComp;
    }

    /*****************************************************************************
     * Function name: getSerial                                                  *
     * Output: returns player serial ID                                          *
     ****************************************************************************/
    int getSerial() const {
        return serialNumber;
    }

    /*****************************************************************************
     * Function name: getWins                                                    *
     * Output: returns total number of wins                                      *
     ****************************************************************************/
    int getWins() const {
        return totalwin;
    }

    /*****************************************************************************
     * Function name: getLoss                                                    *
     * Output: returns total number of losses                                    *
     ****************************************************************************/
    int getLoss() const {
        return totalLoss;
    }

    /*****************************************************************************
     * Function name: nick                                                       *
     * Output: returns player nick name                                          *
     ****************************************************************************/
    string nick() const {
        return nickName;
    }

    /*****************************************************************************
     * Function name: isComputer                                                 *
     * Output: returns boolean value to indicate if the player is representing   *
     *           a compute                                                       *
     ****************************************************************************/
    bool isComputer(){
        return computer;
    }

    /*****************************************************************************
     * Function name: operator ostream << Player                                 *
     * Operation: prints Player to ostream                                       *
     ****************************************************************************/
    friend ostream &operator << (ostream &os, const Player &player);

    /*****************************************************************************
     * Function name: operator ++Player                                          *
     * Operation: increases the total number of wins by 1                        *
     ****************************************************************************/
    friend int operator++(Player &player);

    /*****************************************************************************
     * Function name: operator --Player                                          *
     * Operation: increases the total number of losses by 1                      *
     ****************************************************************************/
    friend int operator--(Player &player);

};


#endif //PLAYER_H
