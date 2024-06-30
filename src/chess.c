#include "chess.h"

// Initialize the chess board (and prevBoard) with the initial pieces setup reversed for black and white
Board prevBoard;

void initialize_board(Board *board) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board->squares[i][j].type = EMPTY;
            board->squares[i][j].color = NONE;
        }
    }

    // Initialize pawns
    for (int j = 0; j < 8; j++) {
        board->squares[6][j].type = PAWN; // Black pawns now on 7th row (index 6)
        board->squares[6][j].color = BLACK;
        board->squares[1][j].type = PAWN; // White pawns now on 2nd row (index 1)
        board->squares[1][j].color = WHITE;
    }

    // Setup Rooks
    board->squares[7][0].type = board->squares[7][7].type = ROOK; // Black Rooks
    board->squares[7][0].color = BLACK;
    board->squares[7][7].color = BLACK;
    board->squares[0][0].type = board->squares[0][7].type = ROOK; // White Rooks
    board->squares[0][0].color = WHITE;
    board->squares[0][7].color = WHITE;

    // Setup Knights
    board->squares[7][1].type = board->squares[7][6].type = KNIGHT; // Black Knights
    board->squares[7][1].color = board->squares[7][6].color = BLACK;
    board->squares[0][1].type = board->squares[0][6].type = KNIGHT; // White Knights
    board->squares[0][1].color = board->squares[0][6].color = WHITE;

    // Setup Bishops
    board->squares[7][2].type = board->squares[7][5].type = BISHOP; // Black Bishops
    board->squares[7][2].color = board->squares[7][5].color = BLACK;
    board->squares[0][2].type = board->squares[0][5].type = BISHOP; // White Bishops
    board->squares[0][2].color = board->squares[0][5].color = WHITE;

    // Setup Queens
    board->squares[7][3].type = QUEEN; // Black Queen
    board->squares[7][3].color = BLACK;
    board->squares[0][3].type = QUEEN; // White Queen
    board->squares[0][3].color = WHITE;

    // Setup Kings
    board->squares[7][4].type = KING; // Black King
    board->squares[7][4].color = BLACK;
    board->squares[0][4].type = KING; // White King
    board->squares[0][4].color = WHITE;

    board->king_moved[WHITE] = false;
    board->king_moved[BLACK] = false;
    board->rook_moved[WHITE][0] = false;  // Left rook
    board->rook_moved[WHITE][1] = false;  // Right rook
    board->rook_moved[BLACK][0] = false;
    board->rook_moved[BLACK][1] = false;

    board->en_passant_possible = false;
    board->squares[7][0].color = BLACK;
    board->squares[7][7].color = BLACK;

    // initialize prevBoard as well by copying contents over
    copy_board(*board, &prevBoard);
}
void displayBoard(const Board *board) {
    // Print the top border
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

// Function to copy one board to another
void copy_board(Board oldBoard, Board *newBoard) {

    // copy over pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            newBoard->squares[i][j] = oldBoard.squares[i][j];
        }
    }

    // copy over king moved and rook moved markers
    newBoard->king_moved[0] = oldBoard.king_moved[0];
    newBoard->king_moved[1] = oldBoard.king_moved[1];
    newBoard->rook_moved[0][0] = oldBoard.rook_moved[0][0];
    newBoard->rook_moved[0][1] = oldBoard.rook_moved[0][1];
    newBoard->rook_moved[1][0] = oldBoard.rook_moved[1][0];
    newBoard->rook_moved[1][1] = oldBoard.rook_moved[1][1];

    // copy over en passant markers
    newBoard->en_passant_x = oldBoard.en_passant_x;
    newBoard->en_passant_y = oldBoard.en_passant_y;
    newBoard->en_passant_possible = oldBoard.en_passant_possible;
}

// Function to get a move from the user with the possibility of undoing it
void get_user_move_with_undo(int *sx, int *sy, int *ex, int *ey, bool *undo) {
    char s[6];  // Buffer to include newline and null terminator
    bool valid_input = false;
    while (!valid_input) {
        printf("Enter your move (e.g., E2E4), or type 'undo' to undo your previous move: ");
        if (fgets(s, sizeof(s), stdin)) {
            // Clear the input buffer if input is longer than expected
            if (!strchr(s, '\n')) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            if (isalpha(s[0]) && isdigit(s[1]) && isalpha(s[2]) && isdigit(s[3]) && s[4] == '\n') {
                *sx = toupper(s[0]) - 'A';  // Convert column letter to index
                *sy = s[1] - '1';          // Adjusted to map input to internal indices correctly
                *ex = toupper(s[2]) - 'A';  // Convert column letter to index
                *ey = s[3] - '1';          // Adjusted to map input to internal indices correctly
                valid_input = true;
            }
            else if (strcmp(s, "undo\n") == 0) { // Check if user wants to undo move
                *undo = true;
                valid_input = true;
            }
            else {
                printf("Invalid format, please try again.\n");
            }
        } else {
            printf("Error reading input, please try again.\n");
        }
    }
}

