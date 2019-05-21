# AI for tic-tac-toe  

In this repo I have implemented minimax, alpha-beta, alpha-beta cutoff with heuristics for the game of tic-tac-toe.    
The AI (hopefully) never loses but it also doesn't always make the most challenging moves.    
Alpha-beta is not really needed for the simple game but if you increase the size of the grid, then it becomes useful.    
Alpha-beta cutoff explores until max depth and then uses a heuristic to evaluate the position.  
Each algorithm is implemented in each own file and defines a computer_move() function which is used by game.c to play the game.   

Tic.c is a standalone file to run a game using minimax.  
Check makefile on how to run

--------------------

The game state is a struct that contains:    
1. the board at the current state  
2. the move that will be played(and initially the last move played)  
3. who plays next(Player or AI)  
4. the depth of the state in the game tree  
5. and a pointer to the next gamestate  

Every state generates all it’s children and then the algorithm traverses them.  

TODO:  
- Implement monte carlo tree search
- Randomize the list of the children because right now the AI plays the first not loosing move it finds
- Make more challenging and promising moves. For example play the move that leads to most wins in the game tree.
