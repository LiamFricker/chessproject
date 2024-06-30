#include "chess_ai.h"
#include "evaluate.h"
#include "log.h"
#include <stdlib.h>
#include <time.h>


// temporarily included for debugging
#include <stdio.h>


/*
VERY VERY IMPORTANT !!! Please read !!!
the main things missing from the alpha beta algorithm & the min/max functions
are the data structure & functions necessary to store and manipulate struct Board
I defined newBoard as the state of Board after old board + move, but newBoard can not replace the old board
In other words, we can not really directly modify the board and most likely have to create EITHER 1) undo function OR 2) copies of the Board struct
*/


/*
IDEAS that I have for implementation: feel free to change or modify as necessary


   To create newBoard
   Board newBoard = copyBoard(board); // copyBoard function HAS BEEN CREATED in chess.c
   newBoard = make_move(newBoard, start_x, start_y, end_x, end_y);
   // note 1: since Board does not require malloc, memory should be freed automatically when it is out of scope
   // note 2: thus, we shouldn't need to worry about memory leaks. although I'm concerned we may run out of memory space.


*/


// Utility function to add a move to the list if it's valid
void try_move(Board *board, int userColor, int x, int y, int dx, int dy, int *move_count, int moves[200][4]) {
   if (board->squares[y][x].type != 0) {
       if (board->squares[y][x].color == userColor) {
           if (is_move_valid(board, x, y, x+dx, y+dy)) {
               moves[*move_count][0] = x;
               moves[*move_count][1] = y;
               moves[*move_count][2] = x + dx;
               moves[*move_count][3] = y + dy;
               (*move_count)++;
           }
       }
   }
}


void ai_make_move(Board *board, Color ai_color) {
   int moves[200][4], move_count = 0;
   // Generate all valid moves for AI color
   //printf("checkpoint 1 passed \n");
   for (int i = 0; i < 8; i++) {
   //printf("checkpoint 2 passed \n");
       for (int j = 0; j < 8; j++) {
           if (board->squares[i][j].color == ai_color) {
               // Generate possible moves for each piece
               for (int dx = -7; dx <= 7; dx++) {
                   for (int dy = -7; dy <= 7; dy++) {
                       int ex = j + dx, ey = i + dy;
                       if (ex >= 0 && ex < 8 && ey >= 0 && ey < 8) {
                           if (is_move_valid(board, j, i, ex, ey)) {
                               moves[move_count][0] = j;
                               moves[move_count][1] = i;
                               moves[move_count][2] = ex;
                               moves[move_count][3] = ey;
                               move_count++;
                           }
                       }
                   }
               }
           }
       }
   }


   // variable to hold whether move leads to king being in check
   int goodMove = 0;
   while (goodMove == 0) {
       // Execute a random valid move
       if (move_count > 0) {
           srand(time(NULL));
           int index = rand() % move_count;
           make_move(board, moves[index][0], moves[index][1], moves[index][2], moves[index][3]);


           // check for checkmate
           if (isCheck(board, ai_color) > 0) {
               undo_move(board);
           }
           else {
               goodMove = 1;
           }
           /* Log AI's move
           char move_str[6];
           sprintf(move_str, "%c%d%c%d", 'A'+moves[index][0], moves[index][1]+1, 'A'+moves[index][2], moves[index][3]+1);
           log_move(move_str); */
       }
   }
}




