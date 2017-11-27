/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/
#include <cstdlib>
#include "../include/ReversiPlayer.h"

/*****************************************************************************
 * Function name: userMove                                                   *
 * Input: array for returning result, string for possible options            *
 * Output: user picking according to user input                              *
 ****************************************************************************/
void ReversiPlayer::userMove(int result[2], Board &board) {
    string options = board.possibleMoves(color);

    if (options.empty()) {
        cout << "No possible moves: Play passes to the other player. Press any key to continue..." << endl;
        pressKeyToContinue();
        return;
    }

    cout << flag << ": It's your move." << endl;
    cout << "Your possible moves:\t" << options << endl;
    cout << "Please Enter your Current move row,col:";

    string input;
    bool legal = false;
    vector<ReversiPlayer::Point *> *optionsVec = stringOptionToVector(options);
    // request move from user until legal move assigned to result
    while(!legal) {
        // get request for move from the user
        cin >> input;
        // check input format
        while(!checkMoveInput(input)){
            cout << endl << "incorrect input format. Enter two number separated by a comma, e.g: 2,2:   ";
            cin.clear();
            cin >> input;
        }
        // removing comma
        input.replace(input.find_first_of(","),1," ");
        istringstream in(input);
        in >> result[0] >> result[1];
        // verify that move is legal
        for(vector<ReversiPlayer::Point *>::const_iterator it = optionsVec->begin(); it != optionsVec->end(); ++it)
            if ((*it)->getX() == result[0] && (*it)->getY() == result[1]) {
                legal = true;
                break;
            }
        if(!legal)
            cout << "move is not legal - try again" << endl;
    }
    deletePoints(optionsVec);
}

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
 * Function name: computerMove                                               *
 * Input: array for returning result, string for possible options            *
 * Output: computer picking according to possibilities                       *
 ****************************************************************************/
void ReversiPlayer::computerMove(int result[2], Board &board) {
    string options = board.possibleMoves(color);
    if (options.empty()) {
        cout << "Computer cant move" << endl;
        return;
    }
    // vector of all possible options as points
    vector<ReversiPlayer::Point *> *vecOptions = stringOptionToVector(options);

    // first option is arbitrarily chosen to be the best
    // next the program will loop over the other option and will update the best if needed
    vector<ReversiPlayer::Point *>::const_iterator bestMove = vecOptions->begin();
    int opponentScoreForBestMove = board.OpponentScoreForMove((*bestMove)->getX(),(*bestMove)->getY(),color);

    for(vector<ReversiPlayer::Point *>::const_iterator it = vecOptions->begin(); it != vecOptions->end(); ++it) {
        int temp = board.OpponentScoreForMove((*it)->getX(),(*it)->getY(),color);
        if(temp < opponentScoreForBestMove){
            bestMove = it;
            opponentScoreForBestMove = temp;
        }
    }
    // return best option
    result[0] = (*bestMove)->getX();
    result[1] = (*bestMove)->getY();
    //// optional print to show opponents score after the move
    //// cout << "----------------" << endl << opponentScoreForBestMove << endl << "--------------------" << endl;
    ////
    cout << "computer move: " << "(" <<result[0] << "," << result[1] << ")" << endl << endl;

    deletePoints(vecOptions);
}

/*****************************************************************************
 * Function name: playReversiMove                                            *
 * Input: array to return result, string representing the move options       *
 * Output: initialize player reference and save the color                    *
 ****************************************************************************/
void ReversiPlayer::playReversiMove(int result[2], Board &board){
    result[0] = -1;
    result[1] = -1;
    // check if the player is a computer or human
    if (playerRef.isComputer())
        computerMove(result, board);
    else
        userMove(result, board);
}

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