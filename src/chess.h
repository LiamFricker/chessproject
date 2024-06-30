#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
//#include "GUI.h"

// Enumeration for the types of chess pieces
typedef enum {
    EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
} PieceType;

typedef struct Position Position;
  struct Position {
    int x;
    int y;
  };

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
    bool king_moved[2];  // Index 0 for WHITE, 1 for BLACK
    bool rook_moved[2][2];  // [color][0 for left rook, 1 for right rook]
    int en_passant_x;  // Store the x-position of the pawn vulnerable to en passant
    int en_passant_y;  // Store the y-position of the pawn vulnerable to en passant
    bool en_passant_possible; // True if en passant capture is possible
} Board;

// Struct to represent a move
typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} Move;

// global variable representing previous board state for undo move
extern Board prevBoard;

// Function prototypes
void initialize_board(Board *board);
void displayBoard(const Board *board);
void copy_board(Board oldBoard, Board *newBoard);
void get_user_move_with_undo(int *sx, int *sy, int *ex, int *ey, bool *undo);
void get_user_move_without_undo(int *sx, int *sy, int *ex, int *ey);
void make_move(Board *board, int start_x, int start_y, int end_x, int end_y);
void undo_move (Board *board);
bool is_move_valid(const Board *board, int start_x, int start_y, int end_x, int end_y);
bool validate_pawn_move(const Board *board, Piece pawn, int sx, int sy, int ex, int ey, Piece end_piece);
bool validate_knight_move(int sx, int sy, int ex, int ey);
bool validate_bishop_move(int sx, int sy, int ex, int ey);
bool validate_rook_move(int sx, int sy, int ex, int ey);
bool validate_queen_move(int sx, int sy, int ex, int ey);
bool validate_king_move(const Board *board, int sx, int sy, int ex, int ey, bool king_moved);
bool is_square_under_attack(const Board *board, int x, int y, Color color);
bool is_path_clear(const Board *board, int sx, int sy, int ex, int ey);
bool can_attack(const Board *board, int sx, int sy, int tx, int ty);
bool is_king_in_check(const Board *board, Color color);
bool validate_pawn_attack(Piece pawn, int sx, int sy, int tx, int ty);
void promote_pawn(Board *board, int x, int y);
bool is_checkmate(const Board *board, Color color);
bool is_stalemate(const Board *board, Color color);
Move* get_valid_moves(const Board *board, Color color, int *possible_moves_count);
Position* get_valid_moves_withStart(const Board *board, Color color, int *possible_moves_count, int start_x, int start_y);
bool correct_side(Board *board, int sx, int sy, Color side);

#endif // CHESS_H
