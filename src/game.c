#include "game.h"

void easystartGamePVP(Board *notboard, Color side, int timer){
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    
    int start_x, start_y, end_x, end_y;
    bool undo = false;
    //Color user_side = (side == BLACK) ? BLACK : WHITE;
    //Color ai_color = (side == WHITE) ? BLACK : WHITE;

    //setupInitialPosition(&board);
    displayBoard(&board);
    //Log* log = createLog();

    int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
    int flipdir = -1;
    
    //int moveCount = 0;

    side = WHITE;

    while(!gameOver) {
        //int moveClick = 0;
        //printf("\nNEW LOOP\n");

        get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
        while (undo == false && (!is_move_valid(&board, start_x, start_y, end_x, end_y) || !correct_side(&board, start_x, start_y, side))) {
            printf("Invalid move, try again.\n");
            get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
        }

        if (undo == true) {
            undo_move(&board);
            displayBoard(&board);
            get_user_move_without_undo(&start_x, &start_y, &end_x, &end_y);
        }
        while (undo == true && (!is_move_valid(&board, start_x, start_y, end_x, end_y) || !correct_side(&board, start_x, start_y, side))) {
            printf("Invalid move, try again.\n");
            get_user_move_without_undo(&start_x, &start_y, &end_x, &end_y);
        }

        // save current board to prevBoard when player makes move, so they can potentially undo next turn
        copy_board(board, &prevBoard);
        undo = false; // set undo back to false for next turn

        make_move(&board, start_x, start_y, end_x, end_y);
        displayBoard(&board);

        // Log the move
        char move_str[6];
        sprintf(move_str, "%c%d%c%d", 'A'+start_x, start_y+1, 'A'+end_x, end_y+1);
        log_move(move_str);

        // Check for game end conditions
        if (is_king_in_check(&board, side)) {
            printf("Check!\n");
            if (is_checkmate(&board, side)) {
                printf("Checkmate!\n");
                gameOver = true;
                break;
            }
        }
        
        moveCounter++;
        flipdir *= -1;
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        //displayBoard(&board);
        //displayLog(log);

    /* temporarily commented out for submission purposes
        Move move = CreateMoveWithInput(board, charMove);

        if (isValidMove(&board, move) == 0) {
            movePiece(&board, log, charMove);
            moveCounter++;
            displayBoard(&board);
            displayLog(log);
        }
        else {
            printf("Invalid Move. Try again.\n");
        }
    */
    }
}
void easystartGamePVC(Board *notboard, int side, int difficulty){
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    
    int start_x, start_y, end_x, end_y;
    bool undo = false;
    Color user_side = (side == BLACK) ? BLACK : WHITE;
    Color ai_color = (side == WHITE) ? BLACK : WHITE;

    //setupInitialPosition(&board);
    displayBoard(&board);
    //Log* log = createLog();
    //instantiateSprites();

    int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
    
    

    side = WHITE;
    
    while(!gameOver) {
        
        //printf("\nNEW LOOP\n");
        
        if (side == user_side){    
            get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
            while (undo == false && (!is_move_valid(&board, start_x, start_y, end_x, end_y) || !correct_side(&board, start_x, start_y, side))) {
                printf("Invalid move, try again.\n");
                get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
            }

            if (undo == true) {
                undo_move(&board);
                displayBoard(&board);
                get_user_move_without_undo(&start_x, &start_y, &end_x, &end_y);
            }
            while (undo == true && (!is_move_valid(&board, start_x, start_y, end_x, end_y) || !correct_side(&board, start_x, start_y, side))) {
                printf("Invalid move, try again.\n");
                get_user_move_without_undo(&start_x, &start_y, &end_x, &end_y);
            }

            // save current board to prevBoard when player makes move, so they can potentially undo next turn
            copy_board(board, &prevBoard);
            undo = false; // set undo back to false for next turn
    
            make_move(&board, start_x, start_y, end_x, end_y);
            displayBoard(&board);
    
            // Log the move
            char move_str[6];
            sprintf(move_str, "%c%d%c%d", 'A'+start_x, start_y+1, 'A'+end_x, end_y+1);
            log_move(move_str);
    
            // Check for game end conditions
            if (is_king_in_check(&board, ai_color)) {
                printf("Check!\n");
                if (is_checkmate(&board, ai_color)) {
                    printf("Checkmate!\n");
                    gameOver = true;
                    break;
                }
            }
                
            
        }
        else{
            // old version of AI
            // ai_make_move(&board, ai_color);
            
            ai_make_move(&board, ai_color);
            displayBoard(&board);
            
            /*
            // new version of AI function
            int depth = 2;
            Move move = alpha_beta_algorithm(&board, ai_color, depth);
            // make sure move exists
            // make sure there's no checkmate
            if (move.start_x != -1 || move.start_y != -1 || move.end_x != -1 || move.end_y != -1 )
            {
                make_move(&board, move.start_x, move.start_y, move.end_x, move.end_y);
            }
            displayBoard(&board);
            /
        }  
        //printf("got here");
        
        
        charMove[0] = 'a' + (firstClick.y);
        charMove[1] = '0' + (8-firstClick.x);
        charMove[2] = 'a' + (secondClick.y);
        charMove[3] = '0' + (8-secondClick.x);
        */
        }
        //movePiece(board, log, side, firstClick, secondClick);
        if (is_king_in_check(&board, side)) {
            printf("Check!\n");
            if (is_checkmate(&board, side)) {
                printf("Checkmate!\n");
                gameOver = true;
                break;
            }
        }

        moveCounter++;
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        //displayBoard(&board);
        //displayLog(log);

    }
}
void easystartGameCVC(Board *notboard, int difficultyW, int difficultyB){
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    Color side = WHITE;
    //int start_x, start_y, end_x, end_y;
    Color user_side = (side == BLACK) ? BLACK : WHITE;
    Color ai_color = (side == WHITE) ? BLACK : WHITE;

    //Log* log = createLog();
    //instantiateSprites();
    
    //int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
      

    side = WHITE;
    
    while(!gameOver) {
        //printf("\nNEW LOOP\n");
        
        if (side == user_side){    
            ai_make_move(&board, user_side);
            displayBoard(&board);
        }
        else{
            ai_make_move(&board, ai_color);
            displayBoard(&board);
        }        //printf("got here");
        /*
        charMove[0] = 'a' + (firstClick.y);
        charMove[1] = '0' + (8-firstClick.x);
        charMove[2] = 'a' + (secondClick.y);
        charMove[3] = '0' + (8-secondClick.x);
        */
        //movePiece(board, log, side, firstClick, secondClick);

        if (is_king_in_check(&board, side)) {
            printf("Check!\n");
            if (is_checkmate(&board, side)) {
                printf("Checkmate!\n");
                gameOver = true;
                break;
            }
        }
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        //displayBoard(&board);
        //displayLog(log);

        
    /* temporarily commented out for submission purposes
        Move move = CreateMoveWithInput(board, charMove);

        if (isValidMove(&board, move) == 0) {
            movePiece(&board, log, charMove);
            moveCounter++;
            displayBoard(&board);
            displayLog(log);
        }
        else {
            //printf("Invalid Move. Try again.\n");
        }
    */
    }
} 



