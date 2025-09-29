#pragma once

#include <stdbool.h>

#include "board.h"

void render_board(const Board* const board);
void render_clear_screen(void);
void render_status_message(const char* const message);
void render_player_input_prompt(bool is_player_x);