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
	calcLines(game->horizontalLines, LINES, game->rows);
	// for (int i = 0; i < game->rows - 1; i++) {
	// }
	for (int y = 0; y < game->rows - 1; y++) {
		mvhline(game->horizontalLines[y], 0, '-', COLS);
	}

	// vertical lines
	calcLines(game->verticalLines, COLS, game->cols);
	for (int x = 0; x < game->cols - 1; x++) {
		mvvline(0, game->verticalLines[x], '|', LINES);
	}

	// intersections
	for (int y = 0; y < game->rows - 1; y++) {
		for (int x = 0; x < game->cols - 1; x++) {
			mvprintw(game->horizontalLines[y], game->verticalLines[x], "+");
			getch();
		}
	}
}

// dumb simple int length function used for drawTiles
// int must be positive
int intLength(int x) {
	int length = 1;
	for (int cmp = 10; x >= cmp; cmp *= 10) {
		length++;
	}
	return length;
}

// given line coordinates and tile index, calculate midpoint
void calcBorders(int coordinates[], int index, int maxIndex, int *start, int *end, int maxCoord) {
	if (index == 0) {
		*start = 0;
		*end = coordinates[0];
	}
	else {
		*start = coordinates[index - 1];
		if (index == maxIndex) {
			*end = maxCoord;
		}
		else {
			*end = coordinates[index];
		}
	}
}

void drawTile(Game *game, int index, int tile) {
	// (y, x) index of tile
	int y = index / game->cols;
	int x = index % game->cols;

	// calculate onscreen coordinate
	// by finding midpoint between the lines
	int start, end;

	// calc y midpoint
	calcBorders(game->horizontalLines, y, game->rows - 1, &start, &end, LINES);
	int midy = (start + end) / 2;

	// calc x midpoint
	calcBorders(game->verticalLines, x, game->cols - 1, &start, &end, COLS);
	int midx = (start + end - intLength(tile)) / 2; // -intLength(tile) to center the text

	mvprintw(midy, midx, "%i", tile);
}

// draw the tiles onscreen
void drawTiles(Game *game) {
	// loop through all tile values
	// use game->tileIndices to know where to draw the tile
	for (int tile = 1; tile < game->numTiles; tile++) {
		drawTile(game, game->tileIndices[tile - 1], tile);
	}
}

void redraw(Game *game) {
	clear();
	initLines(game);
	// drawTiles(game);
	refresh();
}