void startGamePVP(Board *notboard, Color side, int timer, SDL_Surface *screen){ //side = 0 = W / = 1 = B , timer = timer time, 0 or -1 for no timer
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    
    //int start_x, start_y;//, end_x, end_y;
    //bool undo = false;
    //Color user_side = (side == BLACK) ? BLACK : WHITE;
    //Color ai_color = (side != WHITE) ? BLACK : WHITE;

    //setupInitialPosition(&board);
    displayBoard(&board);
    //Log* log = createLog();
    instantiateSprites();

    int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
    int flipdir = -1;
    Position followMouse = {-1, -1};
    Position errorPos = {-1, -1};
    Position hintPos = {-1, -1}; //CHANGE THIS LATER
    Position* hintPositions = NULL;
    int moveCount = 0;
    flipBOARD(flipdir);

    side = WHITE;

    while(!gameOver) {
        //char charMove[4];
        int moveClick = 0;
        Position secondClick;
        Position firstClick = {-1, -1};
        //printf("\nNEW LOOP\n");

        while (moveClick != 2){

            displayGame(&board, screen, followMouse, hintPos, 0, hintPositions, moveCount);    
            Position clickPosition;
            int testVar = getClick(screen, &clickPosition, moveClick, 0);
            //printf("This is the return value %i\n", testVar);
            
            bool current_first_equivalence = (clickPosition.x == firstClick.x && clickPosition.y == firstClick.y);
            //printf("This is the bool value %s\n", current_first_equivalence ? "true" : "false");
            switch(testVar){
                case(0): //Successful Click Normal  
                    if ((moveClick == 1 || moveClick == 10) && validateSecondClick(&board, clickPosition, side, firstClick) )
                    {
                        moveClick = 2;
                        hintPos = errorPos;
                        hintPositions = NULL;
                        moveCount = 0;
                        secondClick = clickPosition;
                        //printf("second check verified"); 
                        break;
                    }
                    if (moveClick != 2 && validateFirstClick(&board, clickPosition, side) && !current_first_equivalence)
                    {
                        moveClick = 1;
                        firstClick = clickPosition;
                        //printf("first check verified FOLLOW");
                        hintPos = clickPosition;
                        Color temp_side = (side == WHITE) ? BLACK : WHITE;
                        hintPositions = get_valid_moves_withStart(&board, temp_side, &moveCount, clickPosition.y, clickPosition.x);
                        followMouse = clickPosition;
                        break;
                    }
                    else{
                        moveClick = 0;
                        hintPos = errorPos;
                        hintPositions = NULL;
                        moveCount = 0;
                        //printf("no check verified");
                    } 
                case(1): //False Click 
                    if (clickPosition.x == -999 && clickPosition.y == -999){
                        SDL_Quit();
                        exit(0);
                    }
                    moveClick = 0;
                    hintPos = errorPos;
                    hintPositions = NULL;
                    moveCount = 0;
                    //printf("no check verified case 1");
                case(2): //CLICK UP?!!?!??!?!?!?!?!?!?!?!?! THERES A BIG BUG HERE
                    if (!current_first_equivalence && (moveClick == 1 || moveClick == 10) && validateSecondClick(&board, clickPosition, side, firstClick) )
                    {
                        moveClick = 2;
                        hintPos = errorPos;
                        hintPositions = NULL;
                        moveCount = 0;
                        secondClick = clickPosition;
                        //printf("second check verified");
                        followMouse = errorPos; 
                        break;
                    }
                    
                    if (current_first_equivalence && followMouse.x != -1 && followMouse.y != -1)
                    {
                        moveClick = 10;
                        firstClick = clickPosition;
                        //printf("first check verified DROP");
                        hintPos = clickPosition;
                        Color temp_side = (side == WHITE) ? BLACK : WHITE;
                        hintPositions = get_valid_moves_withStart(&board, temp_side, &moveCount, clickPosition.y, clickPosition.x);
                        followMouse = errorPos;
                        break;
                    }
                    /*
                    if (moveClick != 2 && validateFirstClick(&board, clickPosition, side) && !current_first_equivalence)
                    {
                        moveClick = 1;
                        firstClick = clickPosition;
                        //printf("first check verified");
                        hintPos = clickPosition;
                        followMouse = clickPosition;//{28, 28};
                        break;
                    }
                    */
                    else{
                        moveClick = 0;
                        hintPos = errorPos;
                        hintPositions = NULL;
                        moveCount = 0;
                        //printf("no check verified case 2");
                    } 
                    
                case(3):
                    //if (followMouse.x != -1 && followMouse.y != -1){
                    followMouse = clickPosition; 
                    //}
                    //if (moveClick == 1)
                    hintPos = firstClick;
                    //printf("\nFOLLOW\n");
                    
                
            }
            
        }
        //printf("got here");
        /*
        charMove[0] = 'a' + (firstClick.y);
        charMove[1] = '0' + (8-firstClick.x);
        charMove[2] = 'a' + (secondClick.y);
        charMove[3] = '0' + (8-secondClick.x);
        */
        //movePiece(board, log, side, firstClick, secondClick);

        //get_user_move_with_undo(&firstClick.x, &firstClick.y, &secondClick.x, &secondClick.y, &undo);
        
        /*
        while (undo == false && !is_move_valid(&board, start_x, start_y, end_x, end_y)) {
            printf("Invalid move, try again.\n");
            get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
        }
        */
        if (board.squares[firstClick.y][firstClick.x].type == PAWN ){
            if (secondClick.x == 0 || secondClick.x == 7)
                showWarning(screen);
        }
        copy_board(board, &prevBoard);
        //undo = false; // set undo back to false for next turn

        make_move(&board, firstClick.y, firstClick.x, secondClick.y, secondClick.x);

        char move_str[6];
        sprintf(move_str, "%c%d%c%d", 'A'+firstClick.y, firstClick.x+1, 'A'+secondClick.y, secondClick.x+1);
        log_move(move_str);
        
        if (is_king_in_check(&board, side)) {
            printf("Check!\n");
            if (is_checkmate(&board, side)) {
                printf("Checkmate!\n");
                gameOver = true;
                break;
            }
        }
        
        moveCounter++;
        followMouse = errorPos;
        hintPos = errorPos;
        flipdir *= -1;
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        displayBoard(&board);
        //displayLog(log);

    /* temporarily commented out for submission purposes
        Move move = CreateMoveWithInput(board, charMove);

        if (isValidMove(&board, move) == 0) {
            movePiece(&board, log, charMove);
            moveCounter++;
            displayBoard(&board);
            displayLog(log);
        }
        else {
            printf("Invalid Move. Try again.\n");
        }
    */
    }

}

