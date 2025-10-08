#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"

struct GameState
{
	Board *board;
	bool game_over;
	enum BoardMoveResult last_move_result;
	uint8_t move_count;
	bool is_player_x_turn;
	enum StatusType status_type;
	const char *status_message;
} GameState;

bool game_init(GameState* game_state, Board* board)
{
	GameState *game_state = malloc(sizeof(GameState));

	if (game_state == NULL || board == NULL)
	{
		free(game_state);
		free(board);
		return false;
	}

	board = board_reset(board);
	game_state->board = board;
	game_state->game_over = false;
	game_state->last_move_result = BOARD_MOVE_RESULT_OK;
	game_state->move_count = 0;
	game_state->is_player_x_turn = true;
	game_state->status_type = STATUS_TYPE_NONE;
	game_state->status_message = NULL;
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