bool correct_side(Board *board, int sx, int sy, Color side){

    if (board->squares[sy][sx].color == side){
        //printf("truetruetrue");
        return true;
    }
    else{
        //printf("falsefalsefalse");
        return false;
    }

}

// Function to get a move from the user without the possibility of undoing it
void get_user_move_without_undo(int *sx, int *sy, int *ex, int *ey) {
    char s[6];  // Buffer to include newline and null terminator
    bool valid_input = false;
    while (!valid_input) {
        printf("You undid your last move, now enter your new move (e.g., E2E4): ");
        if (fgets(s, sizeof(s), stdin)) {
            // Clear the input buffer if input is longer than expected
            if (!strchr(s, '\n')) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            if (isalpha(s[0]) && isdigit(s[1]) && isalpha(s[2]) && isdigit(s[3]) && s[4] == '\n') {
                *sx = toupper(s[0]) - 'A';  // Convert column letter to index
                *sy = s[1] - '1';          // Adjusted to map input to internal indices correctly
                *ex = toupper(s[2]) - 'A';  // Convert column letter to index
                *ey = s[3] - '1';          // Adjusted to map input to internal indices correctly
                valid_input = true;
            }
            else {
                printf("Invalid format, please try again.\n");
            }
        } else {
            printf("Error reading input, please try again.\n");
        }
    }
}

// Function to make a move
void make_move(Board *board, int start_x, int start_y, int end_x, int end_y) {

    if (is_move_valid(board, start_x, start_y, end_x, end_y)) {
        Piece moving_piece = board->squares[start_y][start_x];
        
        // Clear the starting position initially
        board->squares[start_y][start_x] = (Piece){EMPTY, NONE};

        // Check for castling move
        if (moving_piece.type == KING && abs(end_x - start_x) == 2) {
            // Move the king
            board->squares[end_y][end_x] = moving_piece;

            // Calculate and move the rook for castling
            int rook_start_x = (end_x > start_x) ? 7 : 0; // Rook's original position
            int rook_end_x = (end_x > start_x) ? end_x - 1 : end_x + 1; // Rook's new position next to the king
            board->squares[end_y][rook_end_x] = board->squares[start_y][rook_start_x];
            board->squares[start_y][rook_start_x] = (Piece){EMPTY, NONE};
        } 
        else if (moving_piece.type == PAWN) {
            // Move the pawn
            board->squares[end_y][end_x] = moving_piece;
            
            // Handle potential pawn promotion
            if (end_y == 0 || end_y == 7) {
                promote_pawn(board, end_x, end_y);
            }
            // Check for en passant capture
            else if (board->en_passant_possible && end_x == board->en_passant_x && end_y == board->en_passant_y) {
                board->squares[board->en_passant_y][board->en_passant_x] = (Piece){EMPTY, NONE};  // Capture the pawn
                board->en_passant_possible = false;  // Reset en passant possibility
            }
            // Set en passant possibility if the pawn moves two squares forward
            else if (abs(start_y - end_y) == 2) {
                board->en_passant_x = end_x;
                board->en_passant_y = (start_y + end_y) / 2; // Position between start and end y
                board->en_passant_possible = true;
            } 
            else {
                board->en_passant_possible = false;
            }
        } 
        else {
            // Regular move for other pieces
            board->squares[end_y][end_x] = moving_piece;
            board->en_passant_possible = false;  // Reset en passant flag if it was set
        }
    } 
    else {
        printf("Invalid move\n");
    }
}

// Function to undo a move, makes use of global variable prevBoard
void undo_move(Board *board) {
    copy_board(prevBoard, board);
}

