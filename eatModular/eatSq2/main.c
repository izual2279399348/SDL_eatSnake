
#include <stdbool.h>

#include <SDL2/SDL.h>
#include "eatLogic.c"
#include "eatDraw.c"
#include "gameStructures.h"
#include "eatLogic.h"
#include "eatDraw.h"

int main( int argc, char *argv[] )
{
    int delay = 160;

    init();   // setup the game data
    render(); // render initial state

    while( true ) {      // game loop

        input();           // keyboard input

        if( !update() )    // update and check
            gameover();    // if finished

        render();          // render new state

        SDL_Delay( delay );
    }
    return 0;
}

