
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "gameStructures.h"
#include "eatLogic.h"
#include "eatDraw.h"

// game data

node circle;
node oldcircle;
node square;

int dir;
bool eaten;
int number;

SDL_Renderer* renderer = NULL;

SDL_Surface*  white_surface = NULL;
SDL_Surface*  square_surface = NULL;
SDL_Surface*  circle_surface = NULL;

SDL_Texture*  white_texture = NULL;
SDL_Texture*  square_texture = NULL;
SDL_Texture*  circle_texture = NULL;

// initialise the game data

void init(void)
{
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
    
    atexit(SDL_Quit); // set for clean-up on exit

    // SDL structures
    
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetWindowTitle( window, "Circles eat squares");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    square_surface = SDL_LoadBMP("images/square.bmp");
    circle_surface = SDL_LoadBMP("images/circle.bmp");
    white_surface = SDL_LoadBMP("images/white.bmp");

    square_texture = SDL_CreateTextureFromSurface(renderer, square_surface);
    circle_texture = SDL_CreateTextureFromSurface(renderer, circle_surface);
    white_texture = SDL_CreateTextureFromSurface(renderer, white_surface);

    // game data    

    square.x = 5;
    square.y = 5;

    circle = square;
    oldcircle = circle;

    dir = RIGHT;
    
    next_square();
    eaten = true;
    number = 0;

    return;
}

// render current game state

void render(void)
{
    if (eaten) 
        draw_object(square,square_texture); // draw new square if required
     
    draw_object(oldcircle,white_texture);   // redraw old location
    draw_object(circle,circle_texture);     // draw new location

    SDL_RenderPresent(renderer);

    return;
}

// draw game component

void draw_object( node object, SDL_Texture *texture ) 
{
    SDL_Rect rect;
    rect.h = TILE_SIZE;
    rect.w = TILE_SIZE;
    rect.x = object.x * TILE_SIZE;
    rect.y = object.y * TILE_SIZE;
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    return;
}

