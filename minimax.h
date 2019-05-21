#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED

#include "game.h"

extern long int counter;

/* Prototypes for the functions */
void computer_move(int *x, int *y, char grid[WIDTH][WIDTH]);
int minimax(state *s,int *movex,int *movey);
state * generate_children(state *s);
state * add_to_list(state *new,state *head);
void free_children(state *head);

#endif
