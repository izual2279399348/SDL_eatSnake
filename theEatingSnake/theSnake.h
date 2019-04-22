#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Snakestructure.h"
#ifndef THESNAKE_H
#define THESNAKE_H
void get_dx_dy(int *dx, int *dy, Dir dir);
void snake_set_dir(Dir dir, theSnake *theHead);
void place_the_food(Food *theFood);
theSnake *CreateSnake(int the_x, int the_y, Dir thedir);
void grow_snake(theSnake *thelastNode);
void snake_init(int thesize, theSnake *theHead);
theSnake *get_lastNode(theSnake *theHead);
bool is_invalid_move(int x, int y, theSnake *theHead);
void the_move(theSnake *theHead);
void the_grow(theSnake *theHead);
bool snake_move(bool *has_eaten_food, theSnake *theHead, Food *theFood);
Dir snake_get_dir(theSnake *theHead);
void update_game_state( theSnake *theHead, Food *theFood);
#endif // THESNAKE_H
