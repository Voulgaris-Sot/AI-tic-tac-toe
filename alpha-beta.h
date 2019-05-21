#ifndef ALPHABETA_H_INCLUDED
#define ALPHABETA_H_INCLUDED

#include "game.h"

extern long int counter;

/* Prototypes for the functions */
int alpha_beta(state *s,int alpha,int beta,int *movex,int *movey);
void computer_move(int *x, int *y, char grid[WIDTH][WIDTH]);
state * generate_children(state *s);
state * add_to_list(state *new,state *head);
void free_children(state *head);

#endif
