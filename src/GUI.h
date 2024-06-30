#ifndef GUI_H_
#define GUI_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "chess.h"
#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>

void tempdisplayMenu(SDL_Surface *screen, int state);
void displayGame(Board *board, SDL_Surface *screen, Position followMouse, Position hintPos, int state, Position* hintPositions, int moveCount);
void displayMenu(SDL_Surface *screen, int state);
void flipBOARD(int flip);
int getClick(SDL_Surface *screen, Position *position, int moveClick, int state);
void instantiateMenu();
void instantiateSprites();
Position coordinateAbsolution(Position coord);
void showWarning();

#endif
