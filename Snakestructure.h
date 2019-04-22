#include <stdio.h>
#ifndef SNAKESTRUCTURE_H
#define SNAKESTRUCTURE_H

typedef enum dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} Dir;

typedef struct thesnake{
    int num;
    int x;
    int y;
    Dir dir;
    struct thesnake *next;
} theSnake;

typedef struct Food {
    int x;
    int y;
} Food;
#endif // SNAKESTRUCTURE_H