void startGamePVC(Board *notboard, int side, int difficulty, SDL_Surface *screen){ //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default)
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    
    //int start_x, start_y;//, end_x, end_y;
    //bool undo = false;
    Color user_side = (side == BLACK) ? BLACK : WHITE;
    Color ai_color = (side != WHITE) ? BLACK : WHITE;

    //setupInitialPosition(&board);
    displayBoard(&board);
    //Log* log = createLog();
    instantiateSprites();

    int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
    int flipdir = -1;
    Position followMouse = {-1, -1};
    Position errorPos = {-1, -1};
    Position hintPos = {-1, -1}; //CHANGE THIS LATER
    Position* hintPositions = NULL;
    int moveCount = 0;
    flipBOARD(flipdir);

    side = WHITE;
    
    while(!gameOver) {
        //char charMove[4];
        int moveClick = 0;
        Position secondClick;
        Position firstClick = {-1, -1};
        //printf("\nNEW LOOP\n");
        
        if (side == user_side){    
            while (moveClick != 2){

                displayGame(&board, screen, followMouse, hintPos, 0, hintPositions, moveCount);    
                Position clickPosition;
                int testVar = getClick(screen, &clickPosition, moveClick, 0);
                //printf("This is the return value %i\n", testVar);
                
                bool current_first_equivalence = (clickPosition.x == firstClick.x && clickPosition.y == firstClick.y);
                //printf("This is the bool value %s\n", current_first_equivalence ? "true" : "false");
                switch(testVar){
                    case(0): //Successful Click Normal  
                        if ((moveClick == 1 || moveClick == 10) && validateSecondClick(&board, clickPosition, side, firstClick) )
                        {
                            moveClick = 2;
                            hintPos = errorPos;
                            hintPositions = NULL;
                            moveCount = 0;
                            secondClick = clickPosition;
                            //printf("second check verified"); 
                            break;
                        }
                        if (moveClick != 2 && validateFirstClick(&board, clickPosition, side) && !current_first_equivalence)
                        {
                            moveClick = 1;
                            firstClick = clickPosition;
                            //printf("first check verified FOLLOW");
                            hintPos = clickPosition;
                            Color temp_side = (side == WHITE) ? BLACK : WHITE;
                            hintPositions = get_valid_moves_withStart(&board, temp_side, &moveCount, clickPosition.y, clickPosition.x);
                            followMouse = clickPosition;
                            break;
                        }
                        else{
                            moveClick = 0;
                            hintPos = errorPos;
                            hintPositions = NULL;
                            moveCount = 0;
                            //printf("no check verified");
                        } 
                    case(1): //False Click 
                        if (clickPosition.x == -999 && clickPosition.y == -999){
                            SDL_Quit();
                            exit(0);
                        }
                        moveClick = 0;
                        hintPos = errorPos;
                        hintPositions = NULL;
                        moveCount = 0;
                        //printf("no check verified case 1");
                    case(2): //CLICK UP?!!?!??!?!?!?!?!?!?!?!?! THERES A BIG BUG HERE
                        if (!current_first_equivalence && (moveClick == 1 || moveClick == 10) && validateSecondClick(&board, clickPosition, side, firstClick) )
                        {
                            moveClick = 2;
                            hintPos = errorPos;
                            hintPositions = NULL;
                            moveCount = 0;
                            secondClick = clickPosition;
                            //printf("second check verified");
                            followMouse = errorPos; 
                            break;
                        }
                        
                        if (current_first_equivalence && followMouse.x != -1 && followMouse.y != -1)
                        {
                            moveClick = 10;
                            firstClick = clickPosition;
                            //printf("first check verified DROP");
                            hintPos = clickPosition;
                            Color temp_side = (side == WHITE) ? BLACK : WHITE;
                            hintPositions = get_valid_moves_withStart(&board, temp_side, &moveCount, clickPosition.y, clickPosition.x);
                            followMouse = errorPos;
                            break;
                        }
                        /*
                        if (moveClick != 2 && validateFirstClick(&board, clickPosition, side) && !current_first_equivalence)
                        {
                            moveClick = 1;
                            firstClick = clickPosition;
                            //printf("first check verified");
                            hintPos = clickPosition;
                            followMouse = clickPosition;//{28, 28};
                            break;
                        }
                        */
                        else{
                            moveClick = 0;
                            hintPos = errorPos;
                            hintPositions = NULL;
                            moveCount = 0;
                            //printf("no check verified case 2");
                        } 
                        
                    case(3):
                        //if (followMouse.x != -1 && followMouse.y != -1){
                        followMouse = clickPosition; 
                        //}
                        //if (moveClick == 1)
                        hintPos = firstClick;
                        //printf("\nFOLLOW\n");
                      
                  
                }
                
            }
            //get_user_move_with_undo(&firstClick.x, &firstClick.y, &secondClick.x, &secondClick.y, &undo);
        
            /*
            while (undo == false && !is_move_valid(&board, start_x, start_y, end_x, end_y)) {
                //printf("Invalid move, try again.\n");
                get_user_move_with_undo(&start_x, &start_y, &end_x, &end_y, &undo);
            }
            */
            if (board.squares[firstClick.y][firstClick.x].type == PAWN ){
                if (secondClick.x == 0 || secondClick.x == 7)
                    showWarning(screen);
            }
            copy_board(board, &prevBoard);
            //undo = false; // set undo back to false for next turn

            make_move(&board, firstClick.y, firstClick.x, secondClick.y, secondClick.x);

            char move_str[6];
            sprintf(move_str, "%c%d%c%d", 'A'+firstClick.y, firstClick.x+1, 'A'+secondClick.y, secondClick.x+1);
            log_move(move_str);

            if (is_king_in_check(&board, side)) {
                printf("Check!\n");
                if (is_checkmate(&board, side)) {
                    printf("Checkmate!\n");
                    gameOver = true;
                    break;
                }
            }
        }
        else{
            // old version of AI
             ai_make_move(&board, ai_color);
            /*
            // new version of AI function
            int depth = 2;
            Move move = alpha_beta_algorithm(&board, ai_color, depth);
            // make sure move exists
            // make sure there's no checkmate
            if (move.start_x != -1 || move.start_y != -1 || move.end_x != -1 || move.end_y != -1 )
            {
                make_move(&board, move.start_x, move.start_y, move.end_x, move.end_y);
            }
            */
            displayBoard(&board);
        }  
        //printf("got here");
        /*
        charMove[0] = 'a' + (firstClick.y);
        charMove[1] = '0' + (8-firstClick.x);
        charMove[2] = 'a' + (secondClick.y);
        charMove[3] = '0' + (8-secondClick.x);
        */
        //movePiece(board, log, side, firstClick, secondClick);

        
        moveCounter++;
        followMouse = errorPos;
        hintPos = errorPos;
        flipdir *= -1;
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        displayBoard(&board);
        //displayLog(log);

    /* temporarily commented out for submission purposes
        Move move = CreateMoveWithInput(board, charMove);

        if (isValidMove(&board, move) == 0) {
            movePiece(&board, log, charMove);
            moveCounter++;
            displayBoard(&board);
            displayLog(log);
        }
        else {
            //printf("Invalid Move. Try again.\n");
        }
    */
    }
}

