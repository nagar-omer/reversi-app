/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/

#include "../include/Reversi.h"

/*****************************************************************************
 * Function name: play                                                       *
 * Input: RevesiPlayer - player (not Player)                                 *
 * Output: play move for requested player                                    *
 ****************************************************************************/
bool Reversi::play(ReversiPlayer *player, int lastMove[2]){
    // try request move from player
    try {
        player->playReversiMove(lastMove, board);
    }
    catch (const char *msg){
        throw msg;
    }
    // sign for End Game
    if (lastMove[0] == PLAYER_ENDED_GAME) {
        closeConnection(player);
        playerEndedGame = true;
        return false;
    }
        // no legal move
    if (lastMove[0] == -1)
        return false;
    // Play the requested move
    board->playColor(lastMove[0],lastMove[1],player->getColor());
    return true;
}

void Reversi::go(){
    if(getSettingsFromUser())
        startGame();
}

/*****************************************************************************
 * Function name: closeConnection                                            *
 * Operation: inform server that the game was over and terinate connection   *
 ****************************************************************************/
void Reversi::closeConnection(const ReversiPlayer *closingPlayer) const {
    // if the closing player is the local player and its an online game
    if( closingPlayer->getPlayer()->getSerial() == Player::LOCAL_PLAYER
            && player1->getPlayer()->getSerial() == Player::ONLINE_PLAYER) {
        ostringstream temp;
        // send close <name>
        temp << "close " << gameName;
        char temp_c[50];
        strcpy(temp_c, temp.str().c_str());
        write(clientSocket, temp_c, 50);
        close(clientSocket);
    }
    // if the server sent END
    else if( closingPlayer->getPlayer()->getSerial() == Player::ONLINE_PLAYER ) {
        char temp[50] = "END";
        // try sending back END and close conection
        write(clientSocket, temp, 50);
        close(clientSocket);
    }
}

/*****************************************************************************
 * Function name: startGame                                                  *
 * Input: override method for Game "Interface" - starting game               *
 ****************************************************************************/
