#include "boardControl.h"
#include <stdlib.h> // For random move selection (placeholder)
#include <stdio.h>

// helper functions
// not included in header file
void pawn(DefendingPiecesArray *array, int color, int row, int column);
void knight(DefendingPiecesArray *array, int row, int column);
void bishop(const Board *board, DefendingPiecesArray *array, int row, int column);
void rook(const Board *board, DefendingPiecesArray *array, int row, int column);
void queen(const Board *board, DefendingPiecesArray *array, int row, int column);
void king(DefendingPiecesArray *array, int row, int column);

// Utility Functions
// return an array of 8 by 8 that correspond to how many pieces control that square
DefendingPiecesArray whiteControlArray(const Board *board);
DefendingPiecesArray blackControlArray(const Board *board);

DefendingPiecesArray initArray() {
    DefendingPiecesArray array;
    // Initialize all elements of the arrays to 0
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            array.defendingPawns[i][j] = 0;
            array.defendingMinor[i][j] = 0;
            array.defendingRook[i][j] = 0;
            array.defendingQueen[i][j] = 0;
            array.defendingKing[i][j] = 0;
            array.totalNumDefending[i][j] = 0;
        }
    }
    return array;
}

DefendingPiecesArray blackControlArray(const Board *board) {
    DefendingPiecesArray array = initArray();
    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // skip calculations if piece is white
            if (board->squares[i][j].color == 1) {
                continue;
            }
            // skip calculations if piece is null
            if (board->squares[i][j].type == 0) {
                continue;
            }

            switch(board->squares[i][j].type) {
                case 1:
                    // pawn case
                    pawn(&array, -1, i, j);
                    break;
                case 2:
                    // knight case
                    knight(&array, i, j);
                    break;
                case 3:
                    // bishop case
                    bishop(board, &array, i, j);
                    break;
                case 4:
                    // rook case
                    rook(board, &array, i, j);
                    break;
                case 5:
                    // queen case
                    queen(board, &array, i, j);
                    break;
                case 6:
                    // king case
                    king(&array, i, j);
                    break;
                default:
                    // nothing
                    break;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            array.totalNumDefending[i][j] = array.defendingPawns[i][j] + array.defendingMinor[i][j]+ array.defendingRook[i][j] + array.defendingQueen[i][j]+ array.defendingKing[i][j];
        }
    }
    return array;
}

DefendingPiecesArray whiteControlArray(const Board *board) {
    DefendingPiecesArray array = initArray();
    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // skip calculations if piece is black
            if (board->squares[i][j].color == -1) {
                continue;
            }
            // skip calculations if piece is null
            if (board->squares[i][j].type == 0) {
                continue;
            }

            switch(board->squares[i][j].type) {
                case 1:
                    // pawn case
                    pawn(&array, 1, i, j);
                    break;
                case 2:
                    // knight case
                    knight(&array, i, j);
                    break;
                case 3:
                    // bishop case
                    bishop(board, &array, i, j);
                    break;
                case 4:
                    // rook case
                    rook(board, &array, i, j);
                    break;
                case 5:
                    // queen case
                    queen(board, &array, i, j);
                    break;
                case 6:
                    // king case
                    king(&array, i, j);
                    break;
                default:
                    // nothing
                    break;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            array.totalNumDefending[i][j] = array.defendingPawns[i][j] + array.defendingMinor[i][j]+ array.defendingRook[i][j] + array.defendingQueen[i][j]+ array.defendingKing[i][j];
        }
    }
    return array;
}

// tasks to do

void pawn(DefendingPiecesArray *array, int color, int row, int column) {
    // is pawn's next row up/down a valid row
    if ((row + color >= 0) && (row + color <= 7)) {
        // is the left defended?
        if ((column - 1 >= 0)&&(column - 1 <= 7)){
            array->defendingPawns[row+color][column-1] += 1;
        }
        // is the right defended?
        if ((column + 1 >= 0)&&(column + 1 <= 7)) {
            array->defendingPawns[row+color][column+1] += 1;
        }
    }
}
void knight(DefendingPiecesArray *array, int row, int column) {
    int X;
    int Y;
    for (int i = -1; i<=1; i+=2) {
        for (int j = -1; j<= 1; j+=2) {
            for (int k = 0; k<=1; k++) {
                X = column + j * (1+k);
                Y = row + i * (2-k);
                if ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ){
                    array->defendingMinor[Y][X] += 1;
                }
            }
        }
    }
}
void bishop(const Board *board, DefendingPiecesArray *array, int row, int column) {
    int X;
    int Y;
    int i;

    // check for upper right diagonal
    i = 1;
    X = column + i;
    Y = row + i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingMinor[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
        Y = row + i;
    }

    // check for upper left diagonal
    i = 1;
    X = column - i;
    Y = row + i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingMinor[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
        Y = row + i;
    }

    // check for bottom left diagonal
    i = 1;
    X = column - i;
    Y = row - i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingMinor[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
        Y = row - i;
    }

    // check for bottom right diagonal
    i = 1;
    X = column + i;
    Y = row - i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingMinor[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
        Y = row - i;
    }
}
void rook(const Board *board, DefendingPiecesArray *array, int row, int column) {
    int X;
    int Y;
    int i;

    i = 1;
    X = column + i;
    Y = row;
    // squares to the right
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingRook[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
    }

    i = 1;
    X = column - i;
    Y = row;
    // squares to the left
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingRook[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
    }

    i = 1;
    X = column;
    Y = row + i;
    // squares to the top
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingRook[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        Y = row + i;
    }

    i = 1;
    X = column;
    Y = row - i;
    // squares to the bottom
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingRook[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        Y = row - i;
    }
}
void queen(const Board *board, DefendingPiecesArray *array, int row, int column){
    int X;
    int Y;
    int i;

    // check for upper right diagonal
    i = 1;
    X = column + i;
    Y = row + i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
        Y = row + i;
    }

    // check for upper left diagonal
    i = 1;
    X = column - i;
    Y = row + i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
        Y = row + i;
    }

    // check for bottom left diagonal
    i = 1;
    X = column - i;
    Y = row - i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
        Y = row - i;
    }

    // check for bottom right diagonal
    i = 1;
    X = column + i;
    Y = row - i;
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
        Y = row - i;
    }

        i = 1;
    X = column + i;
    Y = row;
    // squares to the right
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column + i;
    }

    i = 1;
    X = column - i;
    Y = row;
    // squares to the left
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        X = column - i;
    }

    i = 1;
    X = column;
    Y = row + i;
    // squares to the top
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        Y = row + i;
    }

    i = 1;
    X = column;
    Y = row - i;
    // squares to the bottom
    while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
        array->defendingQueen[Y][X] += 1;
        if (board->squares[Y][X].color != 0) {
            break;
        }
        i++;
        Y = row - i;
    }
}

void king(DefendingPiecesArray *array, int row, int column) {
    int X;
    int Y;

    X = column+1;
    Y = row;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column+1;
    Y = row+1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column;
    Y = row+1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column-1;
    Y = row+1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column-1;
    Y = row;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column-1;
    Y = row-1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column;
    Y = row-1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
    X = column+1;
    Y = row-1;
    if ((X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7)){
        array->defendingKing[Y][X] += 1;
    }
}

void displayDefendingPiecesArray(DefendingPiecesArray array) {
    int k;
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            k = array.totalNumDefending[i][j];
            printf("%d ", k);
        }
        printf(" row done \n");
    }
}