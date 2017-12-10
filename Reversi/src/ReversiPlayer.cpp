/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/
#include <cstdlib>
#include "../include/ReversiPlayer.h"


/*****************************************************************************
 * Function name: checkMoveInput                                             *
 * Input: user input for a move                                              *
 * Output: true if according to format i,j false otherwise                   *
 ****************************************************************************/
bool ReversiPlayer::checkMoveInput(const string &input) const{
    unsigned long int len = input.size();
    // minimum len for row,col
    if(len < 3)
        return false;
    // check that first char in a number
    if (input[0] > '9' || input[0] < '0')
        return false;
    int i = 0;
    // skip all numbers
    while (i < len && input[i] <= '9' && input[i] >= '0')
        i++;
    // if the input looks like 1234\0
    if(i >= len)
        return false;
    else
        // expecting a comma after first number
    if(input[i] != ',')
        return false;
    i++;
    // if input looks like 1234,\0
    if(i >= len)
        return false;
    else
    if(input[i] > '9' || input[i] < '0')
        return false;
    // skip all numbers
    while(i < len && input[i] <= '9' && input[i] >= '0')
        i++;
    if(i >= len || isspace(input[i]))
        return true;
};


/*****************************************************************************
 * Function name: stringOptionToVector                                       *
 * Input: string representing move options                                   *
 * Output: vector containing Points for all possible options                 *
 ****************************************************************************/
vector<ReversiPlayer::Point *> *ReversiPlayer::stringOptionToVector(const string &options) const{
    vector<ReversiPlayer::Point *> *vec = new vector<ReversiPlayer::Point *>();
    if (options.empty())
        return vec;
    string temp = options;
    // replace '(' ')' and ',' with spaces
    size_t found;
    while((found = temp.find_first_of(",()")) != string::npos)
        temp.replace(found, 1, " ");
    // enter options to vec
    istringstream in(temp);
    while (!in.eof()) {
        int currentOption[2];
        in >> currentOption[0] >> currentOption[1];
        vec->push_back(new ReversiPlayer::Point(currentOption[0],currentOption[1]));
    }
    return vec;
}

void ReversiPlayer::deletePoints(vector<ReversiPlayer::Point *> *points) const{
    for(vector<ReversiPlayer::Point *>::iterator it = points->begin(); it != points->end(); ++it )
        delete (*it);
    delete points;
}
