#ifndef MIDGAME_H
#define MIDGAME_H

#include "chess.h"
#include "evalhelper.h"
#include "boardControl.h"

// Middle Game

// how many squares can the minor pieces move?
int pieceMobility(const Board *board);

// how many squares can the pawns move?
int pawnMobility(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray);

// are the pieces coordinated in defense and attack?
// are many pieces attacking the same square? aka knight + pawn attacking one pawn
int pieceCoordination(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray);

// return value indicating how many squares multiples pieces are attacking/defending
// for example, knight and bishop both defend the same square +5
// if queen + rook are coordinated, +15
// etc...
int intersection(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray);

// - 20 for an isolated p
// - 50 each for double isolated ps
int pawnStructure(const Board *board);

// if 4 pawns are connected and close to promotion (3 or less moves away), + 600
int fourConnectedPawns(const Board *board);

// if the King is in ideal locations, +points
int kingRankSafetyCalculation(const Board *board);

// is the bishop aligned on good diagonals
int bishopDiagonal(const Board *board);

// is the opponent king being attacked?
// +points for the strength of attack
// example: rook on semi open file + 50, two rooks + 80
int attackOpponentKing(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray);

// can the rook pin anything?
// for example: if the rook pins a bishop to the king, +50
// for example: if the rook pins a knight to the queen +50
int rookPinSomething(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray);

#endif