// Check if a move is valid
bool is_move_valid(const Board *board, int start_x, int start_y, int end_x, int end_y) {


    if (start_x == end_x && start_y == end_y) {
        return false; // No move made
    }
    if (end_x < 0 || end_x >= 8 || end_y < 0 || end_y >= 8) {
        return false; // Out of bounds
    }


    Piece start_piece = board->squares[start_y][start_x];
    Piece end_piece = board->squares[end_y][end_x];

    if (start_piece.color == end_piece.color && end_piece.type != EMPTY) {
        return false; // Cannot capture own piece
    }
    // implementation for checking whether King is in check
    Board *temporaryBoard = malloc(sizeof(Board)); // Allocate memory for temporaryBoard
    if (!temporaryBoard) {
        fprintf(stderr, "Memory allocation failed\n");
        return false; // Properly handle memory allocation failure
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            temporaryBoard->squares[i][j].type = board->squares[i][j].type;
            temporaryBoard->squares[i][j].color = board->squares[i][j].color;
        }
    }
    //copy_board(*board, tempBoard);
    Piece moving_piece = start_piece;
    // Clear the starting position initially
    temporaryBoard->squares[start_y][start_x] = (Piece){EMPTY, NONE};
    // Make the end position the moving_piece
    temporaryBoard->squares[end_y][end_x] = moving_piece;
    int tempBoardColor = moving_piece.color;
    if (is_king_in_check(temporaryBoard, tempBoardColor)) {
        // return false if the King becomes in check when the move is played
        return false;
    }
    //*/

    switch (start_piece.type) {
        case PAWN:
            // efficieny update
            // skip pawn validation if attempted "move" is three or more spaces apart row wise
            if (abs(end_y - start_y) >= 3) {
                return false;
            }
            // skip pawn validation if attempted "move" is two or more spaces apart column wise
            if (abs(end_x - start_x) >= 2) {
                return false;
            }
            return validate_pawn_move(board, start_piece, start_x, start_y, end_x, end_y, end_piece);
        case KNIGHT:
            return validate_knight_move(start_x, start_y, end_x, end_y);
        case BISHOP:
            return validate_bishop_move(start_x, start_y, end_x, end_y) && is_path_clear(board, start_x, start_y, end_x, end_y);
        case ROOK:
            return validate_rook_move(start_x, start_y, end_x, end_y) && is_path_clear(board, start_x, start_y, end_x, end_y);
        case QUEEN:
            return validate_queen_move(start_x, start_y, end_x, end_y) && is_path_clear(board, start_x, start_y, end_x, end_y);
        case KING:
            return validate_king_move(board, start_x, start_y, end_x, end_y, board->king_moved[board->squares[start_y][start_x].color]);
        case EMPTY:
            return false; // Empty start means no piece to move
        default:
            return false;
    }
}

// Validate specific pawn movements after switching starting positions
bool validate_pawn_move(const Board *board, Piece pawn, int sx, int sy, int ex, int ey, Piece end_piece) {
    int direction = pawn.color == WHITE ? 1 : -1;  // White moves down, Black moves up

    // Move one square forward
    if (sx == ex && ey == sy + direction && end_piece.type == EMPTY) {
        return true; // Standard single-step move
    }
    // Move two squares forward from initial position
    if (sx == ex && ey == sy + 2 * direction && sy == (pawn.color == WHITE ? 1 : 6) &&
        end_piece.type == EMPTY && board->squares[sy + direction][sx].type == EMPTY) {
        return true; // Initial double-step move is valid if both steps are clear
    }
    // Capture diagonally
    if ((ex == sx + 1 || ex == sx - 1) && ey == sy + direction &&
        end_piece.color != pawn.color && end_piece.type != EMPTY) {
        return true; // Diagonal capture
    }
    // Check for en passant capture
    if (board->en_passant_possible && ex == board->en_passant_x && ey == board->en_passant_y &&
        ((board->squares[sy][sx].color == WHITE && sy == 3 && ey == 2) ||
         (board->squares[sy][sx].color == BLACK && sy == 4 && ey == 5))) {
        return true;
    }
    return false; // If none of the valid moves apply, return false
}


bool validate_knight_move(int sx, int sy, int ex, int ey) {
    return (abs(ex - sx) == 2 && abs(ey - sy) == 1) || (abs(ex - sx) == 1 && abs(ey - sy) == 2);
}

bool validate_bishop_move(int sx, int sy, int ex, int ey) {
    return abs(ex - sx) == abs(ey - sy);
}

bool validate_rook_move(int sx, int sy, int ex, int ey) {
    return sx == ex || sy == ey;
}

bool validate_queen_move(int sx, int sy, int ex, int ey) {
    return validate_bishop_move(sx, sy, ex, ey) || validate_rook_move(sx, sy, ex, ey);
}

