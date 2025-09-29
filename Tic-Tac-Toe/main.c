#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "input.h"
#include "render_cli.h"

static Board* game_board = NULL;
static bool game_over = false;
static bool is_player_x_turn = true;

static void initialise_game(void);
static void uninitialise_game(void);

int main(int argc, char *argv[]) {
	enum BoardMoveResult last_move_result = BOARD_MOVE_RESULT_OK;

	initialise_game();

	while (!game_over)
	{
		render_clear_screen();
		render_board(game_board);

		if (last_move_result != BOARD_MOVE_RESULT_OK)
		{
			switch (last_move_result)
			{
				case BOARD_MOVE_RESULT_OUT_OF_BOUNDS:
				{
					render_status_message("Move is out of bounds. Please enter row and column between 0 and 2.");
					break;
				}
				case BOARD_MOVE_RESULT_CELL_OCCUPIED:
				{
					render_status_message("Cell is already occupied. Please choose another cell.");
					break;
				}
				case BOARD_MOVE_RESULT_INVALID_BOARD:
				{
					render_status_message("Internal error: Invalid board state.");
					game_over = true;
					break;
				}
				case BOARD_MOVE_RESULT_OK:
				default:
				{
					// Should never happen.
					break;
				}
			}
		}

		render_player_input_prompt(is_player_x_turn);

		Input input = get_player_input();
		last_move_result = board_process_player_move(game_board, input.row, input.col, is_player_x_turn);

		if (last_move_result == BOARD_MOVE_RESULT_OK)
		{
			is_player_x_turn = !is_player_x_turn;
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