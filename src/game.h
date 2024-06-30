#include "log.h"
#include "chess.h"
#include "chess_ai.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "GUI.h"
#include <time.h>
#include <ctype.h>  // for tolower()
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>

void printHelp();
void printMenu();

void startGamePVP(Board *notboard, Color side, int timer, SDL_Surface *screen); //side = 0 = W / = 1 = B , timer = timer time, 0 or -1 for no timer
void startGamePVC(Board *notboard, int side, int difficulty, SDL_Surface *screen); //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default)
void startGameCVC(Board *notboard, int difficultyW, int difficultyB, SDL_Surface *screen); //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default)

void easystartGamePVP(Board *notboard, Color side, int timer); //side = 0 = W / = 1 = B , timer = timer time, 0 or -1 for no timer
void easystartGamePVC(Board *notboard, int side, int difficulty); //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default)
void easystartGameCVC(Board *notboard, int difficultyW, int difficultyB); //side = 0 = W / = 1 = B , difficulty = 1,2,3 (1 default)

bool validateFirstClick(Board *board, Position click_pos, Color side);
bool validateSecondClick(Board *board, Position currentPos, Color side, Position firstClick);

Position coordinateAbsolution(Position coord);