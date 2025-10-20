#pragma once

#include <stdbool.h>
#include "common.h"

enum GameOutcome
{
	GAME_OUTCOME_NONE,
	GAME_OUTCOME_X_WINS,
	GAME_OUTCOME_O_WINS,
	GAME_OUTCOME_DRAW,
	GAME_OUTCOME_ERROR
};

typedef struct Game Game;

typedef struct GameStepResult
{
	// High level verdicts for the UI/tests:
	bool terminal; // game ended this step?
	enum GameOutcome outcome;

	// Useful for tests/loop logic:
	bool board_changed; // a valid move altered the board?
	bool turn_changed; // turn flipped?
	
	// Status banner for the UI:
	enum StatusType status_type; // NONE, INFO, WARNING, ERROR
	const char* status_message; // owned by game layer (static strings)
	
	// Low level results for debugging/logging/tests:
	enum InputResult input_result;
	enum BoardMoveResult move_result;
	enum BoardWinState win_state;
} GameStepResult;


// API

bool game_create(GameState *game_state);
bool game_is_over(const GameState *const game_state);
GameStepResult game_step(GameState *game_state, enum InputResult input_result, const Input *input);

void game_destroy(GameState *game);
Board *game_get_board(const GameState *const game);
const char *game_get_status_message(const GameState *const game);
uint8_t game_get_move_count(const GameState *const game);
enum StatusType game_get_status_type(const GameState *const game);
bool game_is_player_x_turn(const GameState *const game);