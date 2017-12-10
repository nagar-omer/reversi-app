/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/
#include "../include/ReversiLocalPlayer.h"


/*****************************************************************************
 * Function name: userMove                                                   *
 * Input: array for returning result, string for possible options            *
 * Output: user picking according to user input                              *
 ****************************************************************************/
void ReversiLocalPlayer::playReversiMove(int *result, Board *board) {
    result[0] = -1;
    result[1] = -1;

    string options = board->possibleMoves(color);

    if (options.empty()) {
        cout << "No possible moves: Play passes to the other player. Press any key to continue..." << endl;
        pressKeyToContinue();
        return;
    }

    cout << flag << ": It's your move." << endl;
    cout << "Your possible moves:\t" << options << endl;
    cout << "Please Enter your Current move row,col:\t";

    string input;
    bool legal = false;
    vector<ReversiPlayer::Point *> *optionsVec = stringOptionToVector(options);
    // request move from user until legal move assigned to result
    while(!legal) {
        // get request for move from the user
        cin >> input;
        // check input format
        while(!checkMoveInput(input)){
            cout << endl << "incorrect input format. Enter two number separated by a comma, e.g: 2,2:\t";
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
            cout << "move is not legal - try again\t";
    }
    deletePoints(optionsVec);
};
