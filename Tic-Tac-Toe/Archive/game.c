#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"

struct Game
{
	Board *board;
	bool game_over;
	enum BoardMoveResult last_move_result;
	uint8_t move_count;
	bool is_player_x_turn;
	enum StatusType status_type;
	const char *status_message;
} Game;

bool game_create(Game *game)
{
	Game *game = malloc(sizeof(Game));

	if (game == NULL)
	{
		return false;
	}

	game->board = board_create();
	game->game_over = false;
	game->last_move_result = BOARD_MOVE_RESULT_OK;
	game->move_count = 0;
	game->is_player_x_turn = true;
	game->status_type = STATUS_TYPE_NONE;
	game->status_message = NULL;
	return true;
}

void game_destroy(GameState *game_state)
{
	if (game_state == NULL)
	{
		return;
	}

	if (game_state->board != NULL)
	{
		board_destroy(game_state->board);
	}

	free(game_state);
}

Board *game_get_board(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return NULL;
	}

	return game_state->board;
}

const char *game_get_status_message(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return NULL;
	}
	return game_state->status_message;
}

uint8_t game_get_move_count(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return 0;
	}

	return game_state->move_count;
}

enum StatusType game_get_status_type(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return STATUS_TYPE_ERROR;
	}

	return game_state->status_type;
}

bool game_is_over(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return true;
	}

	return game_state->game_over;
}

bool game_is_player_x_turn(const GameState *const game_state)
{
	if (game_state == NULL)
	{
		return false;
	}

	return game_state->is_player_x_turn;
}