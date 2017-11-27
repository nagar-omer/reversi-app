/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/


#ifndef BOARD
#define BOARD

#include <sstream>
#include <iostream>
#include <vector>

using namespace std;




/*****************************************************************************
 * Board Class: this class contains the board of the game                    *
 ****************************************************************************/
class Board {
    enum direction {
        UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT
    };

    /*************************************************************************
     * Inner class Cell: holds unique cell in the board                      *
     ************************************************************************/
    class Cell {
        // initializing flag to be blank
        int row, col;
        bool colored;
        // 1 for black 0 for white
        bool color;
        bool outOfBound;
        char flag;
    public:
        /*************************************************************************
         * Function name: isColored                                              *
         * Output: returns false if empty and true otherwise                     *
         ************************************************************************/
        bool isColored() const { return colored; };

        /*************************************************************************
         * Function name: getColor                                               *
         * Output: returns 1 for BLACK, 0 for WHITE                              *
         ************************************************************************/
        bool getColor() const { return color; };

        /*************************************************************************
         * Function name: markOutOfBound                                         *
         * Output: mark as "ERROR" cell - will be used to represent out of range *
         ************************************************************************/
        void markOutOfBound() { outOfBound = true; };

        /*************************************************************************
         * Function name: isOutOfBoud                                            *
         * Output: true for "ERROR" cell false otherwise                         *
         ************************************************************************/
        bool isOutOfBoud() const { return outOfBound; };

        /*************************************************************************
         * Function name: getRow                                                 *
         * Output: returns cell row index                                        *
         ************************************************************************/
        int getRow() const { return row; };

        /*************************************************************************
         * Function name: getCol                                                 *
         * Output: returns cell column index                                     *
         ************************************************************************/
        int getCol() const { return col; };

        /*************************************************************************
         * Function name: index                                                  *
         * Input: row and column indexes                                         *
         * Output: initiate cell acording to location                            *
         ************************************************************************/
        void index(int i, int j) {
            row = i;
            col = j;
        }

        /*************************************************************************
         * Function name: default consructor                                     *
         ************************************************************************/
        Cell() {
            flag = ' ';
            colored =  false;
            outOfBound = false;
        };

        /*************************************************************************
         * Function name: MarkO                                                  *
         * Input: no input                                                       *
         * Output: marks cell as O                                               *
         ************************************************************************/
        void markColor(bool inColor) {
            // checking that the flag is Blank
            colored = true;
            color = inColor;
            if (inColor)
                flag = 'X';
            else
                flag = 'O';

        };

        /*************************************************************************
         * Function name: operator <<                                            *
         * Input: ostream << Cell                                                *
         * Output: prints the cell to the ostream "  F  |"                       *
         ************************************************************************/
        friend ostream &operator<<(ostream &os, const Cell &cell);
    };

    //private variables for board....

    // parameters to hold the dimensions
    int row, col;
    // special cell indicating out of range
    Cell error;
    // ptr for the matrix of the board
    Cell *board;

    /*************************************************************************
     * Function name: getCell                                                *
     * Input: row,col                                                        *
     * Output: returns the correct cell from the board array according       *
     * to the requested row and column                                       *
     ************************************************************************/
    Cell &getCell(int i, int j);

    /*************************************************************************
     * Function name: const version (overload) of getCell                    *
     ************************************************************************/
    const Cell &getCell(int i, int j) const;

    /*************************************************************************
    * Function name: isMovePossible                                         *
    * Input: row, column and (BLACK = 1, WHITE = 0)                         *
    * Output: returns true if its legal to paint cell in requested color    *
    *          and false otherwise                                          *
    ************************************************************************/
    bool isMovePossible(int moveRow, int moveCol, bool color);

    /*************************************************************************
     * Function name: legalMoveDirection                                     *
     * Input: starting cell color(BLACK = 1, WHITE = 0) direction and a bool *
     * value to indicate if paint cells or just return answer for possibility*
     * Output: returns                                                       *
     * - true if there is a legal sequence to the arrow direction            *
     *      i.e Xooox is correct sequence to the right (start = X)           *
     * - false if it's not legal to paint thee cell in requested color       *
     ************************************************************************/
    int legalMoveDirection(Cell &start, bool color,direction arrow, bool mark = false);

    /*************************************************************************
     * Function name: nextCellOnDirection                                    *
     * Input: cell and direction                                             *
     * Output: returns the a reference to the directed neighbor of the cell  *
     ************************************************************************/
    Cell &nextCellOnDirection(const Cell &cell,direction direct) ;


public:
    static const bool BLACK = true;
    static const bool WHITE = false;
    // funcs for testing - other then that they are not needed
    int getRows() { return  row;};
    int getCols() { return  col;};
    // the numbers are shown 1..n hence the -1
    bool getColor(int i, int j) { return getCell(i - 1, j - 1).getColor(); };
    bool isColred(int i, int j) { return getCell(i - 1, j - 1).isColored(); };
    // end of funcs for testing

    /*************************************************************************
     * Function name: Board Constructor                                      *
     * Input: board dimensions row,col                                       *
     * operation: creates starting board col X row (default 8X8)             *
     ************************************************************************/
    Board(int row = 8, int col = 8);

    /*************************************************************************
     * Function name: operator <<                                            *
     * Input: ostream << Board                                               *
     * Output: prints the board of the game at current time                  *
     ************************************************************************/
    friend ostream &operator<<(ostream &os,const Board &bo);

    /*************************************************************************
     * Function name: Board default Constructor                              *
     ************************************************************************/
    ~Board();

    /*************************************************************************
     * giving access to private class Cell to operator of Cell               *
     ************************************************************************/
    friend ostream &operator<<(ostream &os, const Board::Cell &cell);

    /*************************************************************************
     * Function name: playColor                                              *
     * Input: row, column and (BLACK = 1, WHITE = 0)                         *
     * Output: play othello move withe requested cell and color              *
     *          if the move isn't legal returns false                        *
     ************************************************************************/
    bool playColor(int moveRow, int moveCol, bool color);

    /*************************************************************************
     * Function name: possibleMoves                                          *
     * Input: color (BLACK = 1, WHITE = 0)                                   *
     * Output: returns string for possible moves for requested color         *
     ************************************************************************/
    string possibleMoves(bool color);

    /*************************************************************************
     * Function name: score                                                  *
     * Input: color (BLACK = 1, WHITE = 0)                                   *
     * Output: returns number of cells painted with requested color          *
     ************************************************************************/
    int score(bool color) const;

    /*************************************************************************
     * Function name: OpponentScoreForMove                                   *
     * Input: row column and color (BLACK = 1, WHITE = 0)                    *
     * Output: returns opponent's score after the move (row,col)             *
     ************************************************************************/
    int OpponentScoreForMove(int moveRow, int moveCol, bool color);
};



#endif //BOARD
