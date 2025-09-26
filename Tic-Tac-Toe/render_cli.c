#include <stdio.h>

#include "board.h"
#include "render_cli.h"

void render_board(const Board* const board)
{
	if (!board)
	{
		return;
	}

	//printf(" %c | %c | %c \n", board_get_cell(board, 0, 0), board_get_cell(board, 0, 1), board_get_cell(board, 0, 2));
	//printf("---+---+---\n");
	//printf(" %c | %c | %c \n", board_get_cell(board, 1, 0), board_get_cell(board, 1, 1), board_get_cell(board, 1, 2));
	//printf("---+---+---\n");
	//printf(" %c | %c | %c \n", board_get_cell(board, 2, 0), board_get_cell(board, 2, 1), board_get_cell(board, 2, 2));

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			putchar(' ');
			render_board_cell(board_get_cell(board, row, col));
			putchar(' ');

			if (col < 2)
			{
				putchar('|');
			}
		}
		putchar('\n');

		if (row < 2)
		{
			printf("---+---+---\n");
		}
	}
}

void render_board_cell(enum BoardCell board_cell)
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