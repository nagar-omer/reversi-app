/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#include "gtest/gtest.h"
#include "../include/ReversiPlayer.h"

TEST(ReversiPlayer_construct, legal_construct){
    Player user = Player("nick");
    Player pc = Player("pc", true);

    ReversiPlayer reversiUser = ReversiPlayer(user, Board::BLACK);
    ReversiPlayer reversiPc = ReversiPlayer(pc, Board::WHITE);

    Player checkUser = reversiUser.getPlayer();
    Player checkPc = reversiPc.getPlayer();

    EXPECT_EQ(checkPc.nick(), "pc");
    EXPECT_EQ(checkUser.nick(), "nick");

    EXPECT_EQ(reversiUser.getColor(), Board::BLACK);
    EXPECT_EQ(reversiPc.getColor(), Board::WHITE);
}

TEST(ReversiPlayer, play){
    Player pc = Player("pc", true);
    ReversiPlayer reversiPcW = ReversiPlayer(pc, Board::WHITE);
    ReversiPlayer reversiPcB = ReversiPlayer(pc, Board::BLACK);
    int move[2];

    Board board = Board();

    // playing some moves
    board.playColor(3, 4, Board::BLACK);
    board.playColor(3, 3, Board::WHITE);
    board.playColor(6, 5, Board::BLACK);
    board.playColor(3, 5, Board::WHITE);
    board.playColor(2, 3, Board::BLACK);

    // getting best option to play from pc - should be (7,5)
    reversiPcW.playReversiMove(move, board);
    EXPECT_EQ(move[0], 7);
    EXPECT_EQ(move[1], 5);

    // continue playing...
    board.playColor(2, 4, Board::WHITE);
    reversiPcB.playReversiMove(move, board);
    EXPECT_EQ(move[0], 1);
    EXPECT_EQ(move[1], 4);

}
