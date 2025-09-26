#include <stdlib.h>

#include "board.h"
#include "render_cli.h"

static Board* game_board = NULL;

static void initialise_game(void);
static void uninitialise_game(void);

int main(int argc, char *argv[]) {
	initialise_game();
	render_board(game_board);
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