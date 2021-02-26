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
	// game data initiazlization
	game->numTiles = game->rows * game->cols;
	int tileIndices[game->numTiles - 1]; // subtract 1 for not storing index of 0
	game->tileIndices = tileIndices;
	for (int i = 0; i < game->numTiles; i++) {
		game->tileIndices[i - 1] = i;
	}

	// fuck malloc, all my homies use VLAs
	/* int verticalLines[game->cols - 1]; */
	/* game->verticalLines = verticalLines; */
	/* int horizontalLines[game->rows - 1]; */
	/* game->horizontalLines = horizontalLines; */
	game->verticalLines = malloc(sizeof(int) * game->rows - 1);
	game->verticalLines = malloc(sizeof(int) * game->rows - 1);
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
	keypad(stdscr, TRUE);	

	// init game data and draw screen for the first time
	gameInit(&game);
	redraw(&game);

	while (1) {
		int c = getch();
		if (c == KEY_RESIZE) {
			redraw(&game);
		}
		else if (c == 'q' || c == 'Q') {
			endwin();
			return 0;
		}
	}
	endwin();
}
