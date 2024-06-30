#include "midgame.h"

int pawnMobility(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray) {
   int score = 0;
   int colorConstant;

   // 5 points for each space a pawn can move to
   for (int i = 0; i <= 7; i++){
       for (int j = 0; j <= 7; j++) {
           if (board->squares[i][j].type == 1) {
               colorConstant = board->squares[i][j].color;
               // check if new position is in board boundaries
               if ((i + colorConstant >= 0) && (i + colorConstant <= 7)) {
                   // check for whether pawn move is valid
                   // aka if the square is heavily defended
                   if (colorConstant == 1) {
                       if (wArray.defendingPawns[i + colorConstant][j] >= bArray.defendingPawns[i + colorConstant][j]) {
                           if (wArray.totalNumDefending[i + colorConstant][j] >= bArray.totalNumDefending[i + colorConstant][j]) {
                               if (board->squares[i+colorConstant][j].type == 0) {
                                   score += colorConstant * 5;
                               }
                           }
                       }
                   }


                   if (colorConstant == -1) {
                       if (bArray.defendingPawns[i + colorConstant][j] >= wArray.defendingPawns[i + colorConstant][j]) {
                           if (bArray.totalNumDefending[i + colorConstant][j] >= wArray.totalNumDefending[i + colorConstant][j]) {
                               if (board->squares[i+colorConstant][j].type == 0) {
                                   score += colorConstant * 5;
                               }
                           }
                       }
                   }
               }
           }
       }
   }


   return score;
}


int pieceMobility(const Board *board) {
   int score = 0;
   int colorConstant;
   int counter = 0;
   int X;
   int Y;
   int Z;
   int column;
   int row;


   for (int i = 0; i <= 7; i++){
       for (int j = 0; j <= 7; j++) {
           colorConstant = board->squares[i][j].color;
           column = j;
           row = i;
           switch(board->squares[i][j].type) {
               case 2:
                   for (int a = -1; a<=1; a+=2) {
                       for (int b = -1; b<= 1; b+=2) {
                           for (int k = 0; k<=1; k++) {
                               X = j + b * (1+k);
                               Y = i + a * (2-k);
                               if ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ){
                                   if (board->squares[Y][X].color != colorConstant) {
                                       score += colorConstant * 10;
                                   }
                               }
                           }
                       }
                   }
                   break;
               case 3:
                   counter = 0;
                   // check for upper right diagonal
                   Z = 1;
                   X = column + Z;
                   Y = row + Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                       Y = row + Z;
                   }


                   // check for upper left diagonal
                   Z = 1;
                   X = column - Z;
                   Y = row + Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                       Y = row + Z;
                   }


                   // check for bottom left diagonal
                   Z = 1;
                   X = column - Z;
                   Y = row - Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                       Y = row - Z;
                   }


                   // check for bottom right diagonal
                   Z = 1;
                   X = column + Z;
                   Y = row - Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                       Y = row - Z;
                   }


                   // tally up all possible moves * 10
                   score += colorConstant*counter*10;
                   break;
               case 4:
                   counter = 0;
                   Z = 1;
                   X = column + Z;
                   Y = row;
                   // squares to the right
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                   }


                   Z = 1;
                   X = column - Z;
                   Y = row;
                   // squares to the left
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                   }


                   Z = 1;
                   X = column;
                   Y = row + Z;
                   // squares to the top
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       Y = row + Z;
                   }


                   Z = 1;
                   X = column;
                   Y = row - Z;
                   // squares to the bottom
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       Y = row - Z;
                   }


                   // tally up all possible moves * 10
                   score += colorConstant*counter*10;
                   break;
               case 5:
                   counter = 0;


                   Z = 1;
                   X = column + Z;
                   Y = row;
                   // squares to the right
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                   }


                   Z = 1;
                   X = column - Z;
                   Y = row;
                   // squares to the left
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                   }


                   Z = 1;
                   X = column;
                   Y = row + Z;
                   // squares to the top
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       Y = row + Z;
                   }


                   Z = 1;
                   X = column;
                   Y = row - Z;
                   // squares to the bottom
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       Y = row - Z;
                   }


                   // check for upper right diagonal
                   Z = 1;
                   X = column + Z;
                   Y = row + Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                       Y = row + Z;
                   }


                   // check for upper left diagonal
                   Z = 1;
                   X = column - Z;
                   Y = row + Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                       Y = row + Z;
                   }


                   // check for bottom left diagonal
                   Z = 1;
                   X = column - Z;
                   Y = row - Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column - Z;
                       Y = row - Z;
                   }


                   // check for bottom right diagonal
                   Z = 1;
                   X = column + Z;
                   Y = row - Z;
                   while ( (X >= 0)&&(X<=7)&&(Y>=0)&&(Y<=7) ) {
                       counter++;
                       if (board->squares[Y][X].color != 0) {
                           break;
                       }
                       Z++;
                       X = column + Z;
                       Y = row - Z;
                   }


                   // tally up all possible moves * 10
                   score += colorConstant*counter*10;
                   break;
               default:
                   break;
           }
       }
   }


   return score;
}


