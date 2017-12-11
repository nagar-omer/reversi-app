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
    // Board size
    cout << "choose preferred board size" << endl;
    cout << "\t0.\t Back to main menu" << endl;
    cout << "\t1.\t 6X6 " << endl;
    cout << "\t2.\t 8X8 " << endl;
    cout << "\t3.\t 10X10 " << endl;
    cout << "\tdefault.\t 8X8 " << endl;
    int size;
    cin >> size;
    switch (size) {
        case BACK:
            return;
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

    cout << "choose game type:" << endl;
    cout << "\t0.\t Back to main menu" << endl;
    cout << "\t1.\t play against PC" << endl;
    cout << "\t2.\t 2 player online game" << endl;
    cout << "\t3.\t 2 player local game" << endl;
    cout << "\tdefault.\t play against PC" << endl;

    int gameType, id1 = 0, id2;
    cin >> gameType;
    Player *player1 = NULL;
    // initiate first player acording to game type
    switch (gameType) {
        case BACK:
            return;
        case Player::LOCAL_PLAYER:
            if ( players.size() < 4){
                cout << "create 2 players before starting local 2 players game .. " << endl << endl;
                return;
            }
            // Enter first player by id
            cout << "enter player ID for first player" << endl;
            cin >> id1;
            // id 1/2 reserved for pc and online players
            while (id1 == Player::PC || id1 == Player::ONLINE_PLAYER || (player1 = getPlayerByID(id1)) == NULL) {
                cout << "ID not exist - try again" << endl;
                cin >> id1;
            }
            cout << "enter player ID for second player" << endl;
            break;
        case Player::PC:
            player1 = getPlayerByID(Player::PC);
            cout << "enter player ID" << endl;
            break;
        case Player::ONLINE_PLAYER:
            player1 = getPlayerByID(Player::ONLINE_PLAYER);
            cout << "enter player ID" << endl;
            break;
        default:
            player1 = getPlayerByID(Player::PC);
            cout << "enter player ID" << endl;
            break;
    }


    // Enter second player by id
    cin >> id2;
    Player *player2 = NULL;
    // id 1/2 reserved for pc and online players
    while (id2 == Player::PC || id2 == Player::ONLINE_PLAYER || id1 == id2 || (player2 = getPlayerByID(id2)) == NULL) {
        cout << "ID not exist / same as first player - try again" << endl;
        cin >> id2;
    }

    try {
        Reversi reversi(player1, player2, size, size);
        reversi.startGame();
    }
    catch (const char *msg){
        cout << endl << "CANT START GAME !" << endl;
        cout << endl << msg << endl << endl;
    }
}

/*****************************************************************************
 * Function name: startGame                                                  *
 * Operation: asks from user to choose a game and stars the game             *
 ****************************************************************************/
void PlayGround::startGame(){
    if ( players.size() < 3){
        cout << "create a player before starting a game .. " << endl << endl;
        return;
    int id;
    cout << "Pick a game:" << endl;
    cout << "\t0.\t Back" << endl;
    cout << "\t1.\t Reversi" << endl;
    cin >> id;
    switch (id) {
        case BACK:
            return;
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
    players.push_back(new Player(nick, Player::LOCAL_PLAYER));
    cout << *players.back() << endl;
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
