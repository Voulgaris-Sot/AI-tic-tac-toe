#ifndef ALPHABETACUTOFF_H_INCLUDED
#define ALPHABETACUTOFF_H_INCLUDED

#include "game.h"

extern long int counter;

/* Prototypes for the functions */
int heuristic(int turn, char grid[WIDTH][WIDTH]);
int alpha_beta_cutoff(state *s,int alpha,int beta,int *movex,int *movey);
void computer_move(int *x, int *y, char grid[WIDTH][WIDTH]);
state * generate_children(state *s);
state * add_to_list(state *new,state *head);
void free_children(state *head);

#endif
