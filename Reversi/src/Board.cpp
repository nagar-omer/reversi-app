/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Exercise name:   Ex1                                                      *
 * File description: This file contains the Board Class header               *
 ****************************************************************************/

#include "../include/Board.h"

/*************************************************************************
 * Function name: Board default Constructor                              *
 ************************************************************************/
Board::~Board() {
    delete[] board;
}

/*************************************************************************
 * Function name: Board Constructor                                      *
 * Input: board dimensions row,col                                       *
 * operation: creates starting board col X row (default 8X8)             *
 ************************************************************************/
Board::Board(int row, int col) {
    if(row > 1 && col > 1) {
        // initializing row/col
        this->row = row;
        this->col = col;
    }
    else{
        this->row = 8;
        this->col = 8;
    }

    //initiate ERROR cell to return when needed
    error.markOutOfBound();

    // creating new array to save the matrix
    board = new Cell[row*col];
    //initialize cells with indexes
    int current = 0;
    for (int i = 0; i<row; i ++)
        for (int j = 0; j<col; j ++)
            board[current++].index(i,j);


    // marking middle cells to XOXO
    getCell(row/2-1,col/2-1).markColor(false);
    getCell(row/2,col/2).markColor(false);
    getCell(row/2-1,col/2).markColor(true);
    getCell(row/2,col/2-1).markColor(true);

}


/*************************************************************************
 * Function name: getCell                                                *
 * Input: row,col                                                        *
 * Output: returns the correct cell from the board array according       *
 * to the requested row and column                                       *
 ************************************************************************/
Board::Cell &Board::getCell(int i, int j) {
    // verify index
    if(i >= 0 && j >= 0 && i < row && j < col)
        // cell[i][j] is at i*col+j
        return board[i*col + j];
    return error;
}

/*************************************************************************
 * Function name: const version (overload) of getCell                    *
 ************************************************************************/
const Board::Cell &Board::getCell(int i, int j) const{
    // verify index
    if(i >= 0 && j >= 0 && i < row && j < col)
        // cell[i][j] is at i*col+j
        return board[i*col + j];
    return error;
}

/*************************************************************************
 * Function name: operator <<                                            *
 * Input: ostream << Board                                               *
 * Output: prints the board of the game at current time                  *
 ************************************************************************/
ostream & operator << (ostream &os,const Board &bo) {
    ostringstream temp;
    // print first row to indicate col number |  1  |  2  |.....|  k  |....
    temp << "    |";
    for (int j = 0; j < bo.col; j ++){
        if (j < 9)
            temp << "  " << j+1 << "  |";
        else if (j < 99)
            temp << " " << j+1 << "  |";
        else
            temp << " " << j+1 << " |";
    }
    // print separator ---------------------
    temp << endl << "-----";
    for (int j = 0; j < bo.col; j ++)
        temp << "------";
    temp << endl;


    for (int i = 0; i < bo.row; i++) {
        // print first col to indicate row number .  i|
        if (i < 9)
            temp << "   " << i + 1 << "|";
        else if (i < 99)
            temp << "  " << i + 1 << "|";
        else
            temp << " " << i + 1 << "|";

        // print the cell itself
        for (int j = 0; j < bo.col; j++)
            temp << bo.getCell(i, j);


        // print separator ---------------------
        temp << endl << "-----";
        for (int j = 0; j < bo.col; j ++)
            temp << "------";
        temp << endl;
    }
    return os << temp.str();
}

/*************************************************************************
 * Function name: operator <<                                            *
 * Input: ostream << Cell                                                *
 * Output: prints the cell to the ostream "  F  |"                       *
 ************************************************************************/
ostream & operator << (ostream &os, const Board::Cell &cell){
    ostringstream temp;
    // prints ."  F  |"  when F = O/ /X
    temp <<  "  " << cell.flag << "  |";
    return os << temp.str();
}

/*************************************************************************
 * Function name: playColor                                              *
 * Input: row, column and (BLACK = 1, WHITE = 0)                         *
 * Output: play othello move withe requested cell and color              *
 *          if the move isn't legal returns false                        *
 ************************************************************************/
bool Board::playColor(int moveRow, int moveCol, bool color) {
    // to the public indexes from 1...n hence -1
    moveCol = moveCol -1;
    moveRow = moveRow -1;
    if(getCell(moveRow, moveCol).isOutOfBoud())
        return false;
    // if the move is legal paint all directions
    if(isMovePossible(moveRow, moveCol, color)) {
        legalMoveDirection(getCell(moveRow, moveCol), color, UP, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, UP_RIGHT, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, RIGHT, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_RIGHT, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, DOWN, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_LEFT, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, LEFT, true);
        legalMoveDirection(getCell(moveRow, moveCol), color, UP_LEFT, true);
        return true;
    }
    return false;

}

/*************************************************************************
 * Function name: isMovePossible                                         *
 * Input: row, column and (BLACK = 1, WHITE = 0)                         *
 * Output: returns true if its legal to paint cell in requested color    *
 *          and false otherwise                                          *
 ************************************************************************/
bool Board::isMovePossible(int moveRow, int moveCol, bool color) {
    // only empty cells within the board can be legal
    if(getCell(moveRow, moveCol).isOutOfBoud() || getCell(moveRow, moveCol).isColored())
        return false;
    // if one of the following is true then the move is legal
    if (legalMoveDirection(getCell(moveRow, moveCol), color, UP))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, UP_RIGHT))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, RIGHT))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_RIGHT))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, DOWN))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_LEFT))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, LEFT))
        return true;
    else if (legalMoveDirection(getCell(moveRow, moveCol), color, UP_LEFT))
        return true;
    return false;
}

