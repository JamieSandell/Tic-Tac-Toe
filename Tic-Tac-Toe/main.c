#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "input.h"
#include "render_cli.h"

static Board* game_board = NULL;
static bool game_over = false;
static Input input;
static bool is_player_x_turn = true;

static void initialise_game(void);
static void uninitialise_game(void);

int main(int argc, char *argv[]) {
	initialise_game();

	while (!game_over)
	{
		render_clear_screen();
		render_board(game_board);
		render_player_input_prompt(is_player_x_turn);

		input = get_player_input();
		board_process_player_move(game_board, input.row, input.col, is_player_x_turn);

		is_player_x_turn = !is_player_x_turn;
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