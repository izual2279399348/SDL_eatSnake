#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Snakestructure.h"
#include "draw.h"
#include "theSnake.h"


int main(int argc, char *argv[]){
    int n = 8;
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    SDL_Window *window =
        SDL_CreateWindow("Snake",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN
        );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // make the scaled rendering look smoother.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    int quit = 0;
    int count_;
    count_ = n;
    theSnake *theHead;
    Food theFood;
    theHead=CreateSnake(4,0,RIGHT);
    snake_init(5,theHead);
    place_the_food(&theFood);
    draw_screen(renderer, theHead, &theFood);
    bool last_move_drawn = true;
    int speed = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_UP:
                    if (snake_get_dir(theHead) != DOWN && snake_get_dir(theHead) != UP &&
                            last_move_drawn) {
                        snake_set_dir(UP, theHead);
                        last_move_drawn = false;
                    }else if(snake_get_dir(theHead) == UP&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_DOWN:
                    if (snake_get_dir(theHead) != UP && snake_get_dir(theHead) != DOWN &&
                            last_move_drawn) {
                        snake_set_dir(DOWN, theHead);
                        last_move_drawn = false;
                    }else if(snake_get_dir(theHead) == DOWN&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_LEFT:
                    if (snake_get_dir(theHead) != RIGHT && snake_get_dir(theHead) != LEFT &&
                            last_move_drawn) {
                        snake_set_dir(LEFT, theHead);
                        last_move_drawn = false;
                    }else if(snake_get_dir(theHead) == LEFT&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake_get_dir(theHead) != LEFT && snake_get_dir(theHead) != RIGHT &&
                            last_move_drawn) {
                        snake_set_dir(RIGHT, theHead);
                        last_move_drawn = false;
                    }else if(snake_get_dir(theHead) == RIGHT&&last_move_drawn){
                        n = 2;
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (speed%n == 0) {
            update_game_state(theHead, &theFood);
            last_move_drawn = true;
            speed = 0;
            n = count_;
        }

        draw_screen(renderer, theHead, &theFood);
        SDL_RenderPresent(renderer);
        speed++;
    }
    destroysnake(theHead);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
