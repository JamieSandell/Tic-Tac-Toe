#pragma once

#include <stdbool.h>

#include "board.h"

void render_board(const Board* const board);
void render_clear_screen(void);
void render_player_input_prompt(bool is_player_x);

static char render_board_cell(enum BoardCellState board_cell);