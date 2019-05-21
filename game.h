#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define WIDTH 4
#define PLAYER 1
#define CUTOFF_DEPTH 7
#define AI 0

struct state{
    char grid[WIDTH][WIDTH];
    int x,y;
    int turn;
    int depth;
    
    struct state *next;
};

typedef struct state state;


/* Prototypes for the functions of game.c*/
void print_grid(char grid[WIDTH][WIDTH]);
int valid_move(int x, int y, char grid[WIDTH][WIDTH]);
int win(int x, int y, char grid[WIDTH][WIDTH]);
void player_move(int *x, int *y, char grid[WIDTH][WIDTH]);

/* Prototypes for external functions and variables*/
void computer_move(int *x, int *y, char grid[WIDTH][WIDTH]);
extern long int counter;

#endif
