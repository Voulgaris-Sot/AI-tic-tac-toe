#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 4
#define PLAYER 1
#define AI 0

struct state{
    char grid[WIDTH][WIDTH];
    int x,y;
    int turn;
    int depth;

    struct state *next;
};

typedef struct state state;
 
void print_grid(char grid[WIDTH][WIDTH]){
    
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

int valid_move(int x, int y, char grid[WIDTH][WIDTH]){

    return x > 0 && x < WIDTH && y > 0 && y < WIDTH && grid[x][y] == ' ';

}

state * add_to_list(state *new,state *head){

    if( head == NULL){
        return new;
    }
    new->next=head;
    return new;

}

state * generate_children(state *s)
{
    int i,j;
    state *head,*new;

    head = NULL;
    for(i=1; i<WIDTH; i++){
        for(j=1; j<WIDTH; j++){
            if( s->grid[i][j] == ' '){
                new = malloc(sizeof(state));
                new->x = i;
                new->y = j;
                new->turn = s->turn==PLAYER? AI : PLAYER;
                new->depth = s->depth + 1;

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
    
    state *head,*temp,*bestMove;

    head = generate_children(s);
    if(head == NULL){
//        printf("No moves found.Draw.\n");
        return 0;
    }
    int score = s->turn == PLAYER? 2 : -2;
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
                bestMove = temp;
                score = newScore;
            }

        }
    }

    return score;

}

void computer_move(int *x, int *y, char grid[WIDTH][WIDTH])
{
    state *s = malloc(1*sizeof(state));
    memcpy(s->grid,grid,WIDTH*WIDTH*sizeof(char));
    s->x = *x;
    s->y = *y;
    s->turn = AI;
    s->depth = 0;//0 or 1?? 
    
    printf("miniman:%d\n",minimax(s,x,y));

    printf("\nComputer move is %d %d\n",*x,*y); 

    grid[*x][*y]='o';

    return ;
}

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

    return 0;
}
