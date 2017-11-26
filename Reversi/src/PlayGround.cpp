/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#include "../include/PlayGround.h"

/*****************************************************************************
 * Function name: startReversiGame                                           *
 * Operation: creates reversi object and starts the game                     *
 ****************************************************************************/
void PlayGround::startReversiGame(){
    // Enter first player by id
    cout << "enter player ID for first player (1 for Computer)" << endl;
    int id1;
    cin >> id1;
    Player *player1 = NULL;
    while((player1 = getPlayerByID(id1)) == NULL){
        cout << "ID not exist - try again" << endl;
        cin >> id1;
    }

    // Enter second player by id
    cout << "enter player ID for second player (1 for Computer)" << endl;
    int id2;
    cin >> id2;
    Player *player2 = NULL;
    while( id1 == id2 || (player2 = getPlayerByID(id2)) == NULL ){
        cout << "ID not exist / same as first player - try again" << endl;
        cin >> id2;
    }

    // Board size
    cout << "Board size" << endl;
    cout << "1. 6X6 " << endl;
    cout << "2. 8X8 " << endl;
    cout << "3. 10X10 " << endl;
    cout << "default. 8X8 " << endl;
    int size;
    cin >> size;
    switch(size){
        case 1: {
            size = 6;
            break;
        }
        case 2: {
            size = 8;
            break;
        }
        case 3: {
            size = 10;
            break;
        }
        default:
            size = 8;
    }

    Reversi reversi(*player1,*player2,size,size);
    reversi.startGame();
}

/*****************************************************************************
 * Function name: startGame                                                  *
 * Operation: asks from user to choose a game and stars the game             *
 ****************************************************************************/
void PlayGround::startGame(){
    int id;
    cout << "Pick a game:" << endl;
    cout << "1. Reversi" << endl;
    cin >> id;
    switch (id) {
        case REVERSI: {
            startReversiGame();
            break;
        }
        default:
            cout << "No such option";
            return;
    }
}


/*****************************************************************************
 * Function name: addPlayer                                                  *
 * Operation: the function asks from the user to enter new Player            *
 ****************************************************************************/
void PlayGround::addPlayer() {
    cout << "Enter Player Nick Name" << endl;
    string nick;
    cin >> nick;
    players.push_back(new Player(nick));
    cout << *players.back() << endl;
}


/*****************************************************************************
 * Function name: go                                                         *
 * Operation: shows th Main Menu                                             *
 ****************************************************************************/
void PlayGround::go(){
    bool exitMenue = false;
    while(!exitMenue) {
        cout << "Main Menue" << endl;
        cout << "1. Enter new player" << endl;
        cout << "2. Start new Game" << endl;
        cout << "other. Exit" << endl;
        int pick;
        cin >> pick;
        switch (pick) {
            case NEW_PLAYER: {
                addPlayer();
                break;
            }
            case NEW_GAME: {
                startGame();
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