// alpha beta pruning algorithm
// int output is the move that is the "best"
Move alpha_beta_algorithm(Board *board, Color color, int depth) {
   int alpha = -10000000;
   int beta = 10000000;
   int value;


   // default is NULL
   // AI outputs the best "move"
   Move aiMove;
   int startingColumn;
   int startingRow;
   int endingColumn;
   int endingRow;


   // initialize depths
   int maxDepth = depth;
   int currentDepth = 0;


   // create list of all possible moves
   // initialize move count to zero
   int move[200][4];
   int move_count = 0;
   int current_move;
   for (int i = 0; i < 8; i++) {
       for (int j = 0; j <8; j++) {
           for (int dx = -7; dx <= 7; dx++) {
               for (int dy = -7; dy <= 7; dy++) {
                   try_move(board, color, i, j, dx, dy, &move_count, move);
               }
           }
       }
   }


   // if there are no possible moves, return aiMove
   // -1 indicates out of bounds, aka no valid move
   if (move_count == 0) {
       aiMove.start_x = -1;
       aiMove.start_y = -1;
       aiMove.end_x = -1;
       aiMove.end_y = -1;
       return aiMove;
   }


   // create a temporary board
   Board *newBoard = malloc(sizeof(Board)); // Allocate memory for temporaryBoard
   if (!newBoard) {
       fprintf(stderr, "Memory allocation failed\n");
       aiMove.start_x = -1;
       aiMove.start_y = -1;
       aiMove.end_x = -1;
       aiMove.end_y = -1;
       return aiMove; // Properly handle memory allocation failure
   }


   // iterate through every possible move in the current board state
   // additional helper functions may be necessary
   current_move = 0;
   while (current_move < move_count) {
       // get move.??? values
       startingColumn = move[current_move][0];
       startingRow = move[current_move][1];
       endingColumn = move[current_move][2];
       endingRow = move[current_move][3];




       if (color == 1) {
           // newBoard = board + move
           // in other words, newBoard is the board after having taken that move


           // copy board to tempBoard
           copy_board(*board, newBoard);
           // make a move
           make_move(newBoard, startingColumn, startingRow, endingColumn, endingRow);


           currentDepth += 1;
           int newColor = (color == 1) ? -1:1;
           value = minEvalValue(newBoard, alpha, beta, currentDepth, maxDepth, newColor);
           if (value > alpha) {
               alpha = value;
               // assign the move
               aiMove.start_x = startingColumn;
               aiMove.start_y = startingRow;
               aiMove.end_x = endingColumn;
               aiMove.end_y = endingRow;
           }
       }
       if (color == -1) {
           // newBoard = board + move
           // in other words, newBoard is the board after having taken that move


           // copy board to tempBoard
           copy_board(*board, newBoard);
           // make a move
           make_move(newBoard, startingColumn, startingRow, endingColumn, endingRow);


           currentDepth += 1;
           int newColor = (color == 1) ? -1:1;
           value = maxEvalValue(newBoard, alpha, beta, currentDepth, maxDepth, newColor);
           if (value < beta) {
               beta = value;
               // please change the following line of code
               // assign the move
               aiMove.start_x = startingColumn;
               aiMove.start_y = startingRow;
               aiMove.end_x = endingColumn;
               aiMove.end_y = endingRow;
           }
       }


       // increase current_move
       current_move += 1;
   }


   // free the memory
   free(newBoard);


   return aiMove;
}