void Reversi::startGame(){
    ReversiPlayer *black, *white;
    // get black and white players
    if (player1->getColor()) {
        black = player1;
        white = player2;
    }
    else{
        black = player2;
        white = player1;
    }

    // game flow....
    int lastMove[2] = {0, 0};
    bool gameOver = false, blackCanPlay = true, whiteCanPlay = false;
    while(!gameOver){

        /******************************  BLACK PLAYER TURN  ******************************/
        cout << endl << *board << endl;
        blackCanPlay = true;
        // try playing move - quit game if not successful
        try {
            blackCanPlay = play(black, lastMove);
            if (playerEndedGame)
                return;
            white->sendLastMove(lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }
        // if both cant play in a single round then GAME-OVER
        if(!blackCanPlay && !whiteCanPlay) {
            gameOver = true;
            break;
        }

        /******************************  WHITE PLAYER TURN  ******************************/
        cout << endl << *board << endl;
        // try playing move - quit game if not successful
        try{
            whiteCanPlay = true;
            whiteCanPlay = play(white, lastMove);
            if (playerEndedGame)
                return;
            black->sendLastMove(lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }

        // if both cant play in a single round then GAME-OVER
        if(!blackCanPlay && !whiteCanPlay) {
            gameOver = true;
            break;
        }
    }

    /****************************** GAME OVER !  ******************************/
    try {
        if(player2->getColor() == Board::BLACK)
            // close with close gameName
            closeConnection(player2);
        else {
            char buff[50];
            // expected to get END from server
            read(clientSocket, buff, 50);
            // close with END
            closeConnection(player1);
        }
    }
    catch(const char *msg){
        cout << endl << "Error closing connection" << endl << endl;
    }

    cout << endl << endl;
    cout << "------------------------------------------------------------------";
    cout << endl << endl;
    // check which player is the winner and print results
    ReversiPlayer *winner, *loser;
    int score1 = board->score(Board::WHITE), score2 = board->score(Board::BLACK);
    if (score1 > score2) {
        winner = white;
        loser = black;
    }
    else if (score1 < score2) {
        winner = black;
        loser = white;
    }
    else{
        cout << "Tie!" << endl << endl;
        return;
    }
    ++(*winner->getPlayer());
    --(*loser->getPlayer());
    cout << "The winner is:" << endl << *winner->getPlayer() << endl;
};


/*****************************************************************************
 * Function name: connectServer                                              *
 * operation: the function establishes a connection with the game's server   *
 ****************************************************************************/
void Reversi::connectServer() {
    // getting information about server's address from the server_address.txt file
    ifstream addressFile;
    addressFile.open("server_info/server_address.txt");
    string key, stringServerIP;
    int serverPort;
    addressFile >> key >> stringServerIP;
    addressFile >> key >> serverPort;
    const char *serverIP = stringServerIP.c_str();

    // init socket as internet TCP
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
        throw "Error - cant open socket for client";

    // convert ip string from string to binary form
    struct in_addr server_address;
    bzero((char *)&server_address, sizeof(in_addr));
    if (!inet_aton(serverIP, &server_address))
        throw "Error - cant convert IP address";

    // get hostnet struct using the IP address of the server
    struct hostent *server = gethostbyaddr((const void *)&server_address, sizeof(server_address), AF_INET);
    if(server == NULL)
        throw "Error - cant get hostnent for IP address";

    // initiate serverAddress sockaddr_in
    struct sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, (size_t)server->h_length);
    serverAddress.sin_port = htons((uint16_t)serverPort);
    serverAddress.sin_family = AF_INET;

    // try connecting to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw "Error - cant connect to server";
}


/*****************************************************************************
 * Function name: initPlayer                                                 *
 * operation: the function initiate a reversiPlayer object acording to       *
 * player type                                                               *
 ****************************************************************************/
void Reversi::initPlayer(int playerNum, Player *player, bool color) {
    int type = player->getPlayerType();
    switch (type){
        case Player::LOCAL_PLAYER:
            if (playerNum == 1)
                player1 = new ReversiLocalPlayer(player, color);
            else
                player2 = new ReversiLocalPlayer(player, color);
            break;
        case Player::PC:
            if (playerNum == 1)
                player1 = new ReversiPcPlayer(player, color);
            else
                player2 = new ReversiPcPlayer(player, color);
            break;
        case Player::ONLINE_PLAYER:
            if (playerNum == 1)
                player1 = new ReversiOnlinePlayer(player, color, clientSocket);
            else
                player2 = new ReversiOnlinePlayer(player, color, clientSocket);
            break;
        default:
            if (playerNum == 1)
                player1 = new ReversiLocalPlayer(player, color);
            else
                player2 = new ReversiLocalPlayer(player, color);

    }
}

/*****************************************************************************
 * Function name: default constructor - initiate connection players and board*
 ****************************************************************************/
Reversi::Reversi(const vector<Player *> &players):allPlayers(players) {
    player1 = player2 = NULL;
    board = NULL;
    gameName = "";
    playerEndedGame = false;
}

/*****************************************************************************
 * Function name: getSettingsFromUser                                        *
 * Output: main menu for reversi game                                        *
 ****************************************************************************/
bool Reversi::getSettingsFromUser(){

    cout << "choose game type:" << endl;
    cout << "\t0.\t Back to main menu" << endl;
    cout << "\t1.\t play against PC" << endl;
    cout << "\t2.\t online mode" << endl;
    cout << "\t3.\t 2 player local game" << endl;

    int onlineOption, gameType, id1 = 0, id2 = 0, boardSiz = 4;
    cin >> gameType;
    bool color2 = Board::BLACK;
    // initiate first player according to game type
    switch (gameType) {
        case 0: // BACK TO MAIN MENU
            return false;
        case Player::PC:
            if (allPlayers.size() < 3){
                cout << "create player before starting game" << endl << endl;
                return false;
            }
            id1 = Player::PC;
            id2 = getLocalPlayerIndex(false);
            boardSiz = getBoardSize();
            if (boardSiz == 0)
                return false;
            break;
        case Player::ONLINE_PLAYER:
            if (allPlayers.size() < 3){
                cout << "create player before starting game" << endl << endl;
                return false;
            }

            // init player and start/join game
            id1 = Player::ONLINE_PLAYER;
            id2 = getLocalPlayerIndex(false);

            // get option from user
            onlineOption = getOnlineOption();
            // if join change color for local player
            if (onlineOption == ONLINE_JOIN)
                color2 = Board::WHITE;
            // if user want to get list dont init players
            if(!setOnline(onlineOption))
                return false;
            break;

        case Player::LOCAL_PLAYER:
            if (allPlayers.size() < 4){
                cout << "create 2 players before starting 2 players local game" << endl << endl;
                return false;
            }
            id2 = getLocalPlayerIndex(true);
            id1 = getLocalPlayerIndex(true, id2, true);
            boardSiz = getBoardSize();
            if (boardSiz == 0)
                return false;
            break;
        default:
            cout << "wrong input" << endl;
            return false;
    }

    initPlayer(1, getPlayerByID(id1), !color2);
    initPlayer(2, getPlayerByID(id2), color2);
    board = new Board(boardSiz, boardSiz);
    return true;
}

/*****************************************************************************
 * Function name: isNumber                                                   *
 * Input: string                                                             *
 * Output: true/false -> number/NAN                                          *
 ****************************************************************************/
bool Reversi::isNumber(string &s){
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

/*****************************************************************************
 * Function name: getBoardSize                                               *
 * Output: get board size from user                                          *
 ****************************************************************************/
int Reversi::getBoardSize(){
    // Board size
    cout << "choose preferred board size" << endl;
    cout << "\t0.\t Back to main menu" << endl;
    cout << "\t1.\t 6X6 " << endl;
    cout << "\t2.\t 8X8 " << endl;
    cout << "\t3.\t 10X10 " << endl;
    cout << "\tdefault.\t 8X8 " << endl;
    string size_str;
    int size = 4;
    cin >> size_str;
    if (isNumber(size_str))
        size = atoi(size_str.c_str());
    switch (size) {
        case 0: // BACK TO MAIN MENU
            return 0;
        case 1: {
            return 6;
        }
        case 2: {
            return 8;
        }
        case 3: {
            return 10;
        }
        default:
            cout << "wrong input!";
            return 0;
    }
}

/*****************************************************************************
 * Function name: initLocalPlayer                                            *
 * Input: playerNum = 1/2, color = BLACK/WHITE                               *
 * Output: initiate first/second player as local player                      *
 ****************************************************************************/
int Reversi::getLocalPlayerIndex(bool is2PlayersLocal, int id1, bool isSecondPlayer){
    string input;

    if (is2PlayersLocal && !isSecondPlayer)
        cout << "enter player ID for first player" << endl;
    else if (isSecondPlayer)
        cout << "enter player ID for second player" << endl;
    else
        cout << "enter player ID for local player" << endl;
    // Enter first player by id
    cin >> input;
    // id 1/2 reserved for pc and online players
    while (!isNumber(input) || atoi(input.c_str()) == Player::PC || atoi(input.c_str()) == Player::ONLINE_PLAYER ||
           getPlayerByID(atoi(input.c_str())) == NULL || atoi(input.c_str()) == id1) {
        cout << "ID not exist - try again" << endl;
        cin >> input;
    }
    return atoi(input.c_str());
};

/*****************************************************************************
 * Function name: setOnline                                                  *
 * Output: navigation for online mode                                        *
 ****************************************************************************/
int Reversi::getOnlineOption() {

    // print menu for online mode
    cout << "choose option:" << endl;
    cout << "\t0.\t back to main menu" << endl;
    cout << "\t1.\t open new game" << endl;
    cout << "\t2.\t print existing games" << endl;
    cout << "\t3.\t join existing game" << endl;

    string option;
    cin >> option;

    if (!isNumber(option)) {
        cout << "wrong input" << endl;
        return 0;
    }
    return atoi(option.c_str());
}

/*****************************************************************************
 * Function name: playReversiMove                                            *
 * Input: opponent last move and current game board                          *
 * Output: the players move according to answer from server                  *
 ****************************************************************************/
void Reversi::printExistingGames(){
    char buff[50];
    strcpy(buff, "list_games");
    // ask for game list from server
    if (write(clientSocket, buff, 50) == -1) {
        cout << "Error - cant ask games from server" << endl << endl;
    }
    bzero(buff, 50);
    // wait for answer and print it
    if (read(clientSocket, buff, 50) == -1) {
        cout << "Error - cant get games from server" << endl << endl;
    }
    string games(buff);
    cout << "available games:"<< endl << games << endl << endl;
    // disconnect server
    close(clientSocket);
}

/*****************************************************************************
 * Function name: startNewOnlineGame                                         *
 * Operation: initiate players board and server connection for online mode   *
 * for starting a new game                                                   *
 ****************************************************************************/
bool Reversi::startNewOnlineGame(){
    string gameName;
    char buff[50] = "start ";
    // get name for new game from user
    cout << "enter name for new game" << endl;
    cin >> gameName;
    strcpy(&buff[6], gameName.c_str());
    // ask from server to open new game with requested name
    if (write(clientSocket, buff, 50) == -1) {
        cout << "Error - writing to server on start new game" << endl;
        return false;
    }
    cout << "waiting fo server to start game..." << endl;
    // get answer from user - is name already taken?
    if (read(clientSocket, buff, 50) == -1) {
        cout << "Error - cant read on start new game" << endl;
        return false;
    }
    int flag = atoi(buff);
    if (flag == -1) {
        cout << "game already exists" << endl;
        return false;
    }
    // getting local player's color from server
    cout << "new game with the name: " << gameName << " has created" << endl;
    this->gameName = gameName;
    return true;
}


/*****************************************************************************
 * Function name: joinGame                                                   *
 * Operation: initiate players board and server connection for online mode   *
 * for joining existing game                                                 *
 ****************************************************************************/
bool Reversi::joinGame(){
    string gameName;
    char buff[50] = "join ";
    // get name for new game from user
    cout << "enter the name of the game you want to join to." << endl;
    cin >> gameName;
    strcpy(&buff[5], gameName.c_str());
    // ask from server to open new game with requested name
    if (write(clientSocket, buff, 50) == -1) {
        cout << "Error - writing to server on start new game" << endl;
        return false;
    }
    // get answer from user - is name already taken?
    if (read(clientSocket, buff, 50) == -1) {
        cout << "Error - cant read on join game" << endl;
        return false;
    }
    int flag = atoi(buff);
    if (flag == -1) {
        cout << "game doesn't exist" << endl;
        return false;
    }
    this->gameName = gameName;
    cout << "successfully joined game!" << endl;
    return true;


}

/*****************************************************************************
 * Function name: setOnline                                                  *
 * Output: navigation for online mode                                        *
 ****************************************************************************/
bool Reversi::setOnline(int option) {

    // connect to server to get messages from the online player
    try {
        connectServer();
    }
    catch (const char *msg) {
        cout << msg << endl << endl;
        return false;
    }

    // switch according to users choice
    switch (option){

        case ONLINE_BACK: // BACK
            return false;
        case ONLINE_NEW:
            return startNewOnlineGame();
        case ONLINE_LIST:
            printExistingGames();
            return false;
        case ONLINE_JOIN:
            return joinGame();
        default:
            cout << "wrong input" << endl;
            return false;
    }
}
