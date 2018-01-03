/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "../include/PlayGround.h"

/*****************************************************************************
 * Function name: startReversiGame                                           *
 * Operation: creates reversi object and starts the game                     *
 ****************************************************************************/
void PlayGround::startReversiGame() {
    Reversi reversi(players);
    reversi.go();
}


/*****************************************************************************
 * Function name: addPlayer                                                  *
 * Operation: the function asks from the user to enter new Player            *
 ****************************************************************************/
void PlayGround::addPlayer() {
    cout << "Enter Player Nick Name" << endl;
    string nick;
    cin >> nick;
    players.push_back(new Player(nick, Player::LOCAL_PLAYER));
    cout << endl << "player added:" << endl << *players.back() << endl;
}


/*****************************************************************************
 * Function name: go                                                         *
 * Operation: shows th Main Menu                                             *
 ****************************************************************************/
void PlayGround::go(){
    bool exitMenue = false;
    while(!exitMenue) {
        cout << "Main Menu" << endl;
        cout << "\t1.\t Enter new player" << endl;
        cout << "\t2.\t Start new Game" << endl;
        cout << "\tother.\t Exit" << endl;
        int pick;
        cin >> pick;
        switch (pick) {
            case NEW_PLAYER: {
                addPlayer();
                break;
            }
            case NEW_GAME: {
                startReversiGame();
                break;
            }
            default:
                exitMenue = true;
        }
    }

};

/*****************************************************************************
 * Function name: getPlayerByID                                              *
 * Output: returns ptr for player by his ID                                  *
 ****************************************************************************/
Player *PlayGround::getPlayerByID(int id){
    for(vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
        if(id == (*it)->getSerial())
            return (*it);
    return NULL;
}

/*****************************************************************************
 * Function name: default destructor                                         *
 ****************************************************************************/
PlayGround::~PlayGround() {
    for(vector<Player *>::iterator it = players.begin(); it != players.end(); ++it )
        delete (*it);
}
