#pragma once
typedef struct Game {
	int rows; // rows in the game board
	int cols; // columns in the game board
	int numTiles;
	int emptyy; // y index of empty tile
	int emptyx; // x index of empty til
	
	// array of tile values
	// the value at the index occupied by the empty tile is not updated
	int *tiles;

	int *verticalLines;
	int *horizontalLines;
} Game;
