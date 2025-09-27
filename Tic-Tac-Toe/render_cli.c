#include <stdio.h>

#include "board.h"
#include "render_cli.h"

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
		printf("%d | ", r);

		for (int c = 0; c < 3; ++c)
		{
			render_board_cell(board_get_cell(board, r, c));

			if (c < 2)
			{
				printf(" | ");
			}
			else
			{
				printf(" |");
			}
		}

		putchar('\n');
		puts("   -------------");
	}
}

void render_board_cell(enum BoardCellState board_cell)
{
	switch (board_cell)
	{
		case BOARD_CELL_EMPTY:
		{
			putchar('.');
			break;
		}
		case BOARD_CELL_X:
		{
			putchar('X');
			break;
		}
		case BOARD_CELL_O:
		{
			putchar('O');
			break;
		}
		default:
		{
			putchar('?');
			break;
		}
	}
}