#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimax.h"
#include "game.h"

long int counter = 0;

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

    printf("minimax:%d\n",minimax(s,x,y));
    
    printf("\nComputer move is %d %d\n",*x,*y);
    
    grid[*x][*y]='o';
    
    free(s);
    return ;
}

//runs minimax algorithm and return the best move
int minimax(state *s,int *movex,int *movey)
{
    
    if( win(s->x, s->y, s->grid) ){
        if( s->turn == AI)
            return -1;
        else
            return 1;
    }
    
    
    //produce all the childs
    //I could avoid doing that and produce them one by one and check the value
    
    state *head,*temp;
    
    head = generate_children(s);
    if(head == NULL){
        //        printf("No moves found.Draw.\n");
        return 0;
    }
    
    int score = s->turn == PLAYER? 2 : -2;//set the initial score to +-infinity
    int newScore;
    for(temp = head ; temp!=NULL ; temp = temp->next){
        newScore = minimax(temp,NULL,NULL);

        if( s->turn == AI){//max layer
            if( newScore > score){
                score = newScore;
                if( s->depth == 0){//record the move only in the upper level
                    *movex = temp->x;
                    *movey = temp->y;
                }
            }
        }else{ //min layer
            if(newScore < score){
                score = newScore;
            }
        }
    }
    
    free_children(head);

    return score;
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
