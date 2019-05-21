#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "alpha-beta-cutoff.h"
#include "game.h"

long int counter=0;

//take the last move and returns the move of the computer
void computer_move(int *x, int *y, char grid[WIDTH][WIDTH])
{
    state *s = malloc(1*sizeof(state));
    memcpy(s->grid,grid,WIDTH*WIDTH*sizeof(char));
    s->x = *x;
    s->y = *y;
    s->turn = AI;
    s->depth = 0;//0 or 1??
    s->next = NULL;
    
    counter++;

    printf("alpha-beta-cutoff:%d\n",alpha_beta_cutoff(s,INT_MIN,INT_MAX,x,y));
    
    printf("\nComputer move is %d %d\n",*x,*y);
       
    grid[*x][*y]='o';
    
    free(s);
    return ;
}

int heuristic(int turn, char grid[WIDTH][WIDTH])
{
    int i,j,score,found_row,found_column,found_main_diagonal,found_sec_diagonal;
    char c;
    
    score = 0;

    if( turn == PLAYER){
        c = 'o';
    }else{
        c = 'x';
    }
    
    for( i=1; i<WIDTH; i++){
        found_row = 0;
        found_column = 0;
        for( j=1; j<WIDTH; j++){
            if( grid[i][j] == c)
                found_row = 1;
            if( grid[j][i] == c)
                found_column = 1;
            if( found_row && found_column)
                break;
        }
        if( !found_row )
            score+=1;
        if( !found_column )
            score+=1;
    }
    
    found_main_diagonal = found_sec_diagonal = 0;
    
    for( i=1; i<WIDTH; i++){
        if( grid[i][i] == c)
            found_main_diagonal = 1;
        if( grid[i][WIDTH-i] == c)
            found_sec_diagonal = 1;
        if (found_main_diagonal && found_sec_diagonal)
            break;
    }
    if( !found_main_diagonal)
        score+=1;
    if( !found_sec_diagonal)
        score+=1;
    
    
    if( turn == PLAYER)
        return -score;
    else
        return score;
}
//runs alpha-beta algorithm and return the best move
int alpha_beta_cutoff(state *s, int a, int b, int *movex, int *movey)
{
    
    if( win(s->x, s->y, s->grid) ){
        if( s->turn == AI)
            return INT_MIN;
        else
            return INT_MAX;
    }else if( s->depth == CUTOFF_DEPTH){
        return heuristic(s->turn, s->grid);
    }
    
    
    //produce all the childs
    //i could avoid doing that and produce them one by one and check the value
    
    state *head,*temp;
    
    head = generate_children(s);
    if(head == NULL){
        //        printf("No moves found.Draw.\n");
        return 0;
    }
    int alpha, beta, newScore;

    alpha=a;
    beta=b;

    if( s->turn == AI){//max layer
        for(temp = head ; temp!=NULL ; temp = temp->next){
            newScore = alpha_beta_cutoff(temp,alpha,beta,NULL,NULL);

            if( newScore > alpha){
                alpha = newScore;
                if( s->depth == 0){//record the move only in the upper level
                    /*Tha mporousa apla na pernao mia metabliti stin minimax px. return move me 1 arxika 
                     * kai 0 sta epomena epipeda anti na epibarino to state me mia epipleon metabliti*/
                    *movex = temp->x;
                    *movey = temp->y;
                }
                if( alpha >= beta){
                    free_children(head);
                    return beta;
                }
            }
        }
        free_children(head);
        return alpha;
    }else{//min layer
       for(temp = head ; temp!=NULL ; temp = temp->next){
            newScore = alpha_beta_cutoff(temp,alpha,beta,NULL,NULL);

            if( newScore < beta){
                beta = newScore;
                if( alpha >= beta){
                    free_children(head);
                    return alpha;
                }
            }
        }
        free_children(head);
        return beta;
    }
   
}

void free_children(state *head)
{
    state *temp;

    while( head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    
    return ;
}


//takes a state and produces all the children.It returns a pointer to the head of a list
state * generate_children(state *s)
{
    int i,j;
    state *head,*new;
    
    head = NULL;
    for(i=1; i<WIDTH; i++){
        for(j=1; j<WIDTH; j++){
            if( s->grid[i][j] == ' '){

                counter++;

                new = malloc(sizeof(state));
                new->x = i;
                new->y = j;
                new->turn = s->turn==PLAYER? AI : PLAYER;
                new->depth = s->depth + 1;
                new->next = NULL;

                memcpy(new->grid, s->grid,WIDTH*WIDTH*sizeof(char));
                new->grid[i][j] = s->turn == PLAYER ? 'x' : 'o';
                
                head = add_to_list(new,head);
                //              printf("I found a move!!!\n");
                
            }
        }
    }
    /*
     for( new = head; new!=NULL ; new = new->next){
     print_grid(new->grid);
     printf("\n\n");
     } 
     */
    return head;
}

//Add a new state to the head of the list
state * add_to_list(state *new,state *head)
{    
    if( head == NULL){
        return new;
    }
    new->next=head;
    return new;   
}
