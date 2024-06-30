#include "evalhelper.h"

int valueOfPiece(int n) {
   if (n == 1) {
       return 100;
   }
   if (n == 2) {
       return 300;
   }
   if (n == 3) {
       return 310;
   }
   if (n == 4) {
       return 500;
   }
   if (n == 5) {
       return 900;
   }
   if (n == 6) {
       return 30000;
   }
   return 0;
}

// checks if a desired piece is within proximity of another piece
// output indicates how many pieces were found near it
// int color, int row, and int column are characteristics of the main piece
// int desiredTypeOfPiece gives the program info on what piece you are looking for
// rowRadius and columnRadius indicate the search range
// for example, pieceProximity(board, WHITE, 1, 1, 1, 2, 1)
// will look for any pawn in a 2 row by 1 column distance from position (1,1)
int pieceProximity(const Board *board, int color, int row, int column, int desiredTypeOfPiece, int rowRadius, int columnRadius) {
    int numPiecesInProximity = 0;

    for (int i = row - rowRadius; i <= row + rowRadius; i++) {
        for (int j = column - columnRadius; j <= column + columnRadius; j++) {
            // make sure i j are within boundaries
            if (i >= 0 && i < 8 && j >= 0 && j < 8) {
                // checks if the piece is the same
                if (board->squares[i][j].type == desiredTypeOfPiece) {
                    // checks if the color is the same
                    if (board->squares[i][j].color == color) {
                        numPiecesInProximity += 1;
                    }
                }
            }
        }
    }

    return numPiecesInProximity;
}

// is the color's King in check?
int isCheck(const Board *board, int color) {
   DefendingPiecesArray nArray;

   if (color == -1) {
        nArray = whiteControlArray(board);
   }
   if (color == 1) {
        nArray = blackControlArray(board);
   }

   for (int i = 0; i <= 7; i++){
       for (int j = 0; j <= 7; j++) {
            // if piece is king
            if (board->squares[i][j].type == 6) {
                // if king is the correct color
                if (board->squares[i][j].color == color) {
                    if (nArray.totalNumDefending[i][j] >= 1) {
                        return 1;
                    }
                }
            }
       }
   }

   return 0;
}

// fast version of isCheck
int fastIsCheck(const Board *board, int color, DefendingPiecesArray nArray) {

   for (int i = 0; i <= 7; i++){
       for (int j = 0; j <= 7; j++) {
            // if piece is king
            if (board->squares[i][j].type == 6) {
                // if king is the correct color
                if (board->squares[i][j].color == color) {
                    if (nArray.totalNumDefending[i][j] >= 1) {
                        return 1;
                    }
                }
            }
       }
   }

   return 0;
}
