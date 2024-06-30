#include "GUI.h"

//Global Vars (YES BAD PRACTICE I KNOW BUT ITS MY GUI AND IM DOING IT THIS WAY)

int offset_x = 258;//258;//(1000-489)/2 + 3;
int offset_y = 158;//158;//(800-489)/2 +3;

//Menu Sprites
SDL_Surface *background = NULL, *board_setup = NULL, *difficulty = NULL, *whichside = NULL, *timermenu = NULL, *timermenu1 = NULL,
*gamemode = NULL, *white_difficulty = NULL, *black_difficulty = NULL, *checkTerminal = NULL, *startGame = NULL, *skiptogame = NULL; 

//Game Sprites
SDL_Surface *square = NULL, *BPawn = NULL, *WPawn = NULL, *BRook = NULL, *WRook = NULL, *BBishop = NULL,
*WBishop = NULL, *BQueen = NULL, *WQueen = NULL, *BKing = NULL, *WKing = NULL, *BKnight = NULL,
*WKnight = NULL, *ChessBoard = NULL, *green = NULL;

//Game Buttons
SDL_Surface *history = NULL, *terminalInput = NULL, *undobutton = NULL, *rules = NULL, *resign = NULL; 

int flipDirection = 1;
bool wasButtonJustDown = false;
bool FOLLOWINGMOUSE = false;

void instantiateMenu(){

    /*
    background = IMG_Load("assets/menu.png");
    board_setup = IMG_Load("assets/boardsetup.png");
    difficulty = IMG_Load("assets/difficulty.png");
    whichside = IMG_Load("assets/side.png");
    timermenu = IMG_Load("assets/timer.png");
    timermenu1 = IMG_Load("assets/timer1.png");
    gamemode = IMG_Load("assets/gamemode.png");
    white_difficulty = IMG_Load("assets/white_difficulty.png");
    black_difficulty = IMG_Load("assets/black_difficulty.png");
    checkTerminal = IMG_Load("assets/checktheterminal.png");
    startGame = IMG_Load("assets/startgame.png");
    skiptogame = IMG_Load("assets/skiptogame.png");
    */
    background = SDL_LoadBMP("assets/menu.bmp");
    board_setup = SDL_LoadBMP("assets/boardsetup.bmp");
    difficulty = SDL_LoadBMP("assets/difficulty.bmp");
    whichside = SDL_LoadBMP("assets/side.bmp");
    timermenu = SDL_LoadBMP("assets/timer.bmp");
    timermenu1 = SDL_LoadBMP("assets/timer1.bmp");
    gamemode = SDL_LoadBMP("assets/gamemode.bmp");
    white_difficulty = SDL_LoadBMP("assets/white_difficulty.bmp");
    black_difficulty = SDL_LoadBMP("assets/black_difficulty.bmp");
    checkTerminal = SDL_LoadBMP("assets/checktheterminal.bmp");
    startGame = SDL_LoadBMP("assets/startgame.bmp");
    skiptogame = SDL_LoadBMP("assets/skiptogame.bmp");

}

void instantiateSprites(){
    /*
    ChessBoard = IMG_Load("assets/ChessBoard.png");

    WPawn = IMG_Load("assets/WPawn.png");
    BPawn = IMG_Load("assets/BPawn.png");

    WRook = IMG_Load("assets/WRook.png");
    BRook = IMG_Load("assets/BRook.png");

    WQueen = IMG_Load("assets/WQueen.png");
    BQueen = IMG_Load("assets/BQueen.png");

    WKing = IMG_Load("assets/WKing.png");
    BKing = IMG_Load("assets/BKing.png");

    WBishop = IMG_Load("assets/WBishop.png");
    BBishop = IMG_Load("assets/BBishop.png");

    WKnight = IMG_Load("assets/WKnight.png");
    BKnight = IMG_Load("assets/BKnight.png");

    //Green Marker on possible moves
    green = IMG_Load("assets/GreenOverlay.png");

    //Buttons
    history = IMG_Load("assets/History.png");
    terminalInput = IMG_Load("assets/TerminalInput.png");
    undobutton = IMG_Load("assets/Undo.png");
    rules = IMG_Load("assets/Rules.png");
    resign = IMG_Load("assets/Resign.png");
    */
    ChessBoard = SDL_LoadBMP("assets/ChessBoard.bmp");

    WPawn = SDL_LoadBMP("assets/WPawn.bmp");
    BPawn = SDL_LoadBMP("assets/BPawn.bmp");

    WRook = SDL_LoadBMP("assets/WRook.bmp");
    BRook = SDL_LoadBMP("assets/BRook.bmp");

    WQueen = SDL_LoadBMP("assets/WQueen.bmp");
    BQueen = SDL_LoadBMP("assets/BQueen.bmp");

    WKing = SDL_LoadBMP("assets/WKing.bmp");
    BKing = SDL_LoadBMP("assets/BKing.bmp");

    WBishop = SDL_LoadBMP("assets/WBishop.bmp");
    BBishop = SDL_LoadBMP("assets/BBishop.bmp");

    WKnight = SDL_LoadBMP("assets/WKnight.bmp");
    BKnight = SDL_LoadBMP("assets/BKnight.bmp");

    //Green Marker on possible moves
    green = SDL_LoadBMP("assets/GreenOverlay.bmp");
    SDL_SetAlpha(green, SDL_SRCALPHA, 128);

    //Buttons
    history = SDL_LoadBMP("assets/History.bmp");
    terminalInput = SDL_LoadBMP("assets/TerminalInput.bmp");
    undobutton = SDL_LoadBMP("assets/Undo.bmp");
    rules = SDL_LoadBMP("assets/Rules.bmp");
    resign = SDL_LoadBMP("assets/Resign.bmp");
}

