/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#include "../include/Reversi.h"

/*****************************************************************************
 * Function name: play                                                       *
 * Input: RevesiPlayer - player (not Player)                                 *
 * Output: play move for requested player                                    *
 ****************************************************************************/
bool Reversi::play(ReversiPlayer player){
    int playRequest[2];
    player.playReversiMove(playRequest, board);
    // no legal move
    if (playRequest[0] == -1)
        return false;
    // Play the requested move
    board.playColor(playRequest[0],playRequest[1],player.getColor());
    return true;
}

/*****************************************************************************
 * Function name: startGame                                                  *
 * Input: override method for Game "Interface" - starting game               *
 ****************************************************************************/
void Reversi::startGame(){
    bool gameOver = false, blackCanPlay, whiteCanPlay;
    while(!gameOver){
        // white player turn
        whiteCanPlay = true;
        cout << board;
        whiteCanPlay = play(player1);
        // if both cant play in a single round then GAME-OVER
        if(!blackCanPlay && !whiteCanPlay) {
            gameOver = true;
            break;
        }

        // black player turn
        cout << board;
        blackCanPlay = true;
        blackCanPlay = play(player2);
        // if both cant play in a single round then GAME-OVER
        if(!blackCanPlay && !whiteCanPlay)
            gameOver = true;
    }
    cout << endl << endl;
    cout << "------------------------------------------------------------------";
    cout << endl << endl;
    // check which player is the winner and print results
    ReversiPlayer *winner, *loser;
    int score1 = board.score(Board::WHITE), score2 = board.score(Board::BLACK);
    if (score1 > score2) {
        winner = &player1;
        loser = &player2;
    }
    else if (score1 < score2) {
        winner = &player2;
        loser = &player1;
    }
    else{
        cout << "Tie! there is no winner" << endl;
        return;
    }
    ++(winner->getPlayer());
    ++(loser->getPlayer());
    cout << "The winner is:" << endl << winner->getPlayer() << endl;
};