bool validate_king_move(const Board *board, int sx, int sy, int ex, int ey, bool king_moved) {
    // Standard move validation for one-square move in any direction
    if (abs(ex - sx) <= 1 && abs(ey - sy) <= 1) {
        return true;
    }

    // Castling move validation
    if (!king_moved && sy == ey && (ex == sx + 2 || ex == sx - 2)) {
        int rook_x = (ex == sx + 2) ? 7 : 0; // Rook position for kingside or queenside castling
        int rook_idx = (ex == sx + 2) ? 1 : 0; // Right or left rook
        Color color = board->squares[sy][sx].color;

        // Check if the corresponding rook has moved
        if (!board->rook_moved[color][rook_idx] && is_path_clear(board, sx, sy, rook_x, sy)) {
            // Check if all squares between the king's start and end positions (including the rook's square) are not under attack
            int step = (ex > sx) ? 1 : -1;
            for (int check_x = sx; check_x != ex + step; check_x += step) {
                if (is_square_under_attack(board, check_x, sy, color)) {
                    return false;
                }
            }
            return true; // Castling is valid
        }
    }

    return false; // If none of the valid conditions are met, return false
}

// Function to check if a square (x, y) is under attack by any piece of the opposite color
bool is_square_under_attack(const Board *board, int x, int y, Color color) {
    Color opponent_color = (color == WHITE) ? BLACK : WHITE;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece piece = board->squares[i][j];
            if (piece.color == opponent_color) {
                if (can_attack(board, j, i, x, y)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Check if the path between two points is clear
bool is_path_clear(const Board *board, int sx, int sy, int ex, int ey) {
    int dx = (ex - sx) / (abs(ex - sx) ? abs(ex - sx) : 1);
    int dy = (ey - sy) / (abs(ey - sy) ? abs(ey - sy) : 1);
    int x = sx + dx, y = sy + dy;

    while (x != ex || y != ey) {
        if (board->squares[y][x].type != EMPTY) {
            return false;
        }
        x += dx;
        y += dy;
    }
    return true;
}

// Function to check if a particular move by an enemy piece can attack a position (used in is_king_in_check)
bool can_attack(const Board *board, int sx, int sy, int tx, int ty) {
    Piece attacker = board->squares[sy][sx];
    switch (attacker.type) {
        case PAWN:
            return validate_pawn_attack(attacker, sx, sy, tx, ty);
        case KNIGHT:
            return validate_knight_move(sx, sy, tx, ty);
        case BISHOP:
            return validate_bishop_move(sx, sy, tx, ty) && is_path_clear(board, sx, sy, tx, ty);
        case ROOK:
            return validate_rook_move(sx, sy, tx, ty) && is_path_clear(board, sx, sy, tx, ty);
        case QUEEN:
            return validate_queen_move(sx, sy, tx, ty) && is_path_clear(board, sx, sy, tx, ty);
        case KING:
            return validate_king_move(board, sx, sy, tx, ty, board->king_moved[board->squares[sy][sx].color]);
        default:
            return false;
    }
}

// Check if the king of the specified color is in check
bool is_king_in_check(const Board *board, Color color) {
    int king_x = -1, king_y = -1;

    // Find the king's position
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].type == KING && board->squares[i][j].color == color) {
                king_x = j;
                king_y = i;
                break;
            }
        }
        if (king_x != -1) break;
    }

    // Check all possible moves by all opponent pieces to see if they can attack the king
    Color opponent_color = (color == WHITE) ? BLACK : WHITE;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].color == opponent_color) {
                if (can_attack(board, j, i, king_x, king_y)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void promote_pawn(Board *board, int x, int y) {
    char s[10];  // Buffer to hold input, including potential extra characters
    printf("Promote pawn to (Q/R/B/N): ");
    while (fgets(s, sizeof(s), stdin)) {
        // Clear the input buffer if the input line is too long
        if (strchr(s, '\n') == NULL) {
            while (fgets(s, sizeof(s), stdin) && strchr(s, '\n') == NULL);
            printf("Input too long, please enter a single character (Q/R/B/N): ");
            continue;
        }

        // Ensure input is a valid promotion choice
        if (strlen(s) == 2 && strchr("QRBNqrbn", s[0])) {
            // Set the piece type based on input, converting to uppercase to handle both cases
            switch (toupper(s[0])) {
                case 'Q':
                    board->squares[y][x].type = QUEEN;
                    break;
                case 'R':
                    board->squares[y][x].type = ROOK;
                    break;
                case 'B':
                    board->squares[y][x].type = BISHOP;
                    break;
                case 'N':
                    board->squares[y][x].type = KNIGHT;
                    break;
            }
            // Determine the color of the piece to promote based on its current color
            board->squares[y][x].color = board->squares[y][x].color;  // This retains the original color
            break;
        } else {
            printf("Invalid choice, please try again (Q/R/B/N): ");
        }
    }
}


// Implement the pawn attack validation for checking
bool validate_pawn_attack(Piece pawn, int sx, int sy, int tx, int ty) {
    int direction = pawn.color == WHITE ? 1 : -1;  // Adjusted direction based on new starting positions
    return (tx == sx + 1 || tx == sx - 1) && ty == sy + direction;
}

// Checkmate and stalemate functions
bool is_checkmate(const Board *board, Color color) {
    if (!is_king_in_check(board, color)) {
        return false; // not in check
    }

    // Try all possible moves for all pieces of the color of the current player
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].color == color) {
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        if (is_move_valid(board, j, i, y, x)) {
                            Board temp_board = *board;
                            make_move(&temp_board, j, i, y, x);
                            if (!is_king_in_check(&temp_board, color)) {
                                return false; // Found a valid move that !check
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // No is_move_valid, checkmate
}

bool is_stalemate(const Board *board, Color color) {
    if (is_king_in_check(board, color)) {
        return false; // The king is in check, no stalemate
    }

    // Try all possible moves for all pieces of the color of the current player
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board->squares[i][j].color == color) {
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 8; y++) {
                        if (is_move_valid(board, j, i, y, x)) {
                            return false; // Found a valid move, not stalemate
                        }
                    }
                }
            }
        }
    }
    return true; // No valid moves available, stalemate
}

