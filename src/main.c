#include "game.h"
#include <stdbool.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include "chess.h"
#include "chess_ai.h"
#include <stdio.h>
#include <ctype.h>  // for tolower()
#include <string.h>
#undef main

// logging commented out until it's fixed
int main() {

    int GraphicsMode = 0; //0 No GUI, 1 No Clickable GUI, 2 Full GUI
    
    printf("Would you like to enable the GUI? (0 for disable, 1 for enable): ");
    scanf("%i", &GraphicsMode);
    
    if (GraphicsMode == 1){
        SDL_Surface *screen = NULL;
        
        if (SDL_Init(SDL_INIT_VIDEO)){
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }

        SDL_WM_SetCaption("Martin Bot Lite ", NULL);
        
        screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

        if (screen == NULL)
        {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
        }
        
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        
        instantiateMenu();
        instantiateSprites();

        Board board;
        //Color user_color, ai_color;
        //int user_side, start_x, start_y, end_x, end_y;
        //bool undo = false;


        // Initialize log
        init_log("chess_log.txt");

        int startGame = 0;
        int gameType;
        Color side = WHITE;

        printf("Welcome to Chess Program!\n");
        //displayMenu(screen, 0);
        printf("Would you like to start a game? 0 - Y, 1 - N, 2 - Skip to the Board\n");
        displayMenu(screen, 0);

        //scanf("%i", &startGame);
        Position mousePosition;
        while(1){    
            getClick(screen, &mousePosition, 100, 1);
            if (mousePosition.x > 280 && mousePosition.x < 735 && mousePosition.y > 325 && mousePosition.y < 505){
                startGame = 1;
                break;
            }
            else if (mousePosition.x > 800 && mousePosition.x < 950 && mousePosition.y > 50 && mousePosition.y < 110){
                startGame = 2;
                break;
            }
        }
        //startGame = 2;
        if (startGame == 2){
            initialize_board(&board);
            
            //Comment in the one you want to test
            startGamePVP(&board, WHITE, -1, screen);
            //startGamePVC(&board, WHITE, 1, screen);
            //startGameCVC(&board, 1, 1, screen);
        }    
        else  {
            printf("Game Starting\n");
        }
        //startGame = 0;
        printf("Would you like to setup the board? 0 - Y, 1 - N \n");
        displayMenu(screen, 1);
        while(1){    
            getClick(screen, &mousePosition, 100, 1);
            //printf("%i, %i \n", mousePosition.x, mousePosition.y);
            if (mousePosition.x > 120 && mousePosition.x < 465 && mousePosition.y > 415 && mousePosition.y < 580){
                startGame = 1;
                break;
            }
            else if (mousePosition.x > 560 && mousePosition.x < 910 && mousePosition.y > 415 && mousePosition.y < 580){
                startGame = 2;
                break;
            }
        }
        printf("Not implemented yet\n");
        //BOARD SETUP HERE
        initialize_board(&board);
        displayMenu(screen, 2);
        printf("What type of game do you want to play? 0 - PVP, 1 - Player vs CPU, 2 - CPU vs CPU\n");
        while(1){    
            getClick(screen, &mousePosition, 100, 1);
            //printf("%i, %i \n", mousePosition.x, mousePosition.y);
            if (mousePosition.x > 40 && mousePosition.x < 340 && mousePosition.y > 420 && mousePosition.y < 635){
                gameType = 0;
                break;
            }
            else if (mousePosition.x > 355 && mousePosition.x < 650 && mousePosition.y > 420 && mousePosition.y < 635){
                gameType = 1;
                break;
            }
            else if (mousePosition.x > 670 && mousePosition.x < 965 && mousePosition.y > 420 && mousePosition.y < 635){
                gameType = 2;
                break;
            }
        }
        switch(gameType){
            case 0: //PVP
                printf("What side do you want to play?\n");
                displayMenu(screen, 11);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 130 && mousePosition.x < 350 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = WHITE;
                        break;
                    }
                    else if (mousePosition.x > 585 && mousePosition.x < 835 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = BLACK;
                        break;
                    }
                }
                printf("Would you like a timer?\n");
                displayMenu(screen, 12);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 140 && mousePosition.x < 415 && mousePosition.y > 390 && mousePosition.y < 565){
                        startGame = 1;
                        break;
                    }
                    else if (mousePosition.x > 620 && mousePosition.x < 900 && mousePosition.y > 390 && mousePosition.y < 565){
                        startGame = -1;
                        break;
                    }
                }
                int timer = -1;
                if (startGame == 1){
                    printf("How long would the timer be?\n");
                    displayMenu(screen, 13);
                    while(1){    
                        getClick(screen, &mousePosition, 100, 1);
                        //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                        if (mousePosition.x > 265 && mousePosition.x < 510 && mousePosition.y > 430 && mousePosition.y < 575){
                            timer = 60;
                            break;
                        }
                        else if (mousePosition.x > 520 && mousePosition.x < 760 && mousePosition.y > 430 && mousePosition.y < 575){
                            timer = 300;
                            break;
                        }
                        else if (mousePosition.x > 265 && mousePosition.x < 510 && mousePosition.y > 585 && mousePosition.y < 730){
                            timer = 600;
                            break;
                        }
                        else if (mousePosition.x > 520 && mousePosition.x < 760 && mousePosition.y > 585 && mousePosition.y < 730){
                            timer = 1200;
                            break;
                        }
                    }
                }
                printf("\nstarting game~~~");
                startGamePVP(&board, side, timer, screen);
                break;
                //startGamePVP(&board, WHITE, var2, screen);
            case 1: //PVC
                printf("What side do you want to play?\n");
                displayMenu(screen, 21);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 130 && mousePosition.x < 350 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = WHITE;
                        break;
                    }
                    else if (mousePosition.x > 585 && mousePosition.x < 835 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = BLACK;
                        break;
                    }
                }
                //int difficulty = 1;
                printf("What difficulty should the CPU be?\n");
                displayMenu(screen, 22);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 5 && mousePosition.x < 310 && mousePosition.y > 305 && mousePosition.y < 440){
                        timer = 1;
                        break;
                    }
                    else if (mousePosition.x > 315 && mousePosition.x < 670 && mousePosition.y > 305 && mousePosition.y < 440){
                        timer = 300;
                        break;
                    }
                    else if (mousePosition.x > 680 && mousePosition.x < 990 && mousePosition.y > 305 && mousePosition.y < 440){
                        timer = 600;
                        break;
                    }
                }
                
                startGamePVC(&board, WHITE, 1, screen);
                break;
                //startGamePVC(&board, var1, var2, screen);
            case 2: //CVC
                printf("What difficulty should the CPU be?\n");
                int difficultyOne = 1;
                displayMenu(screen, 31);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 5 && mousePosition.x < 310 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyOne = 1;
                        break;
                    }
                    else if (mousePosition.x > 315 && mousePosition.x < 670 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyOne = 300;
                        break;
                    }
                    else if (mousePosition.x > 680 && mousePosition.x < 990 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyOne = 600;
                        break;
                    }
                }
                int difficultyTwo = 1;
                printf("What difficulty should the CPU be?\n");
                displayMenu(screen, 32);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    //printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 5 && mousePosition.x < 310 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyTwo = 1;
                        break;
                    }
                    else if (mousePosition.x > 315 && mousePosition.x < 670 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyTwo = 300;
                        break;
                    }
                    else if (mousePosition.x > 680 && mousePosition.x < 990 && mousePosition.y > 305 && mousePosition.y < 440){
                        difficultyTwo = 600;
                        break;
                    }
                }
                startGameCVC(&board, difficultyOne, difficultyTwo, screen);
                break;
                //startGameCVC(&board, var1, var2, screen);
        }
    }    
    else{
        
        Board board;
        //Color user_color, ai_color;
        //int user_side, start_x, start_y, end_x, end_y;
        //bool undo = false;

        // Initialize log
        init_log("chess_log.txt");

        int startGame = 1;
        int gameType;
        Color side = WHITE;

        printf("Welcome to Chess Program!\n");
        //displayMenu(screen, 0);
        printf("Would you like to start a game? 0 - Y, 1 - N, 2 - Skip to the Board\n");
        scanf("%i", &startGame);
        
        while(startGame == 1){
            printf("Would you like to start a game? 0 - Y, 1 - N, 2 - Skip to the Board\n");    
            scanf("%i", &startGame);
        }
        //startGame = 2;
        if (startGame == 2){
            initialize_board(&board);
            
            //Comment in the one you want to test
            easystartGamePVP(&board, WHITE, -1);
            //startGamePVC(&board, WHITE, 1, screen);
            //startGameCVC(&board, 1, 1, screen);
        }    
        else  {
            printf("Starting Game\n");
        }
        //startGame = 0;
        printf("Would you like to setup the board? 0 - Y, 1 - N \n");
        //scanf("%i", &startGame);
        //displayMenu(screen, 1);
        /*
        while(1){    
            scanf("%i", &startGame);
            break;
        }
        */
        printf("Not implemented yet.\n");
        //BOARD SETUP HERE
        initialize_board(&board);
        //displayMenu(screen, 2);
        printf("What type of game do you want to play? 0 - PVP, 1 - Player vs CPU, 2 - CPU vs CPU\n");
        scanf("%i", &gameType);
        while(gameType < 0 || gameType > 2){    
            printf("What type of game do you want to play? 0 - PVP, 1 - Player vs CPU, 2 - CPU vs CPU\n");
            scanf("%i", &gameType);
        }
        switch(gameType){
            case 0: //PVP
                /*
                printf("What side do you want to play?\n");
                displayMenu(screen, 11);
                while(1){    
                    getClick(screen, &mousePosition, 100, 1);
                    printf("%i, %i \n", mousePosition.x, mousePosition.y);
                    if (mousePosition.x > 130 && mousePosition.x < 350 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = WHITE;
                        break;
                    }
                    else if (mousePosition.x > 585 && mousePosition.x < 835 && mousePosition.y > 325 && mousePosition.y < 635){
                        side = BLACK;
                        break;
                    }
                }
                */
                side = WHITE;
                printf("Would you like a timer? 0 - Y, 1 - N \n");
                scanf("%i", &startGame);
                while(startGame < 0 || startGame > 1){    
                    printf("Would you like a timer? 0 - Y, 1 - N \n");
                    scanf("%i", &startGame);
                }
                int timer = -1;
                if (startGame == 0){
                    printf("How long would the timer be? Enter an integer amount of seconds.\n");
                    scanf("%i", &timer);
                    while(timer < 0 ){    
                        printf("How long would the timer be? Enter an integer amount of seconds.\n");
                        scanf("%i", &timer);
                    }
                }
                printf("\nstarting game~~~");
                easystartGamePVP(&board, side, timer);
                break;
                //startGamePVP(&board, WHITE, var2, screen);
            case 1: //PVC
                printf("What side do you want to play? 0 - White, 1 - Black\n");
                scanf("%i", &startGame);
                while(startGame < 0 || startGame > 1){    
                    printf("What side do you want to play? 0 - White, 1 - Black\n");
                    scanf("%i", &startGame);
                }
                side = startGame == 0 ? WHITE : BLACK;
                int difficulty = 1;
                printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                scanf("%i", &difficulty);
                while(difficulty < 0 || difficulty > 2){    
                    printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                    scanf("%i", &difficulty);
                }
                easystartGamePVC(&board, WHITE, difficulty);
                break;
                //startGamePVC(&board, var1, var2, screen);
            case 2: //CVC
                printf("What difficulty should the CPU be?\n");
                int difficultyOne = 1;
                printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                scanf("%i", &difficultyOne);
                while(difficultyOne < 0 || difficultyOne > 2){    
                    printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                    scanf("%i", &difficultyOne);
                }
                int difficultyTwo = 1;
                printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                scanf("%i", &difficultyTwo);
                while(difficultyTwo < 0 || difficultyTwo > 2){    
                    printf("What difficulty should the CPU be? 0 - Easy, 1 - Medium, 2 - Hard\n");
                    scanf("%i", &difficultyTwo);
                }
                easystartGameCVC(&board, difficultyOne, difficultyTwo);
                break;
                //startGameCVC(&board, var1, var2, screen);
    }
    printf("Thank you for playing!\n");
    close_log();
    SDL_Delay(1000);

    SDL_Quit();

    return 0;

    }
}
