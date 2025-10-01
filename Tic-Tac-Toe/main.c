#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "common.h"
#include "input.h"
#include "render_cli.h"

typedef struct GameState
{
	Board *board;
	bool game_over;
	enum BoardMoveResult last_move_result;
	uint8_t move_count;
	bool is_player_x_turn;
	enum StatusType status_type;
	const char *status_message;
} GameState;

static GameState game_state = { 0 };

static void end_game_with_message(enum StatusType type, const char *const message);
static void initialise_game(void);
static void uninitialise_game(void);

int main(int argc, char *argv[])
{
	initialise_game();

	while (!game_state.game_over)
	{
		render_clear_screen();
		render_board(game_state.board);

		if (game_state.status_type != STATUS_TYPE_NONE && game_state.status_message != NULL)
		{
			render_status_message(game_state.status_type, game_state.status_message);
		}

		render_player_input_prompt(game_state.is_player_x_turn);
		fflush(stdout);

		Input input;
		enum InputResult input_result = get_move_input(&input);

		switch(input_result)
		{
			case INPUT_RESULT_OK:
			{
				enum BoardMoveResult last_move_result = board_process_player_move(game_state.board, input.row, input.col, game_state.is_player_x_turn ? BOARD_PLAYER_X : BOARD_PLAYER_O);

				switch(last_move_result)
				{
					case BOARD_MOVE_RESULT_OK:
					{
						game_state.status_type = STATUS_TYPE_NONE;
						game_state.status_message = NULL;
						enum BoardPlayer last_player = game_state.is_player_x_turn ? BOARD_PLAYER_X : BOARD_PLAYER_O;						
						++game_state.move_count;
						enum BoardWinState win_state = board_check_win_state(game_state.board, last_player);

						switch(win_state)
						{
							case BOARD_WIN_STATE_NONE:
							{
								game_state.is_player_x_turn = !game_state.is_player_x_turn;
								break;
							}
							case BOARD_WIN_STATE_X:
							{
								end_game_with_message(STATUS_TYPE_INFO, "Player X wins! Congratulations!");
								break;
							}
							case BOARD_WIN_STATE_O:
							{
								end_game_with_message(STATUS_TYPE_INFO, "Player O wins! Congratulations!");
								break;
							}
							case BOARD_WIN_STATE_DRAW:
							{
								end_game_with_message(STATUS_TYPE_INFO, "It's a draw! Well played both!");
								break;
							}
							case BOARD_WIN_STATE_INVALID_BOARD:
							{
								end_game_with_message(STATUS_TYPE_ERROR, "Internal error: invalid board state. Exiting.");
								break;
							}
							default:
							{
								// Should never happen.
								end_game_with_message(STATUS_TYPE_ERROR, "Internal error: Unknown board win state. Exiting.");
								break;
							}
						}

						break;
					}
					case BOARD_MOVE_RESULT_OUT_OF_BOUNDS:
					{
						game_state.status_type = STATUS_TYPE_WARNING;
						game_state.status_message = "Out of range (0-2). Try again.";
						break;
					}
					case BOARD_MOVE_RESULT_CELL_OCCUPIED:
					{
						game_state.status_type = STATUS_TYPE_WARNING;
						game_state.status_message = "That square is taken. Pick another.";
						break;
					}
					case BOARD_MOVE_RESULT_INVALID_BOARD:
					{
						end_game_with_message(STATUS_TYPE_ERROR, "Internal error: invalid board state. Exiting.");
						break;
					}
					default:
					{
						// Should never happen.
						end_game_with_message(STATUS_TYPE_ERROR, "Internal error: Unknown board move result. Exiting.");
						break;
					}
				}

				break;
			}
			case INPUT_RESULT_EOF:
			{
				end_game_with_message(STATUS_TYPE_INFO, "End of input detected. Exiting game.");
				break;
			}
			case INPUT_RESULT_ERROR:
			{
				render_status_message(STATUS_TYPE_ERROR, "Error reading input. Please try again.");
				break;
			}
			case INPUT_RESULT_INVALID:
			{
				render_status_message(STATUS_TYPE_WARNING, "Enter two numbers: row col (0–2). Example: 1 2.");
				break;
			}
			case INPUT_RESULT_NULL_POINTER:
			{
				render_status_message(STATUS_TYPE_ERROR, "Internal error: Null pointer passed to input function.");
				game_state.game_over = true;
				break;
			}
			default:
			{
				// Should never happen.
				render_status_message(STATUS_TYPE_ERROR, "Internal error: Unknown input result.");
				game_state.game_over = true;
				break;
			}
		}
	}

	render_message("Thank you for playing Tic-Tac-Toe!");
	render_message("Would you like to play again? (y/n): ");
	get_yes_no_input(NULL);

	uninitialise_game();
	return EXIT_SUCCESS;
}

static void end_game_with_message(enum StatusType type, const char *const message)
{
	render_clear_screen();
	render_board(game_state.board);
	render_status_message(type, message);
	game_state.game_over = true;
}

static void initialise_game(void)
{
	game_state.board = board_create();
	game_state.game_over = false;
	game_state.last_move_result = BOARD_MOVE_RESULT_OK;
	game_state.move_count = 0;
	game_state.is_player_x_turn = true;
	game_state.status_type = STATUS_TYPE_NONE;
	game_state.status_message = NULL;

	if (!game_state.board)
	{
		exit(EXIT_FAILURE);
	}
}

static void uninitialise_game(void)
{
	board_destroy(game_state.board);
	game_state.board = NULL;
}