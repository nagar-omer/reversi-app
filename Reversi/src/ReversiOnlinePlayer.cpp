/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "../include/ReversiOnlinePlayer.h"

ReversiOnlinePlayer::ReversiOnlinePlayer(Player *player, bool color, int serverSocket): ReversiPlayer(player, color) {
    server = serverSocket;
}

void ReversiOnlinePlayer::playReversiMove(int *lastMove, Board &board) {
    char move_c[8];
    // wait for online player to make a move.....
    read(server, move_c, 8);
    // converting string to array of ints for return
    string move_str(move_c);
    size_t comma = move_str.find_first_of(",");
    move_str[comma] = ' ';
    istringstream in(move_str);
    // get final result as ints
    in >> lastMove[0] >> lastMove[1];
}

void ReversiOnlinePlayer::gameOver() {
    write(server, "End", 8);
    close(server);
}

void ReversiOnlinePlayer::sendLastMove(int *move) {
    // last move is 0,0 only for first move - no one played yet - there is nothing to send to the server
    ostringstream out;
    out << move[0] << "," << move[1];
    // send the last move to the server
    write(server, out.str().c_str(), 8);
};