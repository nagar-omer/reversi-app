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
    if (lastMove[0] == -2) {
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

/*****************************************************************************
 * Function name: closeConnection                                            *
 * Operation: inform server that the game was over and terinate connection   *
 ****************************************************************************/
void Reversi::closeConnection(const ReversiPlayer *closingPlayer) const {
    if( closingPlayer->getPlayer()->getSerial() == Player::LOCAL_PLAYER) {
        ostringstream temp;
        temp << "close " << gameName;
        char temp_c[50];
        strcpy(temp_c, temp.str().c_str());
        write(clientSocket, temp_c, 50);
        close(clientSocket);
    }
    else{
        char temp[50] = "END";
        write(clientSocket, temp, 50);
        close(clientSocket);
    }
}

/*****************************************************************************
 * Function name: startGame                                                  *
 * Input: override method for Game "Interface" - starting game               *
 ****************************************************************************/
void Reversi::startGame(){
    reset();
    if (!getSettingsFromUser())
        return;

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

        // black player turn
        cout << endl << *board << endl;
        blackCanPlay = true;
        // try playing move - quit game if not successful
        try {
            blackCanPlay = play(black, lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }
        // if both cant play in a single round then GAME-OVER
        if (playerEndedGame || (!blackCanPlay && !whiteCanPlay)) {
            gameOver = true;
            break;
        }
        try {
            white->sendLastMove(lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }


        cout << endl << *board << endl;
        // try playing move - quit game if not successful
        try{
            whiteCanPlay = true;
            whiteCanPlay = play(white, lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }
        // if both cant play in a single round then GAME-OVER
        if(playerEndedGame || (!blackCanPlay && !whiteCanPlay)) {
            gameOver = true;
            break;
        }
        try {
            black->sendLastMove(lastMove);
        }
        catch(const char *msg){
            cout << endl << " GAME CRASHED" << endl;
            cout << endl << msg << endl << endl;
            return;
        }
    }
    if (playerEndedGame){
        cout << "game stopped!" << endl;
        return;
    }

    // GAME OVER !!
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
        cout << endl << "Error closing connection";
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
        cout << "Tie! there is no winner" << endl;
        return;
    }
    ++(*winner->getPlayer());
    ++(*loser->getPlayer());
    cout << "The winner is:" << endl << *winner->getPlayer() << endl;
};


/*****************************************************************************
 * Function name: connectServer                                              *
 * operation: the function establishes a connection with the game's server   *
 ****************************************************************************/
void Reversi::connectServer() {
    if (connected)
        return;
    cout << "connecting to server ..." << endl;
    // getting information about server's address from the server_address.txt file
    ifstream addressFile;
    addressFile.open("../server_info/server_address.txt");
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
    connected = true;
    cout << "connected to server" << endl;
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
Reversi::Reversi(const vector<Player *> *players) {
    allPlayers = players;
    player1 = player2 = NULL;
    board = NULL;
    rows = cols = clientSocket = 0;
    playerEndedGame = connected = false;
}

/*****************************************************************************
 * Function name: startNewOnlineGame                                         *
 * Operation: initiate players board and server connection for online mode   *
 * for starting a new game                                                   *
 ****************************************************************************/
bool Reversi::startNewOnlineGame(){
    board = new Board(8, 8);
    // initiate player according to colors
    initPlayer(1, getPlayerByID(Player::ONLINE_PLAYER), Board::WHITE);
    initLocalPlayer(2, Board::BLACK);

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
 * Function name: playReversiMove                                            *
 * Input: opponent last move and current game board                          *
 * Output: the players move according to answer from server                  *
 ****************************************************************************/
void Reversi::printExistingGames(){
    char buff[50];
    strcpy(buff, "list_games");
    // ask for game list from server
    if (write(clientSocket, buff, 50) == -1) {
        cout << "Error - cant ask games from server" << endl;
    }
    bzero(buff, 50);
    // wait for answer and print it
    if (read(clientSocket, buff, 50) == -1) {
        cout << "Error - cant get games from server" << endl;
    }
    string games(buff);
    cout << "available games:"<< endl << games << endl;
    // disconnect server
    close(clientSocket);
    connected = false;
}

/*****************************************************************************
 * Function name: joinGame                                                   *
 * Operation: initiate players board and server connection for online mode   *
 * for joining existing game                                                 *
 ****************************************************************************/
bool Reversi::joinGame(){
    // initiate player according to colors
    board = new Board(8, 8);
    initPlayer(1, getPlayerByID(Player::ONLINE_PLAYER), Board::BLACK);
    initLocalPlayer(2, Board::WHITE);

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
bool Reversi::setOnline() {

    // connect to server to get messages from the online player
    try {
        connectServer();
    }
    catch (const char *msg) {
        throw msg;
    }
    cout << endl;

    // print menu for online mode
    cout << "choose option:" << endl;
    cout << "\t0.\t back to main menu" << endl;
    cout << "\t1.\t open new game" << endl;
    cout << "\t2.\t print existing games" << endl;
    cout << "\t3.\t join existing game" << endl;

    int option;
    cin >> option;

    // switch according to users choice
    switch (option){

        case 0: // BACK
            return false;
        case 1:
            return startNewOnlineGame();
        case 2:
            printExistingGames();
            return false;
        case 3:
            return joinGame();
        default:
            cout << "wrong input" << endl;
            return false;
    }
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
 * Function name: initLocalPlayer                                            *
 * Input: playerNum = 1/2, color = BLACK/WHITE                               *
 * Output: initiate first/second player as local player                      *
 ****************************************************************************/
bool Reversi::initLocalPlayer(int playerNum, bool color){
    string input;
    Player *tempPlayer;
    if (playerNum == 2 && player1 == NULL) {
        cout << "Error - init player 2 before player 1" << endl;
        return false;
    }
    if (playerNum == 1) {
        cout << "enter player ID for first player" << endl;
        // Enter first player by id
        cout << "enter player ID for first player" << endl;
        cin >> input;
        // id 1/2 reserved for pc and online players
        while (!isNumber(input) || atoi(input.c_str()) == Player::PC || atoi(input.c_str()) == Player::ONLINE_PLAYER ||
                (tempPlayer = getPlayerByID(atoi(input.c_str()))) == NULL) {
            cout << "ID not exist - try again" << endl;
            cin >> input;
        }
        initPlayer(1, tempPlayer, color);
    }
    else {
        if (player1->getPlayer()->getSerial() == Player::LOCAL_PLAYER)
            cout << "enter player ID for second player" << endl;
        else
            cout << "enter player ID for local player" << endl;
        cin >> input;
        // id 1/2 reserved for pc and online players
        while (!isNumber(input) || atoi(input.c_str()) == Player::PC || atoi(input.c_str()) == Player::ONLINE_PLAYER ||
               (tempPlayer = getPlayerByID(atoi(input.c_str()))) == NULL
               || atoi(input.c_str()) == player1->getPlayer()->getSerial()) {
            cout << "ID not exist - try again" << endl;
            cin >> input;
        }
        initPlayer(2, tempPlayer, color);
    }

};

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

    int gameType, id1 = 0, id2;
    cin >> gameType;
    Player *tempPlayer = NULL;
    // initiate first player according to game type
    switch (gameType) {
        case 0: // BACK TO MAIN MENU
            return false;
        case Player::PC:
            initPlayer(1, getPlayerByID(Player::PC), Board::BLACK);
            break;
        case Player::ONLINE_PLAYER:
            return setOnline();
        case Player::LOCAL_PLAYER:
            if ( allPlayers->size() < 4){
                cout << "create 2 players before starting local 2 players game .. " << endl << endl;
                return false;
            }
            initLocalPlayer(1, Board::BLACK);
            break;
        default:
            cout << "wrong input" << endl;
            return false;
    }

    initLocalPlayer(2, Board::WHITE);

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
        case 0: // BACK TO MAIN MENU
            return false;
        case 1: {
            rows = cols = 6;
            break;
        }
        case 2: {
            rows = cols = 8;
            break;
        }
        case 3: {
            rows = cols = 10;
            break;
        }
        default:
            cout << "wrong input!";
            return false;
    }

    try{
        // create board with available size
        board = new Board(rows, cols);
    }
    catch(const char *msg){
        throw msg;
    }

    return true;
}

void Reversi::reset(){
    delete(player1);
    delete(player2);
    delete(board);
    player1 = player2 = NULL;
    board = NULL;
    rows = cols = 0;
    playerEndedGame = false;
}