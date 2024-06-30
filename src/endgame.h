#ifndef ENDGAME_H
#define ENDGAME_H

#include "chess.h"
#include "boardControl.h"
#include "evalhelper.h"
#include "evaluate.h"

// checks the pawn structure of the chess board
// + 25 for a passer
// + 50 for a protected passer
// + 25 each plus + 50 for the tandem for two connected passers
int endGamePawnStructure(const Board *board);

// checks how many pieces each side has, and whether it is possible to still win
// for example, king + 2 rooks vs king + knight will always end on a win for king + 2 rooks
// unless stupid moves are played
int isWinnable(const Board *board);

// checks if any pawn is 3 or less moves away from promotion
// the closer the pawn, the more points
// if pawn is protected add even more points
int promotionPawn(const Board *board);

int symmetricalPawnStructure(const Board *board);

int kingPosition(const Board *board);
#endif
