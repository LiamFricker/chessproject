#include "endgame.h"

// checks the pawn structure of the chess board
// + 25 for a passer
// + 50 for a protected passer
// + 25 each plus + 50 for the tandem for two connected passers
int endGamePawnStructure(const Board *board) {
    int score = 0;
    int whiteScore = 0, blackScore = 0;
    //checks if there is a passer pawn
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            //checks if there is a white pawn near promotion
            if (board->squares[i][j].color == BLACK && board->squares[i][j].type == PAWN) {
                blackScore -= 25;
                //checks to see if that pawn is a passer pawn (ie if it is blocked)
                for (int k = 0; k < i; k++) {
                    if (board->squares[k][j].type != EMPTY) {
                        blackScore += 25;
                        break;
                    }

                }
                if (pieceProximity(board, BLACK, i, j, 1, 1, 1) >= 1) {
                    blackScore -= 25;
                }
            }
        }
    }

    //checks if there is a black passer pawn
    for (int i = 4; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            //checks if there is a black pawn near promotion
            if (board->squares[i][j].color == WHITE  && board->squares[i][j].type == PAWN) {
                whiteScore += 25;
                //checks to see if that pawn is a passer pawn (ie if it is blocked)
                for (int k = i+1; k < 8; k++) {
                    if (board->squares[k][j].type != EMPTY) {
                        whiteScore -= 25;
                        break;
                    }
                }
                if (pieceProximity(board, WHITE, i, j, 1, 1, 1) >= 1) {
                    whiteScore += 25;
                }
            }
        }
    }
    score = whiteScore + blackScore;
    return score;
}

//helper function with adjusted values for pieces in endgame
int endGamePieceValue(PieceType type) {
    int score;
    switch (type) {
        case EMPTY:
            score = 0;
            break;
        case PAWN:
            score = 10;
            break;
        case KNIGHT:
            score = 35;
            break;
        case BISHOP:
            score = 35;
            break;
        case ROOK:
            score = 55;
            break;
        case QUEEN:
            score = 90;
            break;
        case KING:
            score = 1000;
            break;
    }
    return score;
}

int isWinnableConfigurations(int knights, int bishops, int rooks, int queens) {
    int score = 0;
    if (bishops >= 2) {
        score += 9;
    }
    if (knights >= 2) {
        score += 7;
    }
    if (rooks >= 2) {
        score += 10;
    }
    if (bishops >= 1 && knights >= 1) {
        score += 8;
    }
    if (rooks >= 1 && knights >= 1) {
        score += 9;
    }
    if (rooks >= 1 && bishops >= 1) {
        score += 9;
    }
    if (bishops == 1 && knights == 1) {
        score += 8;
    }
    if (rooks == 1 && bishops == 1) {
        score += 9;
    }
    if (rooks == 1 && knights == 1) {
        score += 9;
    }
    if (rooks == 1 && bishops == 2) {
        score += 9;
    }
    if (rooks == 2 && bishops == 1) {
        score += 9;
    }
    if (rooks == 1 && knights == 2) {
        score += 9;
    }
    if (rooks == 2 && knights == 1) {
        score += 9;
    }
    if (bishops == 1 && knights == 2) {
        score += 8;
    }
    if (bishops == 2 && knights == 1) {
        score += 8;
    }
    if (bishops == 1 && rooks == 2) {
        score += 9;
    }
    if (bishops == 2 && rooks == 1) {
        score += 9;
    }
    if (knights == 1 && rooks == 2) {
        score += 9;
    }
    if (knights == 2 && rooks == 1) {
        score += 9;
    }
    if (knights == 1 && bishops == 2) {
        score += 8;
    }
    if (knights == 2 && bishops == 1) {
        score += 8;
    }
    if (bishops == 1 && rooks == 1 && knights == 1) {
        score += 8;
    }
    if (bishops == 1 && rooks == 1 && knights == 2) {
        score += 9;
    }
    if (bishops == 1 && rooks == 2 && knights == 1) {
        score += 9;
    }
    if (bishops == 2 && rooks == 1 && knights == 1) {
        score += 9;
    }
    if (knights == 1 && rooks == 1 && bishops == 1) {
        score += 8;
    }
    if (knights == 1 && rooks == 1 && bishops == 2) {
        score += 9;
    }
    if (knights == 1 && rooks == 2 && bishops == 1) {
        score += 9;
    }
    if (knights == 2 && rooks == 1 && bishops == 1) {
        score += 9;
    }
    if (bishops == 1 && knights == 1 && rooks == 1) {
        score += 8;
    }
    if (bishops == 1 && knights == 1 && rooks == 2) {
        score += 9;
    }
    if (bishops == 1 && knights == 2 && rooks == 1) {
        score += 9;
    }
    if (bishops == 2 && knights == 1 && rooks == 1) {
        score += 9;
    }
    return score;
}