void showWarning(SDL_Surface *screen){
    SDL_Rect position;
    position.x = -85;
    position.y = -85;
    SDL_BlitSurface(checkTerminal, NULL, screen, &position);
    SDL_Flip(screen);
}

void tempdisplayMenu(SDL_Surface *screen, int state){
    displayMenu(screen, state);
}

void displayMenu(SDL_Surface *screen, int state){

    //printf("f");
    //SDL_Delay(500);
    //return;
    SDL_Rect position;
    position.x = -5;
    position.y = -5;
    SDL_BlitSurface(background, NULL, screen, &position);
    
    switch(state){
        case 0:
            position.x = 282;
            position.y = 325;

            SDL_BlitSurface(startGame, NULL, screen, &position);

            position.x = 800;
            position.y = 50;

            SDL_BlitSurface(skiptogame, NULL, screen, &position);
            break;
        case 1:
            position.x = -85;
            position.y = -70;
            
            SDL_BlitSurface(board_setup, NULL, screen, &position);
            break;
        case 2:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(gamemode, NULL, screen, &position);
            break;
        case 11:
            position.x = -85;
            position.y = -115;
            
            SDL_BlitSurface(whichside, NULL, screen, &position);
            break;
        case 12:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(timermenu, NULL, screen, &position);
            break;
        case 13:
            position.x = -80;
            position.y = -85;
            
            SDL_BlitSurface(timermenu1, NULL, screen, &position);
            break;
        case 21:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(whichside, NULL, screen, &position);
            break;
        case 22:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(difficulty, NULL, screen, &position);
            break;
        case 31:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(white_difficulty, NULL, screen, &position);
            break;
        case 32:
            position.x = -85;
            position.y = -85;
            
            SDL_BlitSurface(black_difficulty, NULL, screen, &position);
            break;
        default:
            position.x = 362;
            position.y = 375;
            
            SDL_BlitSurface(startGame, NULL, screen, &position);

            position.x = 650;
            position.y = 100;

            SDL_BlitSurface(skiptogame, NULL, screen, &position);
            break;
    }
    
    SDL_Flip(screen);
}

