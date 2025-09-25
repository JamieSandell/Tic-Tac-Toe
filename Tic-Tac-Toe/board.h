#pragma once

typedef struct Board Board;

Board *board_create(void);
void board_destroy(Board* board);
char board_get_cell(const Board* const board, const int row, const int col);