/*************************************************************************
 * Function name: OpponentScoreForMove                                   *
 * Input: row column and color (BLACK = 1, WHITE = 0)                    *
 * Output: returns opponent's score after the move (row,col)             *
 ************************************************************************/
int Board::OpponentScoreForMove(int moveRow, int moveCol, bool color){
    // score for opponent player before move
    int scoreOpponentColor = score(!color);
    // legalMoveDirection will return the number of cell that change color from the opponent color
    // to current color, the opponent score after the move will be the subtraction of the
    // those cells from the score before the move
    if(!getCell(moveRow, moveCol).isOutOfBoud() || !getCell(moveRow, moveCol).isColored()) {
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, UP);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, UP_RIGHT);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, RIGHT);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_RIGHT);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, DOWN);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, DOWN_LEFT);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, LEFT);
        scoreOpponentColor -= legalMoveDirection(getCell(moveRow, moveCol), color, UP_LEFT);
    }
    return scoreOpponentColor;
}

/*************************************************************************
 * Function name: possibleMoves                                          *
 * Input: color (BLACK = 1, WHITE = 0)                                   *
 * Output: returns string for possible moves for requested color         *
 ************************************************************************/
string Board::possibleMoves(bool color) {
    ostringstream result;
    bool firstComma = true;
    for(int i = 0l; i < row; i++)
        for (int j=0 ; j < col ; j++) {
            // check if move is legal
            bool legalMove = isMovePossible(i,j,color);
            // if the move is legal add it to the string
            if (legalMove) {
                // don't print before the first cell
                if (!firstComma)
                    result << ",";
                else
                    firstComma = false;
                result << "(" << i+1 << "," << j+1 << ")";
            }
        }
    return result.str();
}


/*************************************************************************
 * Function name: legalMoveDirection                                     *
 * Input: starting cell color(BLACK = 1, WHITE = 0) direction and a bool *
 * value to indicate if paint cells or just return answer for possibility*
 * Output: returns                                                       *
 * - true if there is a legal sequence to the arrow direction            *
 *      i.e Xooox is correct sequence to the right (start = X)           *
 * - false if it's not legal to paint thee cell in requested color       *
 ************************************************************************/
int Board::legalMoveDirection(Board::Cell &start, bool color,direction arrow, bool mark) {
    // get next cell in the direction of the arrow
    Board::Cell *current = &nextCellOnDirection(start, arrow);
    // check that the next cell in the arrow direction is in opposite color otherwise return Error
    if (current->isOutOfBoud() || !current->isColored() || current->getColor() == color )
        return 0;

    // vector to save cells to be colored if move is legal
    vector<Cell *> toMark;
    // first cell to mark in case that start is legal move (because it's color is for sure !color)
    toMark.push_back(&start);
    toMark.push_back(current);

    // loop on all opposite color in arrow direction
    while(!(current = &nextCellOnDirection(*current,arrow))->isOutOfBoud() &&
          current->isColored() && current->getColor() != color)
        // if mark is true
        toMark.push_back(current);

    // if current cell is not colored or it's out of the board then there wasn't
    // a cell withe same color in the arrow direction
    if (current->isOutOfBoud() || !current->isColored())
        return 0;
    // if current cell is colored in the original color then the move is legal

    // counter for number of cells that are painted from one color to the other
    // - starts from -1 because the start point is not painted at all - thus doesn't need to be counted
    int toPaintCount = -1;

    for (vector<Board::Cell *>::iterator it = toMark.begin(); it != toMark.end(); ++it) {
        if(mark)
            (*it)->markColor(color);
        toPaintCount++;
    }


    return toPaintCount;
}

/*************************************************************************
 * Function name: nextCellOnDirection                                    *
 * Input: cell and direction                                             *
 * Output: returns the a reference to the directed neighbor of the cell  *
 ************************************************************************/
Board::Cell &Board::nextCellOnDirection(const Cell &cell,direction direct) {
    switch (direct){
        case UP:
            return getCell(cell.getRow()-1,cell.getCol());
        case UP_RIGHT:
            return getCell(cell.getRow()-1,cell.getCol()+1);
        case RIGHT:
            return getCell(cell.getRow(),cell.getCol()+1);
        case DOWN_RIGHT:
            return getCell(cell.getRow()+1,cell.getCol()+1);
        case DOWN:
            return getCell(cell.getRow()+1,cell.getCol());
        case DOWN_LEFT:
            return getCell(cell.getRow()+1,cell.getCol()-1);
        case LEFT:
            return getCell(cell.getRow(),cell.getCol()-1);
        case UP_LEFT:
            return getCell(cell.getRow()-1,cell.getCol()-1);
        default:
            getCell(cell.getRow()-1,cell.getCol()-1);

    }
}

/*************************************************************************
 * Function name: score                                                  *
 * Input: color (BLACK = 1, WHITE = 0)                                   *
 * Output: returns number of cells painted with requested color          *
 ************************************************************************/
int Board::score(bool color) const {
    int count = 0;
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++) {
            if (getCell(i, j).getColor() == color)
                count++;
        }
    return count;
}