void startGameCVC(Board *notboard, int difficultyW, int difficultyB, SDL_Surface *screen){ //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default) {
    //printf("FKNFSAKLASFn/sajf. Type: %i Color: %i \n", side, side);
    Board board = *notboard;
    Color side = WHITE;
    //int start_x, start_y, end_x, end_y;
    //bool undo = false;
    Color user_side = (side == BLACK) ? BLACK : WHITE;
    Color ai_color = (side == WHITE) ? BLACK : WHITE;

    //setupInitialPosition(&board);
    displayBoard(&board);
    //Log* log = createLog();
    instantiateSprites();
    
    int moveCounter = 0;
    //int CPU = 1;
    bool gameOver = false;
    int flipdir = -1;
    Position followMouse = {-1, -1};
    Position errorPos = {-1, -1};
    Position hintPos = {-1, -1}; //CHANGE THIS LATER
    displayGame(&board, screen, followMouse, hintPos, 0, NULL, 0);    
    flipBOARD(flipdir);

    side = WHITE;
    
    while(!gameOver) {
        //char charMove[4];
        //int moveClick = 0;
        //Position secondClick;
        //Position firstClick = {-1, -1};
        //printf("\nNEW LOOP\n");
        
        if (side == user_side){    
            ai_make_move(&board, user_side);
            displayBoard(&board);
        }
        else{
            ai_make_move(&board, ai_color);
            displayBoard(&board);
        }
        displayGame(&board, screen, followMouse, hintPos, 0, NULL, 0);       
        //printf("got here");
        /*
        charMove[0] = 'a' + (firstClick.y);
        charMove[1] = '0' + (8-firstClick.x);
        charMove[2] = 'a' + (secondClick.y);
        charMove[3] = '0' + (8-secondClick.x);
        */
        //movePiece(board, log, side, firstClick, secondClick);

        if (is_king_in_check(&board, side)) {
            printf("Check!\n");
            if (is_checkmate(&board, side)) {
                printf("Checkmate!\n");
                gameOver = true;
                break;
            }
        }
        
        moveCounter++;
        followMouse = errorPos;
        hintPos = errorPos;
        flipdir *= -1;
        if (side == WHITE)    
            side = BLACK;
        else
            side = WHITE;
        //printf("updated");
        displayBoard(&board);
        //displayLog(log);

    /* temporarily commented out for submission purposes
        Move move = CreateMoveWithInput(board, charMove);

        if (isValidMove(&board, move) == 0) {
            movePiece(&board, log, charMove);
            moveCounter++;
            displayBoard(&board);
            displayLog(log);
        }
        else {
            //printf("Invalid Move. Try again.\n");
        }
    */
    }
}

