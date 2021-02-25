#include <ncurses.h>

// calculate the onscreen coordinates of the line seperators
// and store in calcLines
// dimLength is the real length of the dimension (i.e. height or width)
// dimUnits is the number of tiles in the dimension (e.g. dimUnits = 4 for a 4x4)
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

// draw the tile seperation lines onscreen
void initLines(Game *game) {
	// horizontal lines
	int rowLines[game->rows];
	calcLines(rowLines, LINES, game->rows);
	for (int y = 0; y < game->rows - 1; y++) {
		mvhline(rowLines[y], 0, '-', COLS);
	}

	// vertical lines
	int colLines[game->cols];
	calcLines(colLines, COLS, game->cols);
	for (int x = 0; x < game->cols; x++) {
		mvvline(0, colLines[x], '|', LINES);
	}

	// intersections
	for (int y = 0; y < game->rows - 1; y++) {
		for (int x = 0; x < game->cols - 1; x++) {
			mvprintw(rowLines[y], colLines[x], "+");
		}
	}
}