// returns the max value of the evaluation of all states
int maxEvalValue(Board *board, int alpha, int beta, int currentDepth, int maxDepth, int color) {
   int evaluationValue;
   int Value;
   int bestValue = -10000000; // set to negative infinity
   int newAlpha = alpha;
   int newBeta = beta;
   int newCurrentDepth;


   // cutoff condition, depth of calculations
   if (currentDepth >= maxDepth) {
       // please note that complexEval(newBoard) needs to evaluate the updated version of the board
       // the board is not the original board 5 recursive steps ago
       // instead, "newBoard" is the board state after having taken N moves
       evaluationValue = complexEval(board);
       return evaluationValue;
   }


   // intialize newBoard
   Board *newBoard = malloc(sizeof(Board)); // Allocate memory for temporaryBoard
   // create list of all possible moves
   // initialize move count to zero
   int move[200][4];
   int move_count = 0;
   int current_move;
   for (int i = 0; i < 8; i++) {
       for (int j = 0; j <8; j++) {
           for (int dx = -7; dx <= 7; dx++) {
               for (int dy = -7; dy <= 7; dy++) {
                   try_move(board, color, i, j, dx, dy, &move_count, move);
               }
           }
       }
   }


   // iterate through every possible move in the current board state
   // additional helper functions may be necessary
   current_move = 0;
   int startingColumn;
   int startingRow;
   int endingColumn;
   int endingRow;


   // if there is no valid move left, it means the king is checkmated
   if (move_count == 0) {
       return -10000;
   }


   while (current_move < move_count) {
       newCurrentDepth = currentDepth + 1;


       startingColumn = move[current_move][0];
       startingRow = move[current_move][1];
       endingColumn = move[current_move][2];
       endingRow = move[current_move][3];


       // newBoard = board + move
       // aka board state after move is processed


       // copy board to tempBoard
       copy_board(*board, newBoard);
       // make a move
       make_move(newBoard, startingColumn, startingRow, endingColumn, endingRow);


       int newColor = (color == 1) ? -1:1;
       Value = minEvalValue(newBoard, newAlpha, newBeta, newCurrentDepth, maxDepth, newColor);
       if (Value >= bestValue) {
           bestValue = Value;
       }
       if (newAlpha >= Value) {
           newAlpha = Value;
       }
       if (newAlpha >= newBeta) {
           free(newBoard);
           return Value;
       }


       current_move += 1;
   }


   free(newBoard);
   return bestValue;
}


// returns the min value of the evaluation of all states
int minEvalValue(Board *board, int alpha, int beta, int currentDepth, int maxDepth, int color) {
   int evaluationValue;
   int Value;
   int bestValue = 10000000; // set to positive infinity
   int newAlpha = alpha;
   int newBeta = beta;
   int newCurrentDepth;


   // cutoff condition, depth of calculations
   if (currentDepth >= maxDepth) {
       // please note that complexEval(newBoard) needs to evaluate the updated version of the board
       // the board is not the original board 5 recursive steps ago
       // instead, "newBoard" is the board state after having taken N moves
       evaluationValue = complexEval(board);
       return evaluationValue;
   }


   // intialize newBoard
   Board *newBoard = malloc(sizeof(Board)); // Allocate memory for temporaryBoard
   // create list of all possible moves
   // initialize move count to zero
   int move[200][4];
   int move_count = 0;
   int current_move;
   for (int i = 0; i < 8; i++) {
       for (int j = 0; j <8; j++) {
           for (int dx = -7; dx <= 7; dx++) {
               for (int dy = -7; dy <= 7; dy++) {
                   try_move(board, color, i, j, dx, dy, &move_count, move);
               }
           }
       }
   }


   // if there is no valid move left, it means the king is checkmated
   if (move_count == 0) {
       return 10000;
   }


   // iterate through every possible move in the current board state
   // additional helper functions may be necessary
   int startingColumn;
   int startingRow;
   int endingColumn;
   int endingRow;
   current_move = 0;
   while (current_move < move_count) {


       startingColumn = move[current_move][0];
       startingRow = move[current_move][1];
       endingColumn = move[current_move][2];
       endingRow = move[current_move][3];


       newCurrentDepth = currentDepth + 1;
       // newBoard = board + move
       // aka board state after move is processed


       // copy board to tempBoard
       copy_board(*board, newBoard);
       // make a move
       make_move(newBoard, startingColumn, startingRow, endingColumn, endingRow);


       int newColor = (color == 1) ? -1:1;
       Value = maxEvalValue(newBoard, newAlpha, newBeta, newCurrentDepth, maxDepth, newColor);
       if (Value <= bestValue) {
           bestValue = Value;
       }
       if (newBeta <= Value) {
           newBeta = Value;
       }
       if (newAlpha >= newBeta) {
           free(newBoard);
           return Value;
       }


       current_move += 1;
   }


   free(newBoard);
   return bestValue;
}