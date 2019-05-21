#include <stdio.h>
#include "game.h"

int main()
{
    
    char grid[WIDTH][WIDTH];
    int i, j, turn;
    int moves, x, y;
    
    for( i=0; i < WIDTH ; i++){
        for( j=0; j < WIDTH ; j++){
            grid[i][j] = ' ';
        }
    }
    
    moves=0;
    turn = PLAYER;
    x=y=0;
    
    while(moves != (WIDTH-1)*(WIDTH-1)){
        if( turn == PLAYER){
            player_move(&x,&y,grid);
            turn = AI;
        }else{
            computer_move(&x,&y,grid);
            turn = PLAYER;
        }
        if( win(x,y,grid) )
            break;
        moves++;
    }
    
    if( moves == (WIDTH-1)*(WIDTH-1) )
        printf("It's a draw.\n");
    else{
        if( turn == AI)//the player played last
            printf("The player won.\n");
        else
            printf("The computer won.\n");
    }
    print_grid(grid);
 
    printf("Counter is %ld\n",counter);

    return 0;
}

//get user input from the player
void player_move(int *x, int *y, char grid[WIDTH][WIDTH])
{
    int c;
    
    print_grid(grid);
    do{
        printf("Make a move.\n");
        scanf("%d %d",x,y);
        while ( (c = getchar()) != '\n' && c != EOF ) ; //clear input
    }while( !valid_move(*x,*y,grid) );
    grid[*x][*y] = 'x';
    
    return ;
}

//decides if a move is valid
int valid_move(int x, int y, char grid[WIDTH][WIDTH])
{
    
    return grid[x][y] == ' ' && x > 0 && x < WIDTH && y > 0 && y < WIDTH;
    
}

//print the board
void print_grid(char grid[WIDTH][WIDTH])
{    
    int i,j;
    
    for( i=1; i < WIDTH ; i++){
        for( j=1; j < WIDTH ; j++){
            if( j == WIDTH - 1)
                printf("%c",grid[i][j]);
            else
                printf("%c|",grid[i][j]);
        }
        printf("\n");
        for( j=1; j < 2*WIDTH - 2 ; j++)
            printf("-");
        printf("\n");
    }
}

//calculates if the current state of the board is a win.1 if it is, 0 if not.
//To win all the cells must be the same in a row,column or in some diagonal
int win(int x, int y, char grid[WIDTH][WIDTH])
{
    int i,j;
    int same_column, same_row, same_main_diagonal, same_sec_diagonal;
    
    same_column = same_row = same_main_diagonal = same_sec_diagonal = 1;
    
    
    //check column
    for( i=1; i < WIDTH ; i++){
        if( grid[i][y] != grid[x][y]){
            same_column = 0;
            break;
        }
    }
    
    //check row
    for( j=1; j < WIDTH ; j++){
        if( grid[x][j] != grid[x][y]){
            same_row = 0;
            break;
        }
    }
    
    //check main diagonal
    if( x==y ){
        for( i=1 ; i< WIDTH ; i++){
            if( grid[i][i] != grid[x][y]){
                same_main_diagonal = 0;
                break;
            }
        }
    }else{
        same_main_diagonal = 0;
    }
    
    //check secondary diagonal
    if( x+y == WIDTH ){
        for( i=1; i<WIDTH ; i++){
            if( grid[i][WIDTH-i] != grid[x][y]){
                same_sec_diagonal = 0;
                break;
            }
        }
    }else{
        same_sec_diagonal = 0;
    }
    
    return same_column || same_row || same_main_diagonal || same_sec_diagonal;
}
