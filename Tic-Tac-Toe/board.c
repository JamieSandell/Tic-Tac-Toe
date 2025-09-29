#include <stdlib.h>
#include "board.h"

struct Board
{
	enum BoardCellState cells[3][3];
};

Board *board_create(void)
{
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

void board_destroy(Board* board)
{
	free(board);
}

enum BoardCellState board_get_cell(const Board* const board, const int row, const int col)
{
	if (!board || row < 0 || row >= 3 || col < 0 || col >= 3)
	{
		return BOARD_CELL_INVALID;
	}

	return board->cells[row][col];
}

enum BoardMoveResult board_process_player_move(Board* const board, int row, int col, enum BoardPlayer player)
{
	if (!board)
	{
		return BOARD_MOVE_RESULT_INVALID_BOARD;
	}

	switch (board_get_cell(board, row, col))
	{
		case BOARD_CELL_X:
		case BOARD_CELL_O:
		{
			return BOARD_MOVE_RESULT_CELL_OCCUPIED;
		}
		case BOARD_CELL_EMPTY:
		{
			break;
		}
		case BOARD_CELL_INVALID:
		default:
		{
			return BOARD_MOVE_RESULT_OUT_OF_BOUNDS;
		}
	}

	board->cells[row][col] = player == BOARD_PLAYER_X ? BOARD_CELL_X : BOARD_CELL_O;
	return BOARD_MOVE_RESULT_OK;
}