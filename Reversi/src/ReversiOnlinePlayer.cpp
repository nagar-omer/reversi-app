/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "../include/ReversiOnlinePlayer.h"

ReversiOnlinePlayer::ReversiOnlinePlayer(Player *player, bool color, int serverSocket): ReversiPlayer(player, color) {
    // start TCP connection with the server
    server = serverSocket;
}


/*****************************************************************************
 * Function name: playReversiMove                                            *
 * Input: opponent last move and current game board                          *
 * Output: the players move according to answer from server                  *
 ****************************************************************************/
void ReversiOnlinePlayer::playReversiMove(int *lastMove, Board *board) {
    // wait for online player to make a move.....
    cout << endl << "waiting for online player to make a move..." << endl;
    char move_c[8];
    // wait for online player to make a move.....
    if (read(server, move_c, 8) == -1)
        throw "Connection lost - reading from server";
    // converting string to array of ints for return
    string move_str(move_c);
    size_t comma = move_str.find_first_of(",");
    move_str[comma] = ' ';
    istringstream in(move_str);
    // get final result as ints
    in >> lastMove[0] >> lastMove[1];
    if (lastMove[0] == -1)
        cout << "opponent cant play.." << endl << endl;
    cout << "other player move: " << "(" << lastMove[0] << "," << lastMove[1] << ")" << endl << endl;
}


/*****************************************************************************
 * Function name: GameOver                                                   *
 * Operation: inform server that the game was over and terinate connection   *
 ****************************************************************************/
void ReversiOnlinePlayer::gameOver() {
    write(server, "End", 8);
    close(server);
}

/*****************************************************************************
 * Function name: sendLastMove                                               *
 * Operation: send to the server the opponents last move                     *
 ****************************************************************************/
void ReversiOnlinePlayer::sendLastMove(int *move) {
    // last move is 0,0 only for first move - no one played yet - there is nothing to send to the server
    ostringstream out;
    out << move[0] << "," << move[1];
    // send the last move to the server
    char toSend[8];
    bzero(toSend, 8);
    strcpy(toSend, out.str().c_str());
    if (write(server, toSend, 8) == -1)
        throw "Connection lost - writing to server";
};