void displayGame(Board *board, SDL_Surface *screen, Position followMouse, Position hintPos, int state, Position* hintPositions, int moveCount)//, Move* PossibleMoves, int capturedPieceW, int capturedPieceB)
{

    
    SDL_Rect position;

    int i, j;
    int temp_i = -1;
    int temp_j = -1;

    position.x = -5;
    position.y = -5;

    //Loading Images ~ ~ ~
    SDL_BlitSurface(background, NULL, screen, &position);

    position.x = offset_x-3;
    position.y = offset_y-3;

    SDL_BlitSurface(ChessBoard, NULL, screen, &position);
    
    position.x = 30;
    position.y = 500;

    SDL_BlitSurface(history, NULL, screen, &position);
    
    position.x = 362;
    position.y = 675;

    SDL_BlitSurface(terminalInput, NULL, screen, &position);
    
    position.x = 30;
    position.y = 650;

    SDL_BlitSurface(undobutton, NULL, screen, &position);
    
    position.x = 775;
    position.y = 500;

    SDL_BlitSurface(rules, NULL, screen, &position);
    
    position.x = 775;
    position.y = 650;

    SDL_BlitSurface(resign, NULL, screen, &position);
    
    if (followMouse.x != -1 && followMouse.y != -1){
        temp_i = hintPos.x;
        temp_j = hintPos.y;
        FOLLOWINGMOUSE = true;
        //printf("\nSETTING MY BOYS %i, %i\n", temp_i, temp_j);
    }
    for (i = 0; i < 8; i++)
    {
        for ( j = 0; j < 8; j++)
        {
            if(temp_i == i && temp_j == j && followMouse.x > 7 && followMouse.y > 7){
                position.x = followMouse.x - 28;
                position.y = followMouse.y - 28;
                //printf("\nTEMPI TEMPJ %i, %i, %i, %i\n", position.x, position.y, i, j);
                //printf("THIS EVER HAPPENS?");
            }
            else{
                position.x = offset_x + j * (56+5);
                position.y = offset_y + i * (56+5);
            }
            if (board->squares[i][j].type == PAWN)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BPawn, NULL, screen, &position);
                else
                    SDL_BlitSurface(WPawn, NULL, screen, &position);
            }

            if (board->squares[i][j].type == ROOK)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BRook, NULL, screen, &position);
                else
                    SDL_BlitSurface(WRook, NULL, screen, &position);
            }

            if (board->squares[i][j].type == BISHOP)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BBishop, NULL, screen, &position);
                else
                    SDL_BlitSurface(WBishop, NULL, screen, &position);
            }

            if (board->squares[i][j].type == QUEEN)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BQueen, NULL, screen, &position);
                else
                    SDL_BlitSurface(WQueen, NULL, screen, &position);
            }

            if (board->squares[i][j].type == KNIGHT)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BKnight, NULL, screen, &position);
                else
                    SDL_BlitSurface(WKnight, NULL, screen, &position);
            }

            if (board->squares[i][j].type == KING)
            {
                if (board->squares[i][j].color == BLACK)
                    SDL_BlitSurface(BKing, NULL, screen, &position);
                else
                    SDL_BlitSurface(WKing, NULL, screen, &position);
            }

        }
    }
    /*
    if (hintPos.x != -1 && hintPos.y != -1){
        
        i = (hintPos.x+3) / (56+5);
        if (flipDirection == 1)
            j = ((hintPos.y+3) / (56+5));
        else
            j = ((hintPos.y+3) / (56+5) - 7) * -1;
        
        position.y = offset_y + hintPos.x * (56+5);
        position.x = offset_x + hintPos.y * (56+5);
        printf("\nHINT HINT HINT?\n");
        SDL_BlitSurface(green, NULL, screen, &position);
        
    }
    */
    //printf("Move count: %i", moveCount);
    if (moveCount > 0){
        int i;
        for(i = 0; i < moveCount; i++){
            //printf("true");
            position.x = offset_x + hintPositions[i].x * (56+5);
            position.y = offset_y + hintPositions[i].y * (56+5);
            SDL_BlitSurface(green, NULL, screen, &position);
        }
    }
    SDL_Flip(screen);
}

int getClick(SDL_Surface *screen, Position *position, int moveClick, int state)
{
    bool waiting = true;
    
    SDL_Event event;

    /*
        Return 0:   Default
        Return 1:   Invalid Move
        Return 2:   Button Up
    */

    while (waiting)
    {

        SDL_Flip(screen);
        SDL_WaitEvent(&event);
        
        if(event.type == SDL_QUIT){
            position->x = -999;
            position->y = -999;
            return 1;
        }
        /*
        else if (event.type.state == SDL_RELEASED) {
            position.x = event.button.y;
            position.y = event.button.x;
            if (((position.x+3) / (56+5) < 8) && ((position.y+3) / (56+5) < 8))
            {
                position.x = (position.x+3) / (56+5);
                if (flipDirection == 1)
                    position.y = ((position.y+3) / (56+5)-7) * -1;
                else
                    position.y = ((position.y+3) / (56+5)-7) * -1;
                printf("%c, %i ", position.y + 'a', 8 - position.x);
                //return position;
                return 2;
            }
            else{
                return 1;
            }
        }
        */
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            //printf("\nWORKWORK\n");
            if (state != 0){
                position->x = event.motion.x;
                position->y = event.motion.y;
                return 0;
            }
            position->x = event.button.y;
            position->y = event.button.x;
            FOLLOWINGMOUSE = false;
            //printf("\n%i, %i \n", position->y, position->x);
            if (position->y > offset_x && position->y < 1000 - offset_x && position->x > offset_y && position->x < 800 - offset_y) 
            {
                position->x = (position->x-offset_y) / (56+5);
                if (flipDirection == -1)
                    position->y = ((position->y-offset_x) / (56+5));
                else
                    position->y = ((position->y-offset_x) / (56+5)-7) * -1;
                /*
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                */
                //return position;
                wasButtonJustDown = true;
                return 0;
            }
            else{
                return 1;
            }
        }
        else if (wasButtonJustDown == true && event.button.state == SDL_RELEASED && event.type != SDL_MOUSEMOTION){
            wasButtonJustDown = false;
            position->x = event.button.y;
            position->y = event.button.x;
            
            if (position->y > offset_x && position->y < 1000 - offset_x && position->x > offset_y && position->x < 800 - offset_y)
            {
                position->x = (position->x-offset_y) / (56+5);
                if (flipDirection == -1)
                    position->y = ((position->y-offset_x) / (56+5));
                else
                    position->y = ((position->y-offset_x) / (56+5)-7) * -1;
                /*
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                printf("%c, %i ", position->y + 'a', 8 - position->x);
                */
                //return position;
                //wasButtonJustDown = true;
                FOLLOWINGMOUSE = false;
                return 2;
            }
            else{
                return 1;
                FOLLOWINGMOUSE = false;
            }
            //printf("THIS HAPPENEDED EDJADDASLKM\n");
            //return 2;
        }        
        else if (moveClick == 1 && event.type == SDL_MOUSEMOTION){
            position->x = event.motion.x;
            position->y = event.motion.y;
            //FOLLOWINGMOUSE = false;
            //FOLLOWINGMOUSE = true;
            return 3;
        }
        /*
        else{
            return 4;
        }
        */

    }
    return 0;
}

