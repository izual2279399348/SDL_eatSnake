#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "test2.c"

int main(int argc, char *argv[])
{
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
    snake_init(5, 0, 4, RIGHT);
    place_apple();
    draw_screen(renderer);
    bool last_move_drawn = true;
    int n_frames_mod = 0;
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
                    if (snake_get_dir() != DOWN && snake_get_dir() != UP &&
                            last_move_drawn) {
                        snake_set_dir(UP);
                        last_move_drawn = false;
                    }else if(snake_get_dir() == UP&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_DOWN:
                    if (snake_get_dir() != UP && snake_get_dir() != DOWN &&
                            last_move_drawn) {
                        snake_set_dir(DOWN);
                        last_move_drawn = false;
                    }else if(snake_get_dir() == DOWN&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_LEFT:
                    if (snake_get_dir() != RIGHT && snake_get_dir() != LEFT &&
                            last_move_drawn) {
                        snake_set_dir(LEFT);
                        last_move_drawn = false;
                    }else if(snake_get_dir() == LEFT&&last_move_drawn){
                        n = 2;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake_get_dir() != LEFT && snake_get_dir() != RIGHT &&
                            last_move_drawn) {
                        snake_set_dir(RIGHT);
                        last_move_drawn = false;
                    }else if(snake_get_dir() == RIGHT&&last_move_drawn){
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

        if (n_frames_mod%n == 0) {
            update_game_state();
            last_move_drawn = true;
            n_frames_mod = 0;
            n = count_;
        }

        draw_screen(renderer);
        SDL_RenderPresent(renderer);
        n_frames_mod++;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
