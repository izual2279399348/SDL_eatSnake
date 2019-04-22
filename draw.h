#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Snakestructure.h"
#ifndef DRAW_H
#define DRAW_H
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

// 4:3 aspect ratio is assumed
//
// FIELD_CELL_WIDTH has to divisible by 4, will have to divide SCREEN_WIDTH
#define FIELD_CELL_WIDTH 32
#define CELL_SIZE ((SCREEN_WIDTH) / (FIELD_CELL_WIDTH))
#define FIELD_CELL_HEIGHT ((FIELD_CELL_WIDTH) / 4 * 3)

#define FIELD_START_CELL_X 0
#define FIELD_START_CELL_Y 0
void draw_field(SDL_Renderer *renderer);
void draw_food(SDL_Renderer *renderer, Food *theFood);
void draw_thesnake(SDL_Renderer *renderer, theSnake *theHead);
void draw_screen(SDL_Renderer *renderer, theSnake *theHead, Food *theFood);
#endif // DRAW_H
