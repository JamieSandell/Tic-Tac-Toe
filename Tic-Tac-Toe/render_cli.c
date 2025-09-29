#include <stdio.h>

#include "board.h"
#include "render_cli.h"

static char render_board_cell(enum BoardCellState board_cell);

static char render_board_cell(enum BoardCellState board_cell)
{
	char ch;

	switch (board_cell)
	{
	case BOARD_CELL_EMPTY:
	{
		ch = '.';
		break;
	}
	case BOARD_CELL_X:
	{
		ch = 'X';
		break;
	}
	case BOARD_CELL_O:
	{
		ch = 'O';
		break;
	}
	default:
	{
		ch = '?';
		break;
	}
	}

	return ch;
}

void render_board(const Board* const board)
{
	if (!board)
	{
		return;
	}

	puts("     0   1   2");
	puts("   -------------");

	for (int r = 0; r < 3; ++r)
	{
		printf(" %d | ", r);

		for (int c = 0; c < 3; ++c)
		{
			putchar(render_board_cell(board_get_cell(board, r, c)));
			printf(c < 2 ? " | " : " |");
		}

		putchar('\n');
		puts("   -------------");
	}
}

void render_clear_screen(void)
{
	puts("\033[H\033[J");
}

void render_status_message(const char* const message)
{
	if (message)
	{
		printf("Invalid input: %s\n", message);
	}
	else
	{
		puts("Invalid input.");
	}
}

void render_player_input_prompt(bool is_player_x)
{
	printf("Player %c, enter your move (row and column between 0 an 2): ", is_player_x ? 'X' : 'O');
}