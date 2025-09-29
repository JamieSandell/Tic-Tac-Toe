#pragma once

enum InputResult
{
	INPUT_RESULT_OK,
	INPUT_RESULT_ERROR, // error reading input
	INPUT_RESULT_EOF, // end of file reached, treated seperately from error
	INPUT_RESULT_INVALID, // successfully read but invalid input
	INPUT_RESULT_NULL_POINTER // null pointer passed to function
};

typedef struct Input
{
	int row;
	int col;
} Input;

// Gets player input from stdin in the format "row col".
// Format only; range validated by board.
// out_input must not be NULL.
// Returns the input via the out_input parameter.
// Returns INPUT_RESULT_OK on success, or an appropriate error code on failure.
enum InputResult get_player_input(Input* const out_input);