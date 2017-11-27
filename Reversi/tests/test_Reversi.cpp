#include "gtest/gtest.h"
#include "../include/Reversi.h"

TEST(Reversi_construct, legal_input){
    Player pc = Player("pc", true);
    Player user = Player("user");
    Reversi reversi = Reversi(pc, user, 6, 6);
    ReversiPlayer p1 = reversi.getPlayer1();
    ReversiPlayer p2 = reversi.getPlayer2();
    Board board = reversi.getBoard();

    EXPECT_EQ(p1.getColor(), Board::WHITE);
    EXPECT_EQ(p2.getColor(), Board::BLACK);
    EXPECT_EQ(p1.getPlayer().nick(), "pc");
    EXPECT_EQ(p2.getPlayer().nick(), "user");
    EXPECT_EQ(board.getRows(), 6);
    EXPECT_EQ(board.getCols(), 6);
    EXPECT_EQ(board.getColor(3,3), Board::WHITE);
    EXPECT_EQ(board.getColor(4,4), Board::WHITE);
    EXPECT_EQ(board.getColor(3,4), Board::BLACK);
    EXPECT_EQ(board.getColor(4,3), Board::BLACK);
}

TEST(Reversi_construct, illegal_input){
    Player pc = Player("pc", true);
    Player user = Player("user");
    Reversi reversi = Reversi(pc, user, -1, 2);
    ReversiPlayer p1 = reversi.getPlayer1();
    ReversiPlayer p2 = reversi.getPlayer2();
    Board board = reversi.getBoard();

    EXPECT_EQ(p1.getColor(), Board::WHITE);
    EXPECT_EQ(p2.getColor(), Board::BLACK);
    EXPECT_EQ(p1.getPlayer().nick(), "pc");
    EXPECT_EQ(p2.getPlayer().nick(), "user");
    EXPECT_EQ(board.getRows(), 8);
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getColor(4,4), Board::WHITE);
    EXPECT_EQ(board.getColor(5,5), Board::WHITE);
    EXPECT_EQ(board.getColor(4,5), Board::BLACK);
    EXPECT_EQ(board.getColor(5,4), Board::BLACK);
}