// Returns a list (pointer to array of type Move) of all possible valid moves for a given color
Move* get_valid_moves(const Board *board, Color color, int *possible_moves_count) {

    /* allocate memory for the maximum possible number of moves
    16 max pieces for each color, each piece can have up to 27 legal moves */
    Move* moves = (Move*)malloc(16 * 27 * sizeof(Move));

    // return null if malloc fails
    if (moves == NULL) {
        *possible_moves_count = 0;
        return NULL;
    }

    int count = 0;

    // go through every square
    for (int start_y = 0; start_y < 8; start_y++) {
        for (int start_x = 0; start_x < 8; start_x++) {
            // if piece is of the color we're interested in:
            if (board->squares[start_y][start_x].color == color) {
                // go through all possible destination squares
                for (int end_y = 0; end_y < 8; end_y++) {
                    for (int end_x = 0; end_x < 8; end_x++) {
                        if (is_move_valid(board, start_x, start_y, end_x, end_y)) {
                            // add move entry to array and increment count
                            moves[count].start_x = start_x;
                            moves[count].start_y = start_y;
                            moves[count].end_x = end_x;
                            moves[count].end_y = end_y;
                            count++;
                        }
                    }
                }
            }
        }
    }

    // resize the array to the actual number of moves found, save memory space
    moves = (Move*)realloc(moves, count * sizeof(Move));

    // return null if realloc fails
    if (moves == NULL && count > 0) {
        free(moves);
        *possible_moves_count = 0;
        return NULL;
    }

    *possible_moves_count = count;
    return moves;
}

// Returns a list of position of all possible valid moves for a given starting position
Position* get_valid_moves_withStart(const Board *board, Color color, int *possible_moves_count, int start_x, int start_y) {

    /* allocate memory for the maximum possible number of moves
    16 max pieces for each color, each piece can have up to 27 legal moves */
    Position* moves = (Position*)malloc(27 * sizeof(Position));

    // return null if malloc fails
    if (moves == NULL) {
        *possible_moves_count = 0;
        return NULL;
    }

    int count = 0;

    // go through every square
    
    // if piece is of the color we're interested in:
    if (board->squares[start_y][start_x].color == color) {
        // go through all possible destination squares
        for (int end_y = 0; end_y < 8; end_y++) {
            for (int end_x = 0; end_x < 8; end_x++) {
                if (is_move_valid(board, start_x, start_y, end_x, end_y)) {
                    // add move entry to array and increment count
                    moves[count].x = end_x;
                    moves[count].y = end_y;
                    count++;
                }
            }
        }
    }



    // resize the array to the actual number of moves found, save memory space
    moves = (Position*)realloc(moves, count * sizeof(Position));

    // return null if realloc fails
    if (moves == NULL && count > 0) {
        free(moves);
        *possible_moves_count = 0;
        return NULL;
    }

    *possible_moves_count = count;
    return moves;
}