#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "draw.c"

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

int count_size = 0;
void get_dx_dy(int *dx, int *dy, Dir dir)
{
    switch (dir) {
    case UP:
        *dy = -1;
        *dx = 0;
        break;
    case DOWN:
        *dy = 1;
        *dx = 0;
        break;
    case RIGHT:
        *dy = 0;
        *dx = 1;
        break;
    case LEFT:
        *dy = 0;
        *dx = -1;
        break;
    default:
        *dy = 0;
        *dx = 0;
        break;
    }
}

void snake_set_dir(Dir dir, theSnake *theHead)
{
    if (count_size != 0) {
        theHead.dir = dir;
    }
}

bool is_cell_occupied[FIELD_CELL_WIDTH][FIELD_CELL_HEIGHT];

typedef struct Food {
    int x;
    int y;
} Food;

Food theFood;

void place_the_food(){
    do{
        theFood.x = rand() % FIELD_CELL_HEIGHT;
        theFood.y = rand() % FIELD_CELL_WIDTH;
    }while((is_cell_occupied[theFood.x][theFood.y]));
}

theSnake *CreateSnake(int the_x, int the_y, Dir thedir){
    count_size++;
    theSnake *snake_ = NULL;
    snake_ = (theSnake *)malloc(sizeof(theSnake));
    snake_->x = the_x;
    snake_->y = the_y;
    snake_->num = count_size;
    snake_->dir = thedir;
    snake_->next = NULL;
    return snake_;
}

void grow_snake(theSnake *thelastNode){
    int dx,dy;
    get_dx_dy(&dx, &dy, thelastNode.dir);
    thelastNode->next = CreateSnake(thelastNode.x-dx, thelastNode.y-dy, thelastNode.dir);
}

void snake_init(int size, int thex, int they, Dir dir_,theSnake *theHead){
    if(theHead->num == size){
        is_cell_occupied[theHead.x][theHead.y] = true;
        return;
    }else if(theHead->num == 1){
        theHead = CreateSnake(thex, they, dir_);
        is_cell_occupied[theHead.x][theHead.y] = true;
        grow_snake(theHead);
        snake_init(size, thex, they, dir_, theHead->next);
    }else{
        is_cell_occupied[theHead.x][theHead.y] = true;
        grow_snake(theHead);
        snake_init(size, thex, they, dir_, theHead->next)
    }
}

theSnake *get_lastNode(theSnake *theHead){
    if(theHead.num == count_size){
        return theHead;
    }else{
        get_lastNode(theHead.next);
    }
}

bool is_invalid_move(int x, int y, theSnake *theHead){
    theSnake *lastNode;
    lastNode = get_lastNode(theHead);
    if(y >= FIELD_CELL_HEIGHT || y < 0 ||
       x>=FIELD_CELL_WIDTH || x < 0 ||
       (is_cell_occupied[x][y] &&!(y == lastNode.y &&x == lastNode.x))){
        return true;
       }else{
        return false;
       }
}

void the_move(theSnake *theHead){
    int dx,dy;
    if(theHead->num == count_size){
        is_cell_occupied[theHead->x][theHead->y] = false;
        get_dx_dy(&dx, &dy, theHead.dir);
        theHead.x+=dx;
        theHead.y+=dy;
        return;
    }else if(theHead.num == 1){
        get_dx_dy(&dx, &dy, theHead.dir);
        theHead.x+=dx;
        theHead.y+=dy;
        is_cell_occupied[theHead.x][theHead.y] = true;
        the_move(theHead->next);
    }else{
        get_dx_dy(&dx, &dy, theHead.dir);
        theHead.x+=dx;
        theHead.y+=dy;
        the_move(theHead->next);
    }
}

void the_grow(theSnake *theHead){
    if(theHead.num == count_size && theHead->next == NULL){
        theHead->next = CreateSnake(theHead.x, theHead.y, theHead.dir);
    }else{
        the_grow(theHead->next);
    }
}

bool snake_move(bool *has_eaten_food, theSnake *theHead){
    *has_eaten_food = false;
    theSnake *thetail;
    int dx,dy;
    get_dx_dy(&dx, &dy, theHead.dir);
    if(is_invalid_move(theHead.x+dx, theHead.y+dy, theHead)){
        return true;
    }
    the_move(theHead);
    if(theHead.x + dx == Food.x && theHead.y + dy == Food.y){
        thetail = get_lastNode(theHead);
        is_cell_occupied[thetail.x][thetail.y] = true;
        the_grow(theHead);
        *has_eaten_food = true;
    }
    return false;
}

void update_game_state()
{
    bool has_eaten_food = false;
    if (snake_move(&has_eaten_food)) {
        exit(0);
    }

    if (has_eaten_food) {
        place_the_food();
    }
}
