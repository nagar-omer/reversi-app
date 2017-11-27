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

TEST(Board_constructor, illegal_values){
    Board board = Board(1, 1);
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getRows(), 8);

    board = Board(-5, -1);
    EXPECT_EQ(board.getCols(), 8);
    EXPECT_EQ(board.getRows(), 8);
}

TEST(Board_constructor, colors){
    // 1 Black
    // 0 white
    Board board = Board();
    EXPECT_EQ(board.getColor(4, 4), false);
    EXPECT_EQ(board.getColor(5, 5), false);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(5, 4), true);

    board = Board(12, 4);
    EXPECT_EQ(board.getColor(6, 2), false);
    EXPECT_EQ(board.getColor(7, 3), false);
    EXPECT_EQ(board.getColor(6, 3), true);
    EXPECT_EQ(board.getColor(7, 2), true);
}

TEST(Board_play, legal_moves){
    Board board = Board();

    board.playColor(3, 4, true);
    EXPECT_EQ(board.getColor(3, 4), true);
    EXPECT_EQ(board.getColor(4, 4), true);
    EXPECT_EQ(board.getColor(5, 4), true);

    board.playColor(3, 3, false);
    EXPECT_EQ(board.getColor(3, 3), false);
    EXPECT_EQ(board.getColor(4, 4), false);
    EXPECT_EQ(board.getColor(5, 5), false);

    board.playColor(6, 5, true);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(5, 5), true);
    EXPECT_EQ(board.getColor(6, 5), true);

    board.playColor(3, 5, false);
    EXPECT_EQ(board.getColor(3, 5), false);
    EXPECT_EQ(board.getColor(3, 4), false);
    EXPECT_EQ(board.getColor(3, 3), false);
    EXPECT_EQ(board.getColor(4, 4), false);

    board.playColor(2, 3, true);
    EXPECT_EQ(board.getColor(2, 3), true);
    EXPECT_EQ(board.getColor(3, 4), true);
    EXPECT_EQ(board.getColor(4, 5), true);

    board.playColor(2, 4, false);
    EXPECT_EQ(board.getColor(2, 4), false);
    EXPECT_EQ(board.getColor(3, 4), false);
    EXPECT_EQ(board.getColor(4, 4), false);

    board.playColor(4, 3, true);
    EXPECT_EQ(board.getColor(3, 3), true);
    EXPECT_EQ(board.getColor(4, 4), true);
    EXPECT_EQ(board.getColor(4, 3), true);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(2, 3), true);

}

TEST(Board_play, illegal_moves){
    Board board = Board();
    // out of range
    board.playColor(-1, -1, true);
    board.playColor(9, 7, true);
    board.playColor(3, 10, true);

    EXPECT_EQ(board.getColor(4, 4), false);
    EXPECT_EQ(board.getColor(5, 5), false);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(5, 4), true);

    // on edge of same color
    board.playColor(3, 3, true);
    board.playColor(6, 6, true);
    board.playColor(3, 5, true);
    board.playColor(3, 6, true);
    board.playColor(4, 6, true);
    board.playColor(6, 3, true);
    board.playColor(7, 3, true);
    board.playColor(7, 4, true);

    EXPECT_EQ(board.getColor(4, 4), false);
    EXPECT_EQ(board.getColor(5, 5), false);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(5, 4), true);

    // other illegal moves
    board.playColor(1, 1, true);
    board.playColor(8, 8, true);
    board.playColor(7, 7, true);
    board.playColor(6, 2, true);
    board.playColor(3, 7, true);

    // check that the board is empty
    EXPECT_EQ(board.getColor(4, 4), false);
    EXPECT_EQ(board.getColor(5, 5), false);
    EXPECT_EQ(board.getColor(4, 5), true);
    EXPECT_EQ(board.getColor(5, 4), true);
    EXPECT_EQ(board.isColred(1, 1), false);
    EXPECT_EQ(board.isColred(1, 2), false);
    EXPECT_EQ(board.isColred(1, 3), false);
    EXPECT_EQ(board.isColred(1, 4), false);
    EXPECT_EQ(board.isColred(1, 5), false);
    EXPECT_EQ(board.isColred(1, 6), false);
    EXPECT_EQ(board.isColred(1, 7), false);
    EXPECT_EQ(board.isColred(1, 8), false);
    EXPECT_EQ(board.isColred(2, 1), false);
    EXPECT_EQ(board.isColred(2, 2), false);
    EXPECT_EQ(board.isColred(2, 3), false);
    EXPECT_EQ(board.isColred(2, 4), false);
    EXPECT_EQ(board.isColred(2, 5), false);
    EXPECT_EQ(board.isColred(2, 6), false);
    EXPECT_EQ(board.isColred(2, 7), false);
    EXPECT_EQ(board.isColred(2, 8), false);
    EXPECT_EQ(board.isColred(3, 1), false);
    EXPECT_EQ(board.isColred(3, 2), false);
    EXPECT_EQ(board.isColred(3, 3), false);
    EXPECT_EQ(board.isColred(3, 4), false);
    EXPECT_EQ(board.isColred(3, 5), false);
    EXPECT_EQ(board.isColred(3, 6), false);
    EXPECT_EQ(board.isColred(3, 7), false);
    EXPECT_EQ(board.isColred(3, 8), false);

    EXPECT_EQ(board.isColred(4, 1), false);
    EXPECT_EQ(board.isColred(4, 2), false);
    EXPECT_EQ(board.isColred(4, 3), false);
    EXPECT_EQ(board.isColred(4, 6), false);
    EXPECT_EQ(board.isColred(4, 7), false);
    EXPECT_EQ(board.isColred(4, 8), false);

    EXPECT_EQ(board.isColred(5, 1), false);
    EXPECT_EQ(board.isColred(5, 2), false);
    EXPECT_EQ(board.isColred(5, 3), false);
    EXPECT_EQ(board.isColred(5, 6), false);
    EXPECT_EQ(board.isColred(5, 7), false);
    EXPECT_EQ(board.isColred(5, 8), false);

    EXPECT_EQ(board.isColred(6, 1), false);
    EXPECT_EQ(board.isColred(6, 2), false);
    EXPECT_EQ(board.isColred(6, 3), false);
    EXPECT_EQ(board.isColred(6, 4), false);
    EXPECT_EQ(board.isColred(6, 5), false);
    EXPECT_EQ(board.isColred(6, 6), false);
    EXPECT_EQ(board.isColred(6, 7), false);
    EXPECT_EQ(board.isColred(6, 8), false);
    EXPECT_EQ(board.isColred(7, 1), false);
    EXPECT_EQ(board.isColred(7, 2), false);
    EXPECT_EQ(board.isColred(7, 3), false);
    EXPECT_EQ(board.isColred(7, 4), false);
    EXPECT_EQ(board.isColred(7, 5), false);
    EXPECT_EQ(board.isColred(7, 6), false);
    EXPECT_EQ(board.isColred(7, 7), false);
    EXPECT_EQ(board.isColred(7, 8), false);
    EXPECT_EQ(board.isColred(8, 1), false);
    EXPECT_EQ(board.isColred(8, 2), false);
    EXPECT_EQ(board.isColred(8, 3), false);
    EXPECT_EQ(board.isColred(8, 4), false);
    EXPECT_EQ(board.isColred(8, 5), false);
    EXPECT_EQ(board.isColred(8, 6), false);
    EXPECT_EQ(board.isColred(8, 7), false);
    EXPECT_EQ(board.isColred(8, 8), false);



}