int pieceCoordination(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray) {
   int score = 0;
   int colorConstant;
   int typeOfPiece;
   int valuePiece;

   for (int i = 0; i <= 7; i++){
       for (int j = 0; j <= 7; j++) {
           colorConstant = board->squares[i][j].color;
           // if the piece is not null aka it is either a black or white piece
           if (colorConstant != 0) {
               typeOfPiece = board->squares[i][j].type;
               valuePiece = valueOfPiece(typeOfPiece);

               // defensive calculations
               // add 0.01*valueOfPiece for each piece that defends it
               // offensive calculations
               // add 0.02*valueOfPiece - 0.02 of piece attacking it
               if (colorConstant == 1) {
                    score += (0.01) * (valuePiece) * wArray.totalNumDefending[i][j];
                    if (bArray.totalNumDefending[i][j] >= 1) {
                        if (bArray.defendingPawns[i][j] >= 1) {
                            score -= (0.02) * (valuePiece) - 0.02*100;
                        }
                        else {
                            if (bArray.defendingMinor[i][j] >= 1) {
                                score -= 0.02 * valuePiece - 0.02*300;
                            }
                            else {
                                if (bArray.defendingRook[i][j] >= 1) {
                                    score -= 0.02*valuePiece - 0.02*500;
                                }
                                else {
                                    if (bArray.defendingQueen[i][j] >= 1) {
                                        score -= 0.02*valuePiece - 0.02*900;
                                    }
                                }
                            }
                        }
                    }
               }
               if (colorConstant == 1) {
                    score -= 0.01*valuePiece*bArray.totalNumDefending[i][j];
                    if (wArray.totalNumDefending[i][j] >= 1) {
                        if (wArray.defendingPawns[i][j] >= 1) {
                            score -= 0.02*valuePiece - 0.02*100;
                        }
                        else {
                            if (wArray.defendingMinor[i][j] >= 1) {
                                score -= 0.02*valuePiece - 0.02*300;
                            }
                            else {
                                if (wArray.defendingRook[i][j] >= 1) {
                                    score -= 0.02*valuePiece - 0.02*500;
                                }
                                else {
                                    if (wArray.defendingQueen[i][j] >= 1) {
                                        score -= 0.02*valuePiece - 0.02*900;
                                    }
                                }
                            }
                        }
                    }
               }
           }
       }
   }

   return score;
}

int intersection(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray) {
   int score = 0;

   for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // calculate for white
            if (wArray.totalNumDefending[i][j] >= 2)
            {
                if ((wArray.defendingMinor[i][j] == 1) && (wArray.defendingRook[i][j] >= 1)) {
                    score += 7;
                }
                if (wArray.defendingMinor[i][j] >= 2) {
                    score += 5;
                }
                if ((wArray.defendingMinor[i][j] >= 1) && (wArray.defendingQueen[i][j] >= 1)) {
                    score += 12;
                }
                if ((wArray.defendingRook[i][j] >= 1) && (wArray.defendingQueen[i][j] >= 1)) {
                    score += 15;
                }
            }
            // calculate for black
            if (bArray.totalNumDefending[i][j] >= 2)
            {
                if ((bArray.defendingMinor[i][j] == 1) && (bArray.defendingRook[i][j] >= 1)) {
                    score += 7;
                }
                if (bArray.defendingMinor[i][j] >= 2) {
                    score += 5;
                }
                if ((bArray.defendingMinor[i][j] >= 1) && (bArray.defendingQueen[i][j] >= 1)) {
                    score += 12;
                }
                if ((bArray.defendingRook[i][j] >= 1) && (bArray.defendingQueen[i][j] >= 1)) {
                    score += 15;
                }
            }
        }
   }

   return score;
}

// - 20 for an isolated p
// - 50 each for double isolated ps
int pawnStructure(const Board *board) {
   int score = 0;
   int colorConstant;

   for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // if the piece is a pawn
            if (board->squares[i][j].type == 1) {
                colorConstant = board->squares[i][j].color;
                // if there are no pawns in close proximity
                if ( pieceProximity(board, colorConstant, i, j, 1, 1, 1) == 0 ) {
                    score -= colorConstant*20;
                }
                // check for double isolated pawns
                if ( pieceProximity(board, colorConstant, i, j, 1, 1, 0) > 0 ) {
                    score -= colorConstant*50;
                }
            }
        }
   }

    return score;
}

