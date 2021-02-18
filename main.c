#include <stdio.h>
#include <ncurses.h>

int main() {
	// ncurses initialization 
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);	
	mvprintw(0, 0, "Hello world\n");
	getch();
	endwin();
}
