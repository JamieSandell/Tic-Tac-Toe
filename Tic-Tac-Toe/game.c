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

GameState *game_create(void)
{
	GameState *game = malloc(sizeof(GameState));

	if (game == NULL)
	{
		return NULL;
	}

	game->board = board_create();

	if (game->board == NULL)
	{
		free(game);
		return NULL;
	}

	game->game_over = false;
	game->last_move_result = BOARD_MOVE_RESULT_OK;
	game->move_count = 0;
	game->is_player_x_turn = true;
	game->status_type = STATUS_TYPE_NONE;
	game->status_message = NULL;
	return game;
}

void game_destroy(GameState *game)
{
	if (game == NULL)
	{
		return;
	}

	if (game->board != NULL)
	{
		board_destroy(game->board);
	}

	free(game);
}

Board *game_get_board(const GameState *const game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return game->board;
}

const char *game_get_status_message(const GameState *const game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return game->status_message;
}

uint8_t game_get_move_count(const GameState *const game)
{
	if (game == NULL)
	{
		return 0;
	}

	return game->move_count;
}

enum StatusType game_get_status_type(const GameState *const game)
{
	if (game == NULL)
	{
		return STATUS_TYPE_ERROR;
	}

	return game->status_type;
}

bool game_is_over(const GameState *const game)
{
	if (game == NULL)
	{
		return true;
	}

	return game->game_over;
}

bool game_is_player_x_turn(const GameState *const game)
{
	if (game == NULL)
	{
		return false;
	}

	return game->is_player_x_turn;
}