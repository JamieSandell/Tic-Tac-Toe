#include <stdlib.h>
#include "board.h"

struct Board
{
	enum BoardCellState cells[3][3];
};

enum BoardWinState board_check_win_state(const Board* const board, enum BoardPlayer last_player)
{
	if (!board)
	{
		return BOARD_WIN_STATE_INVALID_BOARD;
	}

	enum BoardCellState player_cell = last_player == BOARD_PLAYER_X ? BOARD_CELL_X : BOARD_CELL_O;
	// Check rows and columns
	for (int i = 0; i < 3; i++)
	{
		if ((board->cells[i][0] == player_cell && board->cells[i][1] == player_cell && board->cells[i][2] == player_cell) ||
			(board->cells[0][i] == player_cell && board->cells[1][i] == player_cell && board->cells[2][i] == player_cell))
		{
			return last_player == BOARD_PLAYER_X ? BOARD_WIN_STATE_X : BOARD_WIN_STATE_O;
		}
	}
	// Check diagonals
	if ((board->cells[0][0] == player_cell && board->cells[1][1] == player_cell && board->cells[2][2] == player_cell) ||
		(board->cells[0][2] == player_cell && board->cells[1][1] == player_cell && board->cells[2][0] == player_cell))
	{
		return last_player == BOARD_PLAYER_X ? BOARD_WIN_STATE_X : BOARD_WIN_STATE_O;
	}
	// Check for draw or ongoing game
	bool is_draw = true;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board->cells[i][j] == BOARD_CELL_EMPTY)
			{
				is_draw = false;
				break;
			}
		}
		if (!is_draw)
		{
			break;
		}
	}

	return is_draw ? BOARD_WIN_STATE_DRAW : BOARD_WIN_STATE_NONE;
}

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