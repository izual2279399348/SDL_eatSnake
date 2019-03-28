
#define LEFT  1
#define UP    2
#define DOWN  3
#define RIGHT 4
#define MAX_X 24
#define MAX_Y 14
#define TILE_SIZE 32
typedef struct game_node {
    int x;
    int y;
} node;

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

