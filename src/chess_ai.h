#ifndef CHESS_AI_H
#define CHESS_AI_H


#include "chess.h"
#include "evalhelper.h"
#include "evaluate.h"


// AI function prototypes
void ai_make_move(Board *board, Color color);


/*
VERY VERY IMPORTANT !!! Please read !!!
the main things missing from the alpha beta algorithm & the min/max functions
are the data structure & functions necessary to store and manipulate struct Board
I defined newBoard as the state of Board after old board + move, but newBoard can not replace the old board
In other words, we can not really directly modify the board and most likely have to create EITHER 1) undo function OR 2) copies of the Board struct
*/


// alpha beta pruning algorithm
// int output is the move that is the "best"
// depth is the number of moves in advance the AI needs to scan through
Move alpha_beta_algorithm(Board *board, Color color, int depth);
/*
FUNCTION output: Move is a struct containing...
   int start_x;
   int start_y;
   int end_x;
   int end_y;


   IMPORTANT NOTE: check whether start_x, start_y, end_x, end_y = -1
   if any of these values is -1, that means it's checkmate, aka no valid move
   in other words, just make sure start_x, start_y, end_x, end_y is between 0 and 7
*/


// returns the max value of the evaluation of all states
int maxEvalValue(Board *board, int alpha, int beta, int currentDepth, int maxDepth, int color);


// returns the min value of the evaluation of all states
int minEvalValue(Board *board, int alpha, int beta, int currentDepth, int maxDepth, int color);


#endif // CHESS_AI_H