// if 4 pawns are connected and close to promotion (3 or less moves away), + 600
int fourConnectedPawns(const Board *board) {
    int score = 0;
    int colorConstant;

    // are white pawns close to the end?
    for (int i = 5; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            colorConstant = 1;
            // if I find a pawn
            if (board->squares[i][j].type == 1) {
                // AND if I find 3 other pawns nearby
                if ( pieceProximity(board, colorConstant, i, j, 1, 2, 2) >= 3 ) {
                    score += colorConstant*600;
                    break;
                }
            }
        }
    }

    // are black pawns close to the end?
    for (int i = 0; i <= 3; i++){
        for (int j = 0; j <= 7; j++) {
            colorConstant = 1;
            // if I find a pawn
            if (board->squares[i][j].type == 1) {
                // AND if I find 3 other pawns nearby
                if ( pieceProximity(board, colorConstant, i, j, 1, 2, 2) >= 3 ) {
                    score += colorConstant*600;
                    break;
                }
            }
        }
    }

    // to be implemented
    return score;
}

int kingRankSafetyCalculation(const Board *board) {
    int score = 0;
    int colorConstant;

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // if chess piece is King
            if (board->squares[i][j].type == 6) {
                colorConstant = board->squares[i][j].color;

                if (colorConstant == 1) {
                    // if there are less than 2 pawns around the king, -50
                    if (pieceProximity(board, 1, i, j, 1, 2, 1) <= 2) {
                        score -= 50;
                    }
                    if (i == 0 && j <= 2) {
                        score += 100;
                    }
                    if (i == 1) {
                        score -= 50;
                    }
                    if (i == 2) {
                        score -= 100;
                    }
                    if (i == 3) {
                        score -= 300;
                    }
                    if (i >= 4) {
                        score -= 500;
                    }
                }

                if (colorConstant == -1) {
                    // if there are less than 2 pawns around the king, +50
                    if (pieceProximity(board, 1, i, j, 1, 2, 1) <= 2) {
                        score += 50;
                    }
                    if (i == 7 && j >= 6) {
                        score -= 100;
                    }
                    if (i == 6) {
                        score += 50;
                    }
                    if (i == 5) {
                        score += 100;
                    }
                    if (i == 4) {
                        score += 300;
                    }
                    if (i >= 3) {
                        score += 500;
                    }
                }
            }
        }
    }

    return score;
}

// is the bishop aligned on good diagonals
int bishopDiagonal(const Board *board) {
    int score = 0;
    int colorConstant;

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // if chess piece is bishop
            if (board->squares[i][j].type == 3) {
                colorConstant = board->squares[i][j].color;
                // white bishops
                if (colorConstant == 1) {
                    if (i == 1 && j == 1) {
                        score += colorConstant*30;
                    }
                    if (i == 1 && j == 6) {
                        score += colorConstant*30;
                    }
                }
                // black bishops
                if (colorConstant == -1) {
                    if (i == 6 && j == 1) {
                        score += colorConstant*30;
                    }
                    if (i == 6 && j == 6) {
                        score += colorConstant*30;
                    }
                }
            }
        }
    }

    return score;
}

