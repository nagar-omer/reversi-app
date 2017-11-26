/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#include "../include/Player.h"

/*****************************************************************************
 * Function name: operator ++Player                                          *
 * Operation: increases the total number of wins by 1                        *
 ****************************************************************************/
int operator++(Player &player){
    (player.totalwin)++;
    return player.totalwin;
}

/*****************************************************************************
 * Function name: operator --Player                                          *
 * Operation: increases the total number of losses by 1                      *
 ****************************************************************************/
int operator--(Player &player){
    (player.totalLoss)++;
    return player.totalLoss;
}

/*****************************************************************************
 * Function name: operator ostream << Player                                 *
 * Operation: prints Player to ostream                                       *
 ****************************************************************************/
ostream &operator << (ostream &os, const Player &player){
    ostringstream result;
    result << "Player name:\t" << player.nickName << "." << endl;
    result << "Player ID:\t" << player.serialNumber << "." << endl;
    result << "Total wins:\t" << player.totalwin << "." << endl;
    result << "Total Losses:\t" << player.totalLoss << "." << endl;
    return os << result.str();
}