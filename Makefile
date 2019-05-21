CC = gcc
CFLAGS = -Wall

minimax: game.o minimax.o
	$(CC) $(CFLAGS) game.o  minimax.o -o minimax

alpha-beta: game.o alpha-beta.o
	$(CC) $(CFLAGS) game.o  alpha-beta.o -o alpha-beta

alpha-beta-cutoff: game.o alpha-beta-cutoff.o
	$(CC) $(CFLAGS) game.o  alpha-beta-cutoff.o -o alpha-beta-cutoff

clean:
	rm -f minimax alpha-beta alpha-beta-cutoff
	rm *.o
