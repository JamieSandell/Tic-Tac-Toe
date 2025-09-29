#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "common.h"
#include "input.h"
#include "render_cli.h"

static Board* game_board = NULL;
static bool game_over = false;
static bool is_player_x_turn = true;

static void initialise_game(void);
static void uninitialise_game(void);

int main(int argc, char *argv[]) {
	enum BoardMoveResult last_move_result = BOARD_MOVE_RESULT_OK;
	enum StatusType status_type = STATUS_TYPE_NONE;
	const char* status_message = NULL;

	initialise_game();

	while (!game_over)
	{
		render_clear_screen();
		render_board(game_board);

		if (status_type != STATUS_TYPE_NONE && status_message != NULL)
		{
			render_status_message(status_type, status_message);
		}

		render_player_input_prompt(is_player_x_turn);

		Input input;
		enum InputResult input_result = get_player_input(&input);

		switch(input_result)
		{
			case INPUT_RESULT_OK:
			{
				last_move_result = board_process_player_move(game_board, input.row, input.col, is_player_x_turn ? BOARD_PLAYER_X : BOARD_PLAYER_O);

				switch(last_move_result)
				{
					case BOARD_MOVE_RESULT_OK:
					{
						status_type = STATUS_TYPE_NONE;
						status_message = NULL;
						is_player_x_turn = !is_player_x_turn;
						break;
					}
					case BOARD_MOVE_RESULT_OUT_OF_BOUNDS:
					{
						status_type = STATUS_TYPE_WARNING;
						status_message = "Out of range (0-2). Try again.";
						break;
					}
					case BOARD_MOVE_RESULT_CELL_OCCUPIED:
					{
						status_type = STATUS_TYPE_WARNING;
						status_message = "That square is taken. Pick another.";
						break;
					}
					case BOARD_MOVE_RESULT_INVALID_BOARD:
					{
						status_type = STATUS_TYPE_ERROR;
						status_message = "Internal error: invalid board. Exiting.";
						game_over = true;
						break;
					}
					default:
					{
						// Should never happen.
						status_type = STATUS_TYPE_ERROR;
						status_message = "Internal error: Unknown board move result.";
						game_over = true;
						break;
					}
				}

				break;
			}
			case INPUT_RESULT_EOF:
			{
				render_status_message(STATUS_TYPE_INFO, "End of input detected. Exiting game.");
				game_over = true;
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
				game_over = true;
				break;
			}
			default:
			{
				// Should never happen.
				render_status_message(STATUS_TYPE_ERROR, "Internal error: Unknown input result.");
				game_over = true;
				break;
			}
		}
	}	

	uninitialise_game();
	return EXIT_SUCCESS;
}

static void initialise_game(void)
{
	game_board = board_create();

	if (!game_board)
	{
		exit(EXIT_FAILURE);
	}
}

static void uninitialise_game(void)
{
	board_destroy(game_board);
	game_board = NULL;
}