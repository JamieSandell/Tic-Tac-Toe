#include <stdlib.h>
#include "board.h"

struct Board {
	enum BoardCell cells[3][3];
};

Board *board_create(void) {
	Board *board = (Board *)malloc(sizeof(Board));

	if (board)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board->cells[i][j] = BOARD_CELL_EMPTY;
			}
		}
	}
	return board;
}

void board_destroy(Board* board) {
	free(board);
}

enum BoardCell board_get_cell(const Board* const board, const int row, const int col) {
	if (!board || row < 0 || row >= 3 || col < 0 || col >= 3)
	{
		return BOARD_CELL_INVALID;
	}

	return board->cells[row][col];
}

void board_set_cell(Board* board, int row, int col, char ch) {
	if (!board || row < 0 || row >= 3 || col < 0 || col >= 3)
	{
		return;
	}

	board->cells[row][col] = ch;
}