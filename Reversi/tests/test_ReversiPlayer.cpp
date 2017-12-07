/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/


#include "gtest/gtest.h"
#include "../include/ReversiPlayer.h"
#include "../include/ReversiPcPlayer.h"
#include "../include/ReversiLocalPlayer.h"

TEST(ReversiPlayer_construct, legal_construct){
    Player user = Player("nick", Player::LOCAL_PLAYER);
    Player pc = Player("pc", Player::PC);

    ReversiPlayer *reversiUser = new ReversiLocalPlayer(&user, Board::BLACK);
    ReversiPlayer *reversiPc = new ReversiPcPlayer(&pc, Board::WHITE);

    Player *checkUser = reversiUser->getPlayer();
    Player *checkPc = reversiPc->getPlayer();

    EXPECT_EQ(checkPc->nick(), "pc");
    EXPECT_EQ(checkUser->nick(), "nick");

    EXPECT_EQ(reversiUser->getColor(), Board::BLACK);
    EXPECT_EQ(reversiPc->getColor(), Board::WHITE);

    delete(reversiUser);
    delete(reversiPc);

}

TEST(ReversiPlayer, play){
    Player pc = Player("pc", Player::PC);
    ReversiPlayer *reversiPcW = new ReversiPcPlayer(&pc, Board::WHITE);
    ReversiPlayer *reversiPcB = new ReversiPcPlayer(&pc, Board::BLACK);
    int move[2];

    Board board = Board();

    // playing some moves
    board.playColor(3, 4, Board::BLACK);
    board.playColor(3, 3, Board::WHITE);
    board.playColor(6, 5, Board::BLACK);
    board.playColor(3, 5, Board::WHITE);
    board.playColor(2, 3, Board::BLACK);

    // getting best option to play from pc - should be (7,5)
    reversiPcW->playReversiMove(move, board);
    EXPECT_EQ(move[0], 7);
    EXPECT_EQ(move[1], 5);

    // continue playing...
    board.playColor(2, 4, Board::WHITE);
    reversiPcB->playReversiMove(move, board);
    EXPECT_EQ(move[0], 1);
    EXPECT_EQ(move[1], 4);

    delete(reversiPcW);
    delete(reversiPcB);
}
