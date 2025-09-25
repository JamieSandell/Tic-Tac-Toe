#include <stdlib.h>
#include "board.h"

struct Board {
	char cells[3][3];
};

Board *board_create(void) {
	Board *board = (Board *)malloc(sizeof(Board));

	if (board)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				board->cells[i][j] = ' ';
			}
		}
	}
	return board;
}

void board_destroy(Board* board) {
	free(board);
}

char board_get_cell(const Board* const board, const int row, const int col) {
	if (!board || row < 0 || row >= 3 || col < 0 || col >= 3)
	{
		return '\0';
	}

	return board->cells[row][col];
}