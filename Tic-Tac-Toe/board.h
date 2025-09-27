#pragma once

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
void board_set_cell(Board* board, int row, int col, enum BoardCellState state);