void printHelp() {
    printf("Commands:\n");
    printf("  move <from><to> - e.g., move e2e4, to move piece from e2 to e4\n");
    printf("  quit - exit the game\n");
    printf("  help - show this help message\n");
}

Position coordinateAbsolution(Position coord){
    Position temp;
    temp.x = (coord.x+258) / (56+5);
    temp.y = ((coord.y+158) / (56+5));
    return temp;
}

//Check is the click is legal
bool validateFirstClick(Board *board, Position click_pos, Color side){
    /*
    printf("1. Type: %i Color: %i \n", board->squares[1][0].type, board->squares[1][0].color);
    printf("1. Type: %i Color: %i \n", board->squares[7][6].type, board->squares[7][6].color);
    printf("0. Type: %i Color: %i \n", side, side);
    
    printf("%i, %i\n", click_pos.y, 7 - click_pos.x);
    */

    if ((board->squares[click_pos.x][click_pos.y].color != side) && (board->squares[click_pos.x][click_pos.y].type != EMPTY ))
        return true;
    else
        return false;
}

bool validateSecondClick(Board *board, Position currentPos, Color side, Position firstClick){
    
    if (is_move_valid(board, firstClick.y, firstClick.x, currentPos.y, currentPos.x)){
        return true;
    }
    return false;   
     
}
/*
void updateGame(board, side, firstClick, secondClick) {// List* capturedPiece[2]

  //add to captured list
      if (board[destCoord.x][destCoord.y].piece != EMPTY)
         insertion_list(&capturedPiece[turn], &board[destCoord.x][destCoord.y].piece, sizeof(int));

  //UPDATE THE POSITION
  board->squares[secondClick.x][secondClick.y].piece = board->squares[secondClick.x][secondClick.y].piece;
  board->squares[firstClick.x][firstClick.y].piece = EMPTY;

  board->squares[secondClick.x][secondClick.y].color = side;
  board->squares[firstClick.x][firstClick.y].color = EMPTY;
}
*/
/*
Move movePositionConstructor(int movefrom, int moveto){
    Move move = (Move*)malloc(sizeof(Move));;
    assert(move);

}


//YOU CAN USE INSERTION LIST TO DO THIS TOO
Move* generateValidMoves(Board *board, Position movefrom, int turn){

  Move* ValidMoves = malloc(22*sizeof(Move));
  for (int i = 0; i < 8; i++)
    coupPossible[i] = malloc(8*sizeof(int));

  /// For testing purposes only 
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      coupPossible[i][j] = 0;


  //PAWN
  //==============================================================
  if ( board->squares[movefrom.x][movefrom.y].piece == PAWN) {
    int pasclassique = 0; // Si on peut fair un pas classique, on met cette variable a 1

    //CLASSICAL MOVE
    if ( board->squares[movefrom.x+1][movefrom.y].piece == EMPTY && turn == WHITE){
      coupPossible[coord.x+1][coord.y] = 1;
      pasclassique = 1;
    }

    else if ( board->squares[coord.x-1][coord.y].piece == EMPTY && turn == BLACK){
      coupPossible[coord.x-1][coord.y] = 1;
      pasclassique = 1;
    }

    //FIRST MOVE
    if ( pasclassique && (( coord.x == 1 && turn == WHITE ) || ( coord.x == 6 && turn == BLACK )))
    {

      if ( board->squares[coord.x+2][coord.y].piece == EMPTY && turn == WHITE)
        coupPossible[coord.x+2][coord.y] = 1;

      else if ( board->squares[coord.x-2][coord.y].piece == EMPTY && turn == BLACK)
        coupPossible[coord.x-2][coord.y] = 1;

    }

    //TAKING OPPONENT'S PIECE
    if ( coord.y != 0 ) {
      if ( board->squares[coord.x+1][coord.y-1].color == -turn && turn == WHITE)
        coupPossible[coord.x+1][coord.y-1] = 1;
      else if ( board->squares[coord.x-1][coord.y-1].color == -turn && turn == BLACK)
        coupPossible[coord.x-1][coord.y-1] = 1;
    }
    if ( coord.y != 7 ) {
      if ( board->squares[coord.x+1][coord.y+1].color == -turn && turn == WHITE)
        coupPossible[coord.x+1][coord.y+1] = 1;
      else if ( board->squares[coord.x-1][coord.y+1].color == -turn && turn == BLACK)
        coupPossible[coord.x-1][coord.y+1] = 1;
    }

  }
  //ROOK OR QUEEN
  //==============================================================
   if ( board->squares[coord.x][coord.y].piece == ROOK || board->squares[coord.x][coord.y].piece == QUEEN) {
      int i;
      i = 1;

      while ( coord.y+i < 8 && board->squares[coord.x][coord.y+i].color != turn ) {
        coupPossible[coord.x][coord.y+i] = 1;
        if (board->squares[coord.x][coord.y+i].color == -turn)
          break;
        i++;
      }

      i = 1;
      while (  coord.y-i >= 0 && board->squares[coord.x][coord.y-i].color != turn) {
        coupPossible[coord.x][coord.y-i] = 1;
        if (board->squares[coord.x][coord.y-i].color == -turn)
          break;
        i++;
      }

      i = 1;
      while ( coord.x+i < 8 && board->squares[coord.x+i][coord.y].color != turn) {
        coupPossible[coord.x+i][coord.y] = 1;
        if (board->squares[coord.x+i][coord.y].color == -turn)
          break;
        i++;
      }

      i = 1;
      while ( coord.x-i >= 0 && board->squares[coord.x-i][coord.y].color != turn  ) {
        coupPossible[coord.x-i][coord.y] = 1;

        if (board->squares[coord.x-i][coord.y].color == -turn)
          break;
        i++;
      }
  }
  //BISHOP OR QUEEN
  //==============================================================
   if ( board->squares[coord.x][coord.y].piece == BISHOP || board->squares[coord.x][coord.y].piece == QUEEN) {
      int i;
      i = 1;

      while ( coord.y+i < 8  &&  coord.x+i < 8 && board->squares[coord.x+i][coord.y+i].color != turn ) {
        coupPossible[coord.x+i][coord.y+i] = 1;
        if (board->squares[coord.x+i][coord.y+i].color == -turn)
          break;
        i++;
      }

      i = 1;
      while ( coord.y-i >= 0  &&  coord.x+i < 8 && board->squares[coord.x+i][coord.y-i].color != turn ) {
        coupPossible[coord.x+i][coord.y-i] = 1;
        if (board->squares[coord.x+i][coord.y-i].color == -turn)
          break;
        i++;
      }

      i = 1;
      while ( coord.y+i < 8  &&  coord.x-i >= 0 && board->squares[coord.x-i][coord.y+i].color != turn ) {
        coupPossible[coord.x-i][coord.y+i] = 1;
        if (board->squares[coord.x-i][coord.y+i].color == -turn)
          break;
        i++;
      }

      i = 1;
      while ( coord.y-i >= 0  &&  coord.x-i >= 0 && board->squares[coord.x-i][coord.y-i].color != turn ) {
        coupPossible[coord.x-i][coord.y-i] = 1;
        if (board->squares[coord.x-i][coord.y-i].color == -turn)
          break;
        i++;
      }
  }
  //KNIGHT
  else if ( board->squares[coord.x][coord.y].piece == KNIGHT){

          // ONE FORWARD LEFT DIAGONAL STEP AND ANOTHER STEP TO THE LEFT
          if ((coord.x > 0 && coord.y > 1) && (board->squares[coord.x -1][coord.y -2].color != turn) )
              coupPossible[coord.x -1][coord.y - 2] = 1;

          // ONE FORWARD RIGHT DIAGONAL STEP AND ANOTHER STEP TO THE RIGHT
          if ((coord.x > 0 && coord.y < 6) && (board->squares[coord.x -1][coord.y +2].color != turn) )
              coupPossible[coord.x -1][coord.y +2] = 1;

          // ONE BACKWARD LEFT DIAGONAL STEP AND ANOTHER ONE TO THE LEFT
          if ((coord.x < 7 && coord.y > 1) && (board->squares[coord.x +1][coord.y -2].color != turn) )
              coupPossible[coord.x +1][coord.y -2] = 1;

          // ONE BACKWARD RIGHT DIAGONAL STEP AND ANOTHER STEP TO THE RIGHT
          if ((coord.x < 7 && coord.y < 6) && (board->squares[coord.x +1][coord.y +2].color != turn) )
              coupPossible[coord.x +1][coord.y +2] = 1;

          // ONE FORWARD LEFT DIAGONAL STEP AND ANOTHER FORWARD ONE
          if ((coord.x > 1 && coord.y > 0) && (board->squares[coord.x -2][coord.y -1].color != turn) )
              coupPossible[coord.x -2][coord.y -1] = 1;

          // ONE FORWARD RIGHT DIAGONAL STEP AND ANOTHER FORWARD ONE
          if ((coord.x > 1 && coord.y < 7) && (board->squares[coord.x -2][coord.y +1].color != turn) )
              coupPossible[coord.x -2][coord.y +1] = 1;

          // ONE BACKWARD DIAGONAL LEFT MOVE AND ANOTHER FORWARD MOVE
          if ((coord.x < 6 && coord.y > 0  && (board->squares[coord.x +2][coord.y -1].color != turn) ))
              coupPossible[coord.x +2][coord.y -1] = 1;

          // ONE BACKWARD DIAGONAL RIGHT MOVE AND ANOTHER BACKWARD ONE
          if ((coord.x < 6 && coord.y < 7) && (board->squares[coord.x +2][coord.y +1].color != turn) )
              coupPossible[coord.x +2][coord.y +1] = 1;

  }
  // KING
  if ( board->squares[coord.x][coord.y].piece == KING){
  // FORWARD STEP
        if ((board->squares[coord.x + 1][coord.y].color != turn) && (coord.x < 7 ))
            coupPossible[coord.x + 1][coord.y] = 1;

        // BACKWARD STEP
        if ((board->squares[coord.x -1][coord.y].color != turn) && (coord.x > 0))
            coupPossible[coord.x -1][coord.y] = 1;

        // MOVE TO THE RIGHT
        if ((board->squares[coord.x][coord.y + 1].color != turn) && (coord.y < 7))
            coupPossible[coord.x][coord.y + 1] = 1;

        // MOVE TO THE LEFT
        if ((board->squares[coord.x][coord.y - 1].color != turn) && (coord.y > 0))
            coupPossible[coord.x][coord.y - 1] = 1;

        // FORWARD LEFT DIAGONAL MOVE
        if ((board->squares[coord.x - 1][coord.y - 1].color != turn) && (coord.x > 0 && coord.y > 0))
            coupPossible[coord.x - 1][coord.y - 1] = 1;

        // FORWARD RIGHT DIAGONAL MOVE
        if ((board->squares[coord.x -1][coord.y + 1].color != turn) && (coord.x > 0 && coord.y < 7))
            coupPossible[coord.x - 1][coord.y + 1] =1;

        // BACKWARD RIGHT DIAGONAL MOVE
        if ((board->squares[coord.x + 1][coord.y + 1].color != turn ) && (coord.x < 7 && coord.y < 7))
            coupPossible[coord.x +1][coord.y +1] = 1;

        // BACKWARD LEFT DIAGONAL MOVE
         if ((board->squares[coord.x +1][coord.y -1].color != turn) && (coord.x < 7 && coord.y > 0))
            coupPossible[coord.x +1][coord.y -1] =1;

    }

  // coupPossible[coord.x][coord.y] = 2;

  return coupPossible;
}
*/

