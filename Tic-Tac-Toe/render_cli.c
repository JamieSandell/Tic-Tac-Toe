#include <stdio.h>

#include "board.h"
#include "render_cli.h"

void render_board(const Board* const board)
{
	if (!board)
	{
		return;
	}

	printf(" %c | %c | %c \n", board_get_cell(board, 0, 0), board_get_cell(board, 0, 1), board_get_cell(board, 0, 2));
	printf("---+---+---\n");
	printf(" %c | %c | %c \n", board_get_cell(board, 1, 0), board_get_cell(board, 1, 1), board_get_cell(board, 1, 2));
	printf("---+---+---\n");
	printf(" %c | %c | %c \n", board_get_cell(board, 2, 0), board_get_cell(board, 2, 1), board_get_cell(board, 2, 2));
}