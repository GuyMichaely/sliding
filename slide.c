#include <stdio.h>
#include <ncurses.h>

int counter;

void handle_winch(int sig) {
	refresh();
	clear();
	mvprintw(0, 0, "%i", ++counter);
	refresh();
}

int main() {
	// ncurses initialization 
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);	
	mvprintw(0, 0, "0");
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
