#ifndef EVALUATE_H
#define EVALUATE_H

#include "chess.h"
#include "earlygame.h"
#include "midgame.h"
#include "endgame.h"
#include "boardControl.h"

#define BOARD_SIZE 8

// Simple Evaluation Function
// returns sum of value of pieces
int simpleEval(const Board *board);

// Complex Evaluation Function
// takes into account other factors of the chess game;i.e. king safety, control, etc...
int complexEval(const Board *board);

#endif
