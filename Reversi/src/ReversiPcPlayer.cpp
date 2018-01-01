/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "../include/ReversiPcPlayer.h"

/*****************************************************************************
 * Function name: playReversiMove                                            *
 * Input: array for returning result, string for possible options            *
 * Output: computer picking according to possibilities                       *
 ****************************************************************************/
void ReversiPcPlayer::playReversiMove(int *result, Board *board) const{
    result[0] = -1;
    result[1] = -1;

    string options = board->possibleMoves(color);
    if (options.empty()) {
        cout << "Computer cant move" << endl;
        return;
    }
    // vector of all possible options as points
    vector<ReversiPlayer::Point *> *vecOptions = stringOptionToVector(options);

    // first option is arbitrarily chosen to be the best
    // next the program will loop over the other option and will update the best if needed
    vector<ReversiPlayer::Point *>::const_iterator bestMove = vecOptions->begin();
    int opponentScoreForBestMove = board->OpponentScoreForMove((*bestMove)->getX(),(*bestMove)->getY(),color);

    for(vector<ReversiPlayer::Point *>::const_iterator it = vecOptions->begin(); it != vecOptions->end(); ++it) {
        int temp = board->OpponentScoreForMove((*it)->getX(),(*it)->getY(),color);
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
