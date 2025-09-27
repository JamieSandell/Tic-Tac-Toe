#pragma once

#include "board.h"

void render_board(const Board* const board);

static char render_board_cell(enum BoardCellState board_cell);