// is the opponent king being attacked?
// +points for the strength of attack
/*
    + 50 for a q attacking a square defended by the enemy king
    + 30 for a bishop or n attacking such square
    +50 for a r on a semiopen file against the king
    +70 for a r on an open file against the king
    +80 for double rooks
*/
int attackOpponentKing(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray) {
    int score = 0;
    int colorConstant;

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // if chess piece is king
            if (board->squares[i][j].type == 6) {
                colorConstant = board->squares[i][j].color;
                if (colorConstant == 1) {
                    // check in a 1 unit radius around the King
                    for (int m = -1; m <= 1; m++) {
                        for (int n = -1; n<= 1; n++) {
                            // make sure indices are within bounds
                            if (i+m >= 0 && i+m < 8 && j+n >= 0 && j+n < 8) {
                                // one rook
                                if (wArray.defendingRook[i+m][j+n] == 1) {
                                    score -= colorConstant*50;
                                }
                                // two rooks
                                if (wArray.defendingRook[i+m][j+n] == 2) {
                                    score -= colorConstant*80;
                                }
                                // bishop and knight
                                if (wArray.defendingMinor[i+m][j+n] >= 1) {
                                    score -= wArray.defendingMinor[i+m][j+n]*colorConstant*30;
                                }
                                // queen
                                if (wArray.defendingQueen[i+m][j+n] > 0) {
                                    score -= colorConstant*50;
                                }
                            }
                        }
                    }
                }
                if (colorConstant == -1) {
                    // check in a 1 unit radius around the King
                    for (int m = -1; m <= 1; m++) {
                        for (int n = -1; n<= 1; n++) {
                            // make sure indices are within bounds
                            if (i+m >= 0 && i+m < 8 && j+n >= 0 && j+n < 8) {
                                // one rook
                                if (bArray.defendingRook[i+m][j+n] == 1) {
                                    score -= colorConstant*50;
                                }
                                // two rooks
                                if (bArray.defendingRook[i+m][j+n] == 2) {
                                    score -= colorConstant*80;
                                }
                                // bishop and knight
                                if (bArray.defendingMinor[i+m][j+n] >= 1) {
                                    score -= bArray.defendingMinor[i+m][j+n]*colorConstant*30;
                                }
                                // queen
                                if (bArray.defendingQueen[i+m][j+n] > 0) {
                                    score -= colorConstant*50;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return score;
}

// can the rook pin anything?
// for example: if the rook pins a bishop to the king, +50
// for example: if the rook pins a knight to the queen +50
int rookPinSomething(const Board *board, DefendingPiecesArray wArray, DefendingPiecesArray bArray) {
    int score = 0;
    int colorConstant;

    int wKingRow;
    int wKingColumn;
    int bKingRow;
    int bKingColumn;
    int wQueenRow;
    int wQueenColumn;
    int bQueenRow;
    int bQueenColumn;

    // integer storing type of piece first seen & second seen
    int firstPiece;
    int secondPiece;

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {

            // locate the kings
            if (board->squares[i][j].type == 6) {
                if (colorConstant == 1) {
                    wKingRow = i;
                    wKingColumn = j;
                }
                if (colorConstant == -1) {
                    bKingRow = i;
                    bKingColumn = j;
                }
            }
            // locate the queens
            if (board->squares[i][j].type == 5) {
                if (colorConstant == 1) {
                    wQueenRow = i;
                    wQueenColumn = j;
                }
                if (colorConstant == -1) {
                    bQueenRow = i;
                    bQueenColumn = j;
                }
            }

            // if chess piece is rook
            if (board->squares[i][j].type == 4) {
                colorConstant = board->squares[i][j].color;
                if (colorConstant == 1) {
                    // make sure rook is not dangling, aka if it is supported enough it won't get captured
                    if (wArray.totalNumDefending[i][j] > bArray.totalNumDefending[i][j]) {
                        if (bKingRow == i || bQueenRow == i) {
                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = -7; k < 0; k++) {
                                if (i+k >= 0 && i+k <= 7) {
                                    if (wArray.defendingRook[i+k][j] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i+k][j].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i+k][j].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }

                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = 1; k <= 7; k++) {
                                if (i+k >= 0 && i+k <= 7) {
                                    if (wArray.defendingRook[i+k][j] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i+k][j].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i+k][j].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }
                        }
                        if (bKingColumn == j || bQueenColumn == j) {
                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = -7; k < 0; k++) {
                                if (j+k >= 0 && j+k <= 7) {
                                    if (wArray.defendingRook[i][j+k] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i][j+k].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i][j+k].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }

                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = 1; k <= 7; k++) {
                                if (j+k >= 0 && j+k <= 7) {
                                    if (wArray.defendingRook[i][j+k] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i][j+k].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i][j+k].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }
                        }
                    }
                }
                if (colorConstant == -1) {
                     if (bArray.totalNumDefending[i][j] > wArray.totalNumDefending[i][j]) {
                        if (wKingRow == i || wQueenRow == i) {
                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = -7; k < 0; k++) {
                                if (i+k >= 0 && i+k <= 7) {
                                    if (bArray.defendingRook[i+k][j] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i+k][j].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i+k][j].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }

                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = 1; k <= 7; k++) {
                                if (i+k >= 0 && i+k <= 7) {
                                    if (bArray.defendingRook[i+k][j] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i+k][j].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i+k][j].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }
                        }
                        if (wKingColumn == j || wQueenColumn == j) {
                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = -7; k < 0; k++) {
                                if (j+k >= 0 && j+k <= 7) {
                                    if (bArray.defendingRook[i][j+k] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i][j+k].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i][j+k].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }

                            firstPiece = 0;
                            secondPiece = 0;
                            for (int k = 1; k <= 7; k++) {
                                if (j+k >= 0 && j+k <= 7) {
                                    if (bArray.defendingRook[i][j+k] != 0) {
                                        if (firstPiece != 0) {
                                            firstPiece = board->squares[i][j+k].type;
                                        }
                                        else {
                                            secondPiece = board->squares[i][j+k].type;
                                        }
                                    }
                                }
                            }

                            if (firstPiece == 5 || firstPiece == 6) {
                                score += colorConstant*50;
                            }
                            else {
                                if (firstPiece != 1) {
                                    if (secondPiece == 5 || secondPiece == 6) {
                                        score += colorConstant*50;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return score;
}