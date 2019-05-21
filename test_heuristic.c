#include <stdio.h>

#define WIDTH 6
#define PLAYER 1
#define AI 0

int heuristic(int turn, char grid[WIDTH][WIDTH]);

int main(){
    
    char grid[WIDTH][WIDTH]={
        {'q','q','q','q','q','q'},
        {'q',' ',' ','x',' ',' '},
        {'q','o','x',' ',' ','o'},
        {'q','x',' ',' ',' ',' '},
        {'q','x',' ',' ','o',' '},
        {'q','x',' ',' ',' ',' '},
    };
    
    printf("Heuristic is: %d\n",heuristic(PLAYER,grid));
    
    
    return 0;
}


int heuristic(int turn, char grid[WIDTH][WIDTH])
{
    int i,j,score,found_row,found_column,found_main_diagonal,found_sec_diagonal;
    char c;
    
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
