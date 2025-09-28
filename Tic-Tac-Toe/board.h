#pragma once

#include "stdbool.h"

typedef struct Board Board;

enum BoardCellState {
	BOARD_CELL_EMPTY,
	BOARD_CELL_X,
	BOARD_CELL_O,
	BOARD_CELL_INVALID
};

Board *board_create(void);
void board_destroy(Board* board);
enum BoardCellState board_get_cell(const Board* const board, const int row, const int col);
// Processes a player's move. Returns true if the move was successful, false otherwise.
bool board_process_player_move(Board* const board, int row, int col, bool is_player_x);