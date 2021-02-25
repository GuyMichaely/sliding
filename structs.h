#pragma once
typedef struct Game {
	int rows; // rows in the game board
	int cols; // columns in the game board
	 // index (n - 1) tells you where n is
	 // does not store index of empty tile
	int tileIndices[];
} Game;
