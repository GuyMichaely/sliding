#include <ncurses.h>

void calcLines(int lineCoords[], int dimLength, int dimUnits) {
	// store the onscreen coordinates of the dimUnits lines in lineCoords
	
	const int realLength = dimLength - (dimUnits - 1);
	const int minLength = realLength / dimUnits;
	const int remainder = realLength % dimUnits;

	// set the minimum coordinates of the lines
	// will increase them later if neccesary
	for (int i = 0; i < dimUnits - 1; i++) {
		// total extra to add to the line
		// to intersperse the leftover evenly
		const int extra = remainder * (i + 1) / dimUnits;
		// add i because previous lines take up space on screen
		lineCoords[i] = minLength * (i + 1) + i + extra;
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
	for (int y = 0; y < game->rows - 1; y++) {
		for (int x = 0; x < game->cols - 1; x++) {
			mvprintw(rowLines[y], colLines[x], "+");
		}
	}
}
