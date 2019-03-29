
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "gameStructures.h"
#include "eatLogic.h"

// game variables (external)

extern node circle;
extern node oldcircle;
extern node square;

extern int dir;
extern bool eaten;
extern int number;

extern SDL_Renderer* renderer;

extern SDL_Surface*  white_surface;
extern SDL_Surface*  square_surface;
extern SDL_Surface*  circle_surface;

extern SDL_Texture*  white_texture;
extern SDL_Texture*  square_texture;
extern SDL_Texture*  circle_texture;

// read keyboard input

void input(void)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    SDL_PumpEvents();

    if (state[SDL_SCANCODE_UP]) {
        dir = UP;
    } 
    else if (state[SDL_SCANCODE_DOWN]) {
        dir = DOWN;
    } 
    else if (state[SDL_SCANCODE_LEFT]) {
        dir = LEFT;
    } 
    else if (state[SDL_SCANCODE_RIGHT]) {
        dir = RIGHT;
    } 
    else if (state[SDL_SCANCODE_ESCAPE]) {
        exit(0);
    }
    return;
}

// update player position

bool update(void)
{
    oldcircle = circle;

    switch (dir) {
        case UP:
            circle.y = circle.y - 1;
            break;
        case DOWN:
            circle.y = circle.y + 1;
            break;
        case LEFT:
            circle.x = circle.x - 1;
            break;
        case RIGHT:
            circle.x = circle.x + 1;
            break;
    }

    if (circle.x < 0 || circle.x > MAX_X || circle.y < 0 || circle.y > MAX_Y) {
        return false; // lose
    }

    if (circle.x == square.x && circle.y == square.y) {
        next_square();
        number++;
        eaten = true;  // eat square
    } else {
        eaten = false; // continue
    }

    return true;
}

// generate new square location

void next_square(void)
{
    square.x = (square.x * 6 + 1) % (MAX_X + 1);
    square.y = (square.y * 16 + 1) % (MAX_Y + 1);
}

// game over

void gameover(void)
{
    printf("Eaten: %d\n", number);
    printf("Game Over\n");
    exit(0);
}


