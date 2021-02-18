#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int counter;
void handle_winch(int sig) {
	refresh();
	clear();
	mvprintw(0, 0, "%i", ++counter);
	refresh();
}

int main(int argc, char *argv[]) {
	bool needToSeed = true; // for seeding srand()
	long int seed;
	
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
				needToSeed = false;
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
	int rows, cols;
	if (argc == 0) {
		// no dimensions supplied
		cols = rows = 4;
	}
	else if (argc == 2) {
		// both dimensions supplied
		rows = atoi(argv[optind]);
		cols = atoi(argv[optind + 1]);
		if (rows < 2 || cols < 2) {
			fprintf(stderr, "The game breaks when either dimension has a value less than 2\n");
			exit(1);
		}
	}
	else {
		printf("Usage: ./npuzzle [columns rows] [-s seed]\nseed must be a long int\n");
		exit(1);
	}
	if (needToSeed) {
		seed = time(NULL);
	}
	srand(seed);
	// ncurses initialization 
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);	
	mvprintw(0, 0, "0");
	mvprintw(1, 0, "%i %i %li", rows, cols, seed);
	while (1) {
		int c = getch();
		if (c == KEY_RESIZE) {
			handle_winch(0);
		}
		else if (c == 'q' || c == 'Q') {
			endwin();
			return 0;
		}
	}
	endwin();
}
