#pragma once

typedef struct Input
{
	int row;
	int col;
} Input;

// Gets player input from stdin in the format "row col", where row and col are integers from 0 to 2.
// Returns an Input struct with row and col set to -1 if the input is invalid.
Input get_player_input(void);