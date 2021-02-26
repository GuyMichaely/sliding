#pragma once
typedef struct Game {
	int rows; // rows in the game board
	int cols; // columns in the game board
	int numTiles;
	int emptyy; // y index of empty tile
	int emptyx; // x index of empty til
	int *tiles; // array of tile values
	int *verticalLines;
	int *horizontalLines;
} Game;
