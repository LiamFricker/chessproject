#ifndef EARLYGAME_H
#define EARLYGAME_H

#include "evalhelper.h"
#include "boardControl.h"
#include "chess.h"
#include "log.h"

// Early Game

// how many squares in the direct center are controlled by pawns?
int controlOfCenter(const Board *board);

// how many squares in near the center are controlled by pawns
int controlOfLargeCenter(const Board *board);

// make sure minor pieces are developed first
// did the knight move before bishop? did queen move before minors?
//int orderOfDevelopment(Log *log);

// is one side massively underdeveloped? aka minor pieces have not moved from original square
int underDevelopment(const Board *board);

// are pawns supported by other pawns
int isPawnSupported(const Board *board);

// if the king has not castled yet, did the king lose its castling rights?
//int isCastlingRights(Log *log);

// is the knight pinned to a king or queen?
int knightPinToKingOrQueen(const Board *board);

#endif