void flipBOARD(int flip){
    flipDirection = flip;
    if (flipDirection == 1){
        /*
        WPawn = IMG_Load("assets/WPawn.png");
        BPawn = IMG_Load("assets/BPawn.png");

        WRook = IMG_Load("assets/WRook.png");
        BRook = IMG_Load("assets/BRook.png");

        WQueen = IMG_Load("assets/WQueen.png");
        BQueen = IMG_Load("assets/BQueen.png");

        WKing = IMG_Load("assets/WKing.png");
        BKing = IMG_Load("assets/BKing.png");

        WBishop = IMG_Load("assets/WBishop.png");
        BBishop = IMG_Load("assets/BBishop.png");

        WKnight = IMG_Load("assets/WKnight.png");
        BKnight = IMG_Load("assets/BKnight.png");
        */
        WPawn = SDL_LoadBMP("assets/WPawn.bmp");
        BPawn = SDL_LoadBMP("assets/BPawn.bmp");

        WRook = SDL_LoadBMP("assets/WRook.bmp");
        BRook = SDL_LoadBMP("assets/BRook.bmp");

        WQueen = SDL_LoadBMP("assets/WQueen.bmp");
        BQueen = SDL_LoadBMP("assets/BQueen.bmp");

        WKing = SDL_LoadBMP("assets/WKing.bmp");
        BKing = SDL_LoadBMP("assets/BKing.bmp");

        WBishop = SDL_LoadBMP("assets/WBishop.bmp");
        BBishop = SDL_LoadBMP("assets/BBishop.bmp");

        WKnight = SDL_LoadBMP("assets/WKnight.bmp");
        BKnight = SDL_LoadBMP("assets/BKnight.bmp");
    }
    else{
        /*
        BPawn = IMG_Load("assets/WPawn.png");
        WPawn = IMG_Load("assets/BPawn.png");

        BRook = IMG_Load("assets/WRook.png");
        WRook = IMG_Load("assets/BRook.png");

        BQueen = IMG_Load("assets/WQueen.png");
        WQueen = IMG_Load("assets/BQueen.png");

        BKing = IMG_Load("assets/WKing.png");
        WKing = IMG_Load("assets/BKing.png");

        BBishop = IMG_Load("assets/WBishop.png");
        WBishop = IMG_Load("assets/BBishop.png");

        BKnight = IMG_Load("assets/WKnight.png");
        WKnight = IMG_Load("assets/BKnight.png");
        */
        BPawn = SDL_LoadBMP("assets/WPawn.bmp");
        WPawn = SDL_LoadBMP("assets/BPawn.bmp");

        BRook = SDL_LoadBMP("assets/WRook.bmp");
        WRook = SDL_LoadBMP("assets/BRook.bmp");

        BQueen = SDL_LoadBMP("assets/WQueen.bmp");
        WQueen = SDL_LoadBMP("assets/BQueen.bmp");

        BKing = SDL_LoadBMP("assets/WKing.bmp");
        WKing = SDL_LoadBMP("assets/BKing.bmp");

        BBishop = SDL_LoadBMP("assets/WBishop.bmp");
        WBishop = SDL_LoadBMP("assets/BBishop.bmp");

        BKnight = SDL_LoadBMP("assets/WKnight.bmp");
        WKnight = SDL_LoadBMP("assets/BKnight.bmp");
    }
}