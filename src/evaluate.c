#include "evaluate.h"

int simpleEval(const Board *board) {
    int numPawns = 0;
    int numKnight = 0;
    int numBishop = 0;
    int numRook = 0;
    int numQueen = 0;

    int colorConstant;

    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            if (board->squares[i][j].type == 1) {
                colorConstant = board->squares[i][j].color;
                numPawns += colorConstant*1;
            }
            if (board->squares[i][j].type == 2) {
                colorConstant = board->squares[i][j].color;
                numKnight += colorConstant*1;
            }
            if (board->squares[i][j].type == 3) {
                colorConstant = board->squares[i][j].color;
                numBishop += colorConstant*1;
            }
            if (board->squares[i][j].type == 4) {
                colorConstant = board->squares[i][j].color;
                numRook += colorConstant*1;
            }
            if (board->squares[i][j].type == 5) {
                colorConstant = board->squares[i][j].color;
                numQueen += colorConstant*1;
            }
        }
    }
    // note: bishop is worth slightly more than a knight (310 vs 300)
    return 900*numQueen + 500*numRook + 310*numBishop + 300*numKnight+ 100*numPawns;
}

int complexEval(const Board *board) {
    int score = 0;
    int piecesLeftOnTheBoard = 0;

    // num of pieces left on board to trigger function calls
    // adjust these values as necessary to fine tune the engine
    int earlyGameThreshold = 25; // if piecesLeftOnTheBoard >= 25, then include earlyGame functions
    int midGameThreshold = 24; // if piecesLeftOnTheBoard <= 23, then include midGame functions
    int endGameThreshold = 14; // if piecesLeftOnTheBoard <= 24, then include endGame functions
    // IMPORTANT NOTE: some functions are used in MULTIPLE parts of the game

    DefendingPiecesArray wArray = whiteControlArray(board);
    DefendingPiecesArray bArray = whiteControlArray(board);

    // check for how many pieces are left on the board
    // the number of pieces left determine whether the game is in early game, mid game, or end game
    // please keep in mind that the boundaries of early, mid, and end game is not fixed
    for (int i = 0; i <= 7; i++){
        for (int j = 0; j <= 7; j++) {
            // if piece type is not null
            if (board->squares[i][j].type != 0) {
                piecesLeftOnTheBoard += 1;
            }
        }
    }

    // early game
    if (piecesLeftOnTheBoard >= earlyGameThreshold) {
        score += controlOfCenter(board);
        score += controlOfLargeCenter(board);
        score += underDevelopment(board);
        score += isPawnSupported(board);
        score += knightPinToKingOrQueen(board);

        // mid game functions important in early game
        score += 0.8*pieceCoordination(board, wArray, bArray);
        // why 0.8? because this is somewhat less important in early game
        // 0.8 is a scaling down factor because control of center is typically more important
    }

    // mid game
    if (piecesLeftOnTheBoard <= midGameThreshold) {
        // early game functions that are still important in mid game
        score += 0.5*controlOfCenter(board); // scaling factor can be fine tuned for improvements
        score += 0.5*controlOfLargeCenter(board); // scaling factor can be fine tuned for improvements
        score += isPawnSupported(board);
        score += knightPinToKingOrQueen(board);
        // mid game functions
        score += pieceMobility(board);
        score += pawnMobility(board, wArray, bArray);
        score += pieceCoordination(board, wArray, bArray);
        score += intersection(board, wArray, bArray);
        score += pawnStructure(board);
        score += fourConnectedPawns(board);
        score += bishopDiagonal(board);
        score += attackOpponentKing(board, wArray, bArray);
        score += rookPinSomething(board, wArray, bArray);
        // do many more stuff
    }

    if (piecesLeftOnTheBoard > endGameThreshold) {
        // when the game is not in end game state, make sure the king does not move up
        score += kingRankSafetyCalculation(board);
    }

    // end game
    if (piecesLeftOnTheBoard <= endGameThreshold) {
        score += endGamePawnStructure(board);
        score += isWinnable(board);
        score += promotionPawn(board);
        score += kingPosition(board);
        // do many more stuff

        score += symmetricalPawnStructure(board);
    }

    score += simpleEval(board);

    return score;
}
