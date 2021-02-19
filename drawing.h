#include <ncurses.h>

void calcLines(int lineCoords[], int dimLength, int dimUnits) {
	// store the onscreen coordinates of the dimUnits lines in lineCoords
	
	const int realLength = dimLength - (dimUnits - 1);
	const int minLength = realLength / dimUnits;
	const int extra = realLength % dimUnits;

	// set the minimum coordinates of the lines
	// will increase them later if neccesary
	for (int i = 0; i < dimUnits - 1; i++) {
		// add i because previous lines take up space on screen
		lineCoords[i] = minLength * (i + 1) + i;
	}

	// if the screen is not cleanly divided
	if (extra) {
		// try to spread out the remainder space
		// evenly over the grid dimensions
		for (int i = 0; i < dimUnits - 1; i++) {
			lineCoords[i] += extra * (i + 1) / dimUnits;
		}
	}
}

void initLines(Game *game) {
	int rowLines[game->rows];
	calcLines(rowLines, LINES, game->rows);
	int colLines[game->cols];
	calcLines(colLines, COLS, game->cols);

	for (int y = 0; y < game->rows - 1; y++) {
		mvhline(rowLines[y], 0, '-', COLS);
	}
	for (int x = 0; x < game->cols; x++) {
		mvvline(0, colLines[x], '|', LINES);
	}
}