// checks how many pieces each side has, and whether it is possible to still win
// for example, king + 2 rooks vs king + knight will always end on a win for king + 2 rooks
// unless stupid moves are played
int isWinnable(const Board *board) {
    int score = 0;
    int whiteScore = 0, blackScore = 0;
    int numWKnight = 0, numWBishop = 0, numWRook = 0, numWQueen = 0;
    int numBKnight = 0, numBBishop = 0, numBRook = 0, numBQueen = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].color == BLACK) {
                if (board->squares[i][j].type == KNIGHT) {
                    numBKnight++;
                } else if (board->squares[i][j].type == BISHOP) {
                    numBBishop++;
                } else if (board->squares[i][j].type == ROOK) {
                    numBRook++;
                } else if (board->squares[i][j].type == QUEEN) {
                    numBQueen++;
                }
            } else if (board->squares[i][j].color == WHITE) {
                if (board->squares[i][j].type == KNIGHT) {
                    numWKnight++;
                } else if (board->squares[i][j].type == BISHOP) {
                    numWBishop++;
                } else if (board->squares[i][j].type == ROOK) {
                    numWRook++;
                } else if (board->squares[i][j].type == QUEEN) {
                    numWQueen++;
                }
            }
        }
    }
    whiteScore = isWinnableConfigurations(numWKnight, numWBishop, numWRook, numWQueen);
    blackScore = -1 * isWinnableConfigurations(numBKnight, numBBishop, numBRook, numBQueen);
    score = whiteScore + blackScore;
    return score;
}



// checks if any pawn is 3 or less moves away from promotion
// the closer the pawn, the more points
// if pawn is protected add even more points
int promotionPawn(const Board *board) {
    int score = 0;
    int whiteScore = 0, blackScore = 0;
    //scans the first three rows of the board for a white pawn, awards different point amounts based off of
    for (int i = 1; i < 4; i++) {
        for (int j = 0 ; j < 8; j++) {
            if (board->squares[i][j].color == BLACK && board->squares[i][j].type == PAWN) {
                blackScore -= 25*(4-i);
                if (pieceProximity(board, BLACK, i, j, 1, 1, 1) >= 1) {
                    blackScore -= 25;
                }
            }
        }
    }

    for (int i = 4; i < 7; i++) {
        for (int j = 0 ; j < 8; j++) {
            if (board->squares[i][j].color == WHITE && board->squares[i][j].type == PAWN) {
                whiteScore += 25*(i - 3);
                if (pieceProximity(board, WHITE, i, j, 1, 1, 1) >= 1) {
                    whiteScore += 25;
                }
            }
        }
    }

    score = whiteScore + blackScore;
    return score;
}

//awards points if the pawns on the board are symmetrical
int symmetricalPawnStructure(const Board *board) {
    int score = 0, blackScore = 0, whiteScore = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].color == WHITE && board->squares[i][j].type == PAWN
                && board->squares[7-i][j].color == BLACK && board->squares[7-i][j].type == PAWN) {
                if (simpleEval(board) > 0) {
                    blackScore -= 35;
                } else if (simpleEval(board) < 0) {
                    whiteScore += 35;
                }
            }

        }
    }
    score = blackScore + whiteScore;
    return score;
}

//helper function to determine score of king's position in endgame board
int kingScore(int i, int j, Color color) {
    if (color == WHITE && i == 2 && (j == 2 || j == 3 || j == 4 || j == 5)) {
        return 25;
    } else if (color == BLACK && i == 5 && (j == 2 || j == 3 || j == 4 || j == 5)) {
        return -25;
    } else if (color == WHITE && i == 2) {
        return 75;
    } else if (color == WHITE && i == 3) {
        return 50;
    } else if (color == BLACK && i == 5) {
        return -75;
    } else if (color == BLACK && i == 4) {
        return -50;
    } else {
        return 0;
    }
}

int kingPosition(const Board *board) {
    int score = 0, whiteScore = 0, blackScore = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].type == KING && board->squares[i][j].color == WHITE) {
                whiteScore = kingScore(i, j, WHITE);
            }
            if (board->squares[i][j].type == KING && board->squares[i][j].color == BLACK) {
                blackScore = kingScore(i, j, BLACK);
            }
        }
    }
    score = whiteScore + blackScore;
    return score;
}