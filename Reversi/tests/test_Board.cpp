#include "gtest/gtest.h"
#include "../include/Board.h"

// test board constructor
TEST(Board_constructor, legal_values){
    Board board = Board();
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getRows(), 8);

    board = Board(6, 6);
    EXPECT_EQ(board.getCols(), 6);
    EXPECT_EQ(board.getRows(), 6);

    board = Board(2, 2);
    EXPECT_EQ(board.getCols(), 2);
    EXPECT_EQ(board.getRows(), 2);
}

TEST(Board_constructor, ilegal_values){
    Board board = Board(1, 1);
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getRows(), 8);

    board = Board(-5, -1);
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getRows(), 8);
}