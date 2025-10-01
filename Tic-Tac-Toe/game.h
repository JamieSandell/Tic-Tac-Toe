#pragma once

#include <stdbool.h>
#include "common.h"

typedef struct GameState GameState;

GameState *game_create(void);
void game_destroy(GameState *game);
Board *game_get_board(const GameState *const game);
const char *game_get_status_message(const GameState *const game);
uint8_t game_get_move_count(const GameState *const game);
enum StatusType game_get_status_type(const GameState *const game);
bool game_is_over(const GameState *const game);
bool game_is_player_x_turn(const GameState *const game);