#ifndef AI_H
#define AI_H

#include "chess.h"
#include "boardControl.h"

// helper functions

// returns value of pieces
// example: pawn = 100, knight = 300, queen = 900
int valueOfPiece(int n);

// checks if a desired piece is within proximity of another piece
// output indicates how many pieces were found near it
// int color, int row, and int column are characteristics of the main piece
// int desiredTypeOfPiece gives the program info on what piece you are looking for
// rowRadius and columnRadius indicate the search range
// for example, pieceProximity(board, WHITE, 1, 1, 1, 2, 1)
// will look for any pawn in a 2 row by 1 column distance from position (1,1)
int pieceProximity(const Board *board, int color, int row, int column, int desiredTypeOfPiece, int rowRadius, int columnRadius);

// is the color's King in check?
int isCheck(const Board *board, int color);

// fast version of isCheck
// assuming nArray is already created
int fastIsCheck(const Board *board, int color, DefendingPiecesArray nArray);

#endif
