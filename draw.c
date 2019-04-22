#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "draw.h"
#include "theSnake.h"
#include "Snakestructure.h"

extern int count_size;
const SDL_Color BLACK = { .r = 0, .g = 0, .b = 0, .a = 255 };
const SDL_Color WHITE = { .r = 255, .g = 255, .b = 255, .a = 255 };

const SDL_Color RED = { .r = 255, .g = 0, .b = 0, .a = 255 };
const SDL_Color MAROON =  { .r = 128, .g = 0, .b = 0, .a = 255 };

const SDL_Color BLUE = { .r = 0, .g = 0, .b = 255, .a = 255 };
const SDL_Color NAVY = { .r = 0, .g = 0, .b = 128, .a = 255 };

const SDL_Color LIME = { .r = 0, .g = 255, .b = 0, .a = 255 };
const SDL_Color GREEN = { .r = 0, .g = 128, .b = 0, .a = 255 };

void draw_field(SDL_Renderer *renderer)
{
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(renderer, NAVY.r, NAVY.g, NAVY.b, NAVY.a);
    SDL_Rect field = {
        FIELD_START_CELL_X * CELL_SIZE,
        FIELD_START_CELL_Y * CELL_SIZE,
        FIELD_CELL_WIDTH * CELL_SIZE,
        FIELD_CELL_HEIGHT * CELL_SIZE
    };

    SDL_RenderFillRect(renderer, &field);
    SDL_SetRenderDrawColor(renderer, BLUE.r, BLUE.g, BLUE.b, BLUE.a);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);
    for (int i = 1; i < FIELD_CELL_WIDTH; i++) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0,
                i * CELL_SIZE, FIELD_CELL_HEIGHT * CELL_SIZE);
    }
    for (int i = 1; i < FIELD_CELL_HEIGHT; i++) {
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE,
                FIELD_CELL_WIDTH * CELL_SIZE, i * CELL_SIZE);
    }

    SDL_SetRenderDrawColor(renderer, prev.a, prev.g, prev.b, prev.a);
}

void draw_food(SDL_Renderer *renderer, Food *theFood){
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.r, &prev.g, &prev.b, &prev.a);
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);

    SDL_Rect food_cell = {
        .x = theFood->x * CELL_SIZE, .y = theFood->y * CELL_SIZE,
        .w = CELL_SIZE, .h = CELL_SIZE
    };
    SDL_RenderFillRect(renderer, &food_cell);
    SDL_SetRenderDrawColor(renderer, MAROON.r, MAROON.g, MAROON.b,
            MAROON.a);
    SDL_RenderDrawRect(renderer, &food_cell);
    SDL_SetRenderDrawColor(renderer, prev.r, prev.g, prev.b, prev.a);
}


void draw_thesnake(SDL_Renderer *renderer, theSnake *theHead){
    SDL_Color prev;
    SDL_GetRenderDrawColor(renderer, &prev.a, &prev.g, &prev.b, &prev.a);
    if(theHead->num == count_size){
        SDL_Rect cell ={ theHead->x * CELL_SIZE, theHead->y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_SetRenderDrawColor(renderer, LIME.r, LIME.g, LIME.b, LIME.a);
        SDL_RenderFillRect(renderer, &cell);
        SDL_SetRenderDrawColor(renderer,GREEN.r,GREEN.g,GREEN.b, 255);
        SDL_RenderDrawRect(renderer, &cell);
        SDL_SetRenderDrawColor(renderer, prev.a, prev.g, prev.b, prev.a);
    }else{
        SDL_Rect cell ={ theHead->x * CELL_SIZE, theHead->y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_SetRenderDrawColor(renderer, LIME.r, LIME.g, LIME.b, LIME.a);
        SDL_RenderFillRect(renderer, &cell);
        SDL_SetRenderDrawColor(renderer,GREEN.r,GREEN.g,GREEN.b, 255);
        SDL_RenderDrawRect(renderer, &cell);
        draw_thesnake(renderer, theHead->next);
    }
}
void draw_screen(SDL_Renderer *renderer, theSnake *theHead, Food *theFood){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_field(renderer);
    draw_food(renderer, theFood);
    draw_thesnake(renderer,theHead);
}
