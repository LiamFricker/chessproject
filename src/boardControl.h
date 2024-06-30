#ifndef BOARDCONTROL_H
#define BOARDCONTROL_H

#include "chess.h"

typedef struct {
    int defendingPawns[8][8];
    int defendingMinor[8][8];
    int defendingRook[8][8];
    int defendingQueen[8][8];
    int defendingKing[8][8];
    // totalNumDefending = total number of pieces defending a square
    int totalNumDefending[8][8];
} DefendingPiecesArray;

// initiates the array
DefendingPiecesArray initArray();

// Utility Functions
// return an array of 8 by 8 that correspond to how many pieces control that square
DefendingPiecesArray whiteControlArray(const Board *board);
DefendingPiecesArray blackControlArray(const Board *board);

void displayDefendingPiecesArray(DefendingPiecesArray array);

#endif
