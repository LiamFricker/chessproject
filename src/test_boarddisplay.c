#include <stdio.h>

typedef enum {
    EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
} PieceType;

// Enumeration for the color of chess pieces
typedef enum {
    BLACK = -1,
    WHITE = 1,
    NONE = 0
} Color;

// Struct to represent a chess piece
typedef struct {
    PieceType type;
    Color color;
} Piece;

// Struct to represent a chess board
typedef struct {
    Piece squares[8][8];
    /*
    bool king_moved[2];  // Index 0 for WHITE, 1 for BLACK
    bool rook_moved[2][2];  // [color][0 for left rook, 1 for right rook]
    int en_passant_x;  // Store the x-position of the pawn vulnerable to en passant
    int en_passant_y;  // Store the y-position of the pawn vulnerable to en passant
    bool en_passant_possible; // True if en passant capture is possible
    */
} Board;

void initialize_board(Board *board);
void displayBoard(const Board *board);

int main() {
    Board board;
    initialize_board(&board);
    displayBoard(&board);

}

void initialize_board(Board *board) {
    // Clear all squares first
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board->squares[i][j].type = EMPTY;
            board->squares[i][j].color = NONE;
        }
    }

    // Place black pieces
    board->squares[0][0].type = ROOK;
    board->squares[0][0].color = BLACK;
    board->squares[0][7].type = ROOK;
    board->squares[0][7].color = BLACK;
    board->squares[0][1].type = KNIGHT;
    board->squares[0][1].color = BLACK;
    // Simulate that one knight has moved
    board->squares[2][2].type = KNIGHT;
    board->squares[2][2].color = BLACK;
    board->squares[0][2].type = BISHOP;
    board->squares[0][2].color = BLACK;
    board->squares[0][5].type = BISHOP;
    board->squares[0][5].color = BLACK;
    board->squares[0][3].type = QUEEN;
    board->squares[0][3].color = BLACK;
    board->squares[0][4].type = KING;
    board->squares[0][4].color = BLACK;

    // Place black pawns and simulate some movement
    for (int j = 0; j < 8; j++) {
        if (j != 3) { // Assume pawn at column d has moved
            board->squares[1][j].type = PAWN;
            board->squares[1][j].color = BLACK;
        }
    }
    // Simulate pawn at d4
    board->squares[3][3].type = PAWN;
    board->squares[3][3].color = BLACK;

    // Place white pieces
    board->squares[7][0].type = ROOK;
    board->squares[7][0].color = WHITE;
    board->squares[7][7].type = ROOK;
    board->squares[7][7].color = WHITE;
    board->squares[7][1].type = KNIGHT;
    board->squares[7][1].color = WHITE;
    board->squares[7][6].type = KNIGHT;
    board->squares[7][6].color = WHITE;
    board->squares[7][2].type = BISHOP;
    board->squares[7][2].color = WHITE;
    board->squares[7][5].type = BISHOP;
    board->squares[7][5].color = WHITE;
    board->squares[7][3].type = QUEEN;
    board->squares[7][3].color = WHITE;
    board->squares[7][4].type = KING;
    board->squares[7][4].color = WHITE;

    // Place white pawns and simulate some movement
    for (int j = 0; j < 8; j++) {
        if (j != 4) { // Assume pawn at column e has moved
            board->squares[6][j].type = PAWN;
            board->squares[6][j].color = WHITE;
        }
    }
    // Simulate pawn at e4
    board->squares[4][4].type = PAWN;
    board->squares[4][4].color = WHITE;
}

void displayBoard(const Board *board) {
    printf("\n  +----+----+----+----+----+----+----+----+\n");
    
    // Loop through each row of the board
    for (int i = 7; i >= 0; i--) {
        printf("%d |", i + 1); // Print the row number
        for (int j = 0; j < 8; j++) {
            char c = ' ';
            Piece p = board->squares[i][j];
            if (p.type != EMPTY) {
                c = (p.type == PAWN) ? 'P' :
                    (p.type == KNIGHT) ? 'N' :
                    (p.type == BISHOP) ? 'B' :
                    (p.type == ROOK) ? 'R' :
                    (p.type == QUEEN) ? 'Q' :
                    (p.type == KING) ? 'K' : ' ';
                printf(" %c%c |", (p.color == BLACK) ? 'b' : 'w', c);
            } else {
                printf("    |"); // Empty space formatting
            }
        }
        // Print the row border after each row
        printf("\n  +----+----+----+----+----+----+----+----+\n");
    }

    // Print the column labels at the bottom
    printf("    a    b    c    d    e    f    g    h\n");
}

