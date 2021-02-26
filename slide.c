#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "structs.h"
#include "drawing.h"

// initialize game struct
void gameInit(Game *game) {
	game->emptyy = game->emptyx = 0;
	game->numTiles = game->rows * game->cols;
	/* int tileIndices[game->numTiles - 1]; // subtract 1 for not storing index of 0 */
	game->tiles = malloc(sizeof(int) * game->numTiles);
	for (int i = 1; i < game->numTiles; i++) {
		game->tiles[i] = i;
	}

	/* int verticalLines[game->cols - 1]; */
	/* game->verticalLines = verticalLines; */
	/* int horizontalLines[game->rows - 1]; */
	/* game->horizontalLines = horizontalLines; */
	game->verticalLines = malloc(sizeof(int) * game->rows - 1);
	game->horizontalLines = malloc(sizeof(int) * game->cols - 1);
}

// determine what direction an input char c is
bool isQuit(int c) {
	return c == 'q' || c == 'Q';
}
bool isLeft(int c) {
	return c == 'h' || c == 'H' || c == KEY_LEFT;
}
bool isDown(int c) {
	return c == 'j' || c == 'J' || c == KEY_DOWN;
}
bool isUp(int c) {
	return c == 'k' || c == 'K' || c == KEY_UP;
}
bool isRight(int c) {
	return c == 'l' || c == 'L' || c == KEY_RIGHT;
}

// attempt to move a tile in to the empty space by (dy, dx)
// is designed to only accept (-1, 0), (1, 0), (0, 1), (0, -1)
void moveTile(Game *game, int dy, int dx) {
	// if movement would result in out of bounds
	if (game->emptyy - dy < 0 || game->emptyy - dy >= game->rows){
		return;
	}
	if (game->emptyx - dx < 0 || game->emptyx - dx >= game->cols){
		return;
	}
	
	const int emptyIndex = game->emptyy * game->rows + game->emptyx;
	game->tiles[emptyIndex] = game->tiles[(game->emptyy - dy) * game->rows + (game->emptyx - dx)];
	game->emptyy -= dy;
	game->emptyx -= dx;
}

int main(int argc, char *argv[]) {
	long int seed = 0;
	
	// cmd line parsing
	opterr = 0;
	int c;
	while ((c = getopt(argc, argv, "s:")) != -1) {
		// optional argument s to supply seed for srand
		if (c == -1) {
			break;
		}
		switch (c) {
			case 's':
				seed = atol(optarg);
				break;
			case ':':
				fprintf(stderr, "Seed option must take value\n");
				exit(1);
			case '?':
				fprintf(stderr, "Unknown option %c\n", optopt);
				exit(1);
		}
	}
	// can supply either both dimension arguments or none
	// dimensions must both be >= 2
	argc -= optind;
	Game game;
	if (argc == 0) {
		// no dimensions supplied
		game.cols = game.rows = 4;
	}
	else if (argc == 2) {
		// both dimensions supplied
		game.rows = atoi(argv[optind]);
		game.cols = atoi(argv[optind + 1]);
		if (game.rows < 2 || game.cols < 2) {
			fprintf(stderr, "The game breaks when either dimension has a value less than 2\n");
			exit(1);
		}
	}
	else {
		// bad arguments supplied
		printf("Usage: ./npuzzle [columns rows] [-s seed]\nseed must be a long int\n");
		exit(1);
	}
	if (seed == 0) {
		seed = time(NULL);
	}
	srand(seed);
	
	// ncurses initialization 
	initscr();
	noecho();
	raw();
	curs_set(0);
	keypad(stdscr, TRUE);	

	// init game data and draw screen for the first time
	gameInit(&game);
	redraw(&game);

	while (!isQuit(c = getch())) {
		if (c == KEY_RESIZE) {
			redraw(&game);
		}
		else if (isLeft(c)) {
			moveTile(&game, 0, -1);
		}
		else if (isDown(c)) {
			moveTile(&game, 1, 0);
		}
		else if (isUp(c)) {
			moveTile(&game, -1, 0);
		}
		else if (isRight(c)) {
			moveTile(&game, 0, 1);
		}

		redraw(&game);
	}
	endwin();
	return 0;
}
