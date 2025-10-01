#pragma once

#include <stdbool.h>

typedef struct Board Board;

enum BoardCellState {
	BOARD_CELL_EMPTY,
	BOARD_CELL_X,
	BOARD_CELL_O,
	BOARD_CELL_INVALID
};

enum BoardMoveResult
{
	BOARD_MOVE_RESULT_OK,
	BOARD_MOVE_RESULT_OUT_OF_BOUNDS,
	BOARD_MOVE_RESULT_CELL_OCCUPIED,
	BOARD_MOVE_RESULT_INVALID_BOARD
};

enum BoardPlayer
{
	BOARD_PLAYER_X,
	BOARD_PLAYER_O
};

enum BoardWinState
{
	BOARD_WIN_STATE_NONE,
	BOARD_WIN_STATE_X,
	BOARD_WIN_STATE_O,
	BOARD_WIN_STATE_DRAW,
	BOARD_WIN_STATE_INVALID_BOARD
};

enum BoardWinState board_check_win_state(const Board *const board, enum BoardPlayer last_player);
Board *board_create(void);
void board_destroy(Board *board);
enum BoardCellState board_get_cell(const Board *const board, const int row, const int col);
enum BoardMoveResult board_process_player_move(Board *const board, int row, int col, enum BoardPlayer player);