#include "earlygame.h"



// Control of center function
int controlOfCenter(const Board *board) {
    int score = 0;
    int colorConstant;

    // checks if a pawn is in these squares: e4, d4, e5, d5
    // if white pawn occupies the space +20, if black pawn then -20
    // if white minor piece +10, if black -10
    // colorConstant is 1 for white and -1 for black
    for (int i = 3; i <= 4; i++){
        for (int j = 3; j <= 4; j++){
        // check for pawns
            if (board->squares[i][j].type == 1){
                colorConstant = board->squares[i][j].color;
                score += colorConstant*20;
            }
            // check for bishop or knight
            if ((board->squares[i][j].type == 2) || (board->squares[i][j].type == 3)){
                colorConstant = board->squares[i][j].color;
                score += colorConstant*10;
            }
        }
    }

    return score;
}

// Control of large center function
int controlOfLargeCenter(const Board *board) {
    int score = 0;
    int colorConstant;

    // if white pawn occupies the space +10, if black pawn then -10
    // if white minor piece +10, if black -10
    // colorConstant is 1 for white and -1 for black
    for (int i = 2; i <= 5; i++){
        for (int j = 2; j <= 5; j++){
        // check for pawns
            if (board->squares[i][j].type == 1){
                colorConstant = board->squares[i][j].color;
                score += colorConstant*10;
            }
            // check for bishop or knight
            if ((board->squares[i][j].type == 2) || (board->squares[i][j].type == 3)){
                colorConstant = board->squares[i][j].color;
                score += colorConstant*10;
            }
        }
    }

    return score;
}
/* commented cause log.h have not been implemented
int orderOfDevelopment(Log *log) {
    int numMinorPiecesDeveloped = 0;
    int score = 0;
    int colorConstant = log->last->color;

    bool whiteBishopMoved = false;
    bool knightMoved = false;
    for (int i = 0; i < log->length; i++) {
        if (move->color == 1) {
            while
        }
        if (move->color == -1) {
            while
        }
    }

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // psuedo code
            // if knight develops before bishop +20 * colorConstant
            // if queen develops before bishop/knight -20 * colorConstant
            // if castling +50*colorConstant
            // if castling short. + 10
        }
    }

    return score;
}
*/
int underDevelopment(const Board *board) {
    int score = 0;

    // number of undeveloped pieces
    int numOfUndevelopedPiecesBlack = 0;
    int numOfUndevelopedPiecesWhite = 0;

    // checks white side knight and bishop
    if (board->squares[0][1].type == 2) {
        numOfUndevelopedPiecesWhite += 1;
    }
    if (board->squares[0][1].type == 3) {
        numOfUndevelopedPiecesWhite += 1;
    }
    if (board->squares[0][7].type == 2) {
        numOfUndevelopedPiecesWhite += 1;
    }
    if (board->squares[0][6].type == 3) {
        numOfUndevelopedPiecesWhite += 1;
    }

    // checks black side knight and bishop
    if (board->squares[7][1].type == 2) {
        numOfUndevelopedPiecesBlack += 1;
    }
    if (board->squares[7][1].type == 3) {
        numOfUndevelopedPiecesBlack += 1;
    }
    if (board->squares[7][7].type == 2) {
        numOfUndevelopedPiecesBlack += 1;
    }
    if (board->squares[7][6].type == 3) {
        numOfUndevelopedPiecesBlack += 1;
    }

    // if one player develops 2 or more minor pieces ahead of opponent, the player gets +175
    if (numOfUndevelopedPiecesWhite - numOfUndevelopedPiecesBlack >= 2) {
        score += 175;
    }
    if (numOfUndevelopedPiecesWhite - numOfUndevelopedPiecesBlack <= -2) {
        score -= 175;
    }

    return score;
}

int isPawnSupported(const Board *board) {
    int score = 0;
    int colorConstant;

    for (int i = 2; i <= 5; i++){
        for (int j = 1; j <= 6; j++) {
            // check for pawns
            if (board->squares[i][j].type == 1) {
                // check for support
                // if pawn is supported +20 for white
                colorConstant = board->squares[i][j].color;
                if ((board->squares[i-colorConstant*1][j-colorConstant*1].type == 1)||(board->squares[i-colorConstant*1][j+colorConstant*1].type == 1)) {
                    score += colorConstant*20;
                }
            }
        }
    }

    return score;
}
/* commented cause log.h have not been implemented
int isCastlingRights(Log *log) {
    // !!!
    // make sure to handle exception
    // if king has moved, but the move is a castling move, don't do anything
     int score = 0;
     bool kingHasMoved = log->whiteCastling
     int whitePoints = log->whiteCastlingRights ? 0 : -200;
     int blackPoints = log->blackCastlingRights ? 0 : 200;
     score = whitePoints + blackPoints;
     return score;
}
*/
int knightPinToKingOrQueen(const Board *board) {
    int score = 0;

    // check fow white's knight getting pinned to King
    if ((board->squares[2][2].type == 2) || (board->squares[1][3].type == 2) ){
        if (board->squares[1][3].type != 1) {
            if ((board->squares[3][1].type == 3)&&(board->squares[3][1].color == -1)) {
                score -= 40;
            }
            if ((board->squares[4][0].type == 3)&&(board->squares[4][0].color == -1)) {
                score -= 40;
            }
        }
    }

    // check fow white's knight getting pinned to Queen
    if ((board->squares[2][5].type == 2)||(board->squares[2][5].type == 2)) {
        if (board->squares[1][4].type == 0) {
            if ((board->squares[3][6].type == 3)&&(board->squares[3][6].color == -1)) {
                score -= 40;
            }
            if ((board->squares[4][7].type == 3)&&(board->squares[4][7].color == -1)) {
                score -= 40;
            }
        }
    }

    // check fow black's knight getting pinned
    if ((board->squares[2][5].type == 2)||(board->squares[1][4].type == 2)) {
        if (board->squares[1][4].type != 1) {
            if ((board->squares[4][1].type == 3)&&(board->squares[4][1].color == 1)) {
                score += 40;
            }
            if ((board->squares[3][0].type == 3)&&(board->squares[3][0].color == 1 )){
                score += 40;
            }
        }
    }

    // check fow black's knight getting pinned to Queen
    if ((board->squares[5][5].type == 2)||(board->squares[5][5].type == 2)) {
        if (board->squares[6][4].type == 0) {
            if ((board->squares[3][7].type == 3)&&(board->squares[3][7].color == -1)) {
                score += 40;
            }
            if ((board->squares[4][6].type == 3)&&(board->squares[4][6].color == -1)) {
                score += 40;
            }
        }
    }
    return score;
}
