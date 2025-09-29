#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // doing the safe pattern (fgets -> parse), so sscanf here is perfectly reasonable.
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "input.h"

#define MAX_INPUT_LENGTH 100

enum InputResult get_player_input(Input* const out_input)
{
	if (out_input == NULL)
	{
		return INPUT_RESULT_NULL_POINTER;
	}

	char buffer[MAX_INPUT_LENGTH];

	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
		if (feof(stdin))
		{
			return INPUT_RESULT_EOF;
		}
		
		if(ferror(stdin))
		{
			return INPUT_RESULT_ERROR;
		}
		
		return INPUT_RESULT_ERROR; // should not happen		
	}

	int row;
	int col;
	int pos;

	if (sscanf(buffer, "%d %d %n", &row, &col, &pos) == 2)
	{
		for (int i = pos; buffer[i] != '\0'; ++i)
		{
			if (!isspace((unsigned char)buffer[i])) // cast to unsigned char to avoid UB when char is signed.
			{
				return INPUT_RESULT_INVALID; // extra characters after valid input
			}
		}
	}
	else
	{
		return INPUT_RESULT_INVALID; // could not parse two integers
	}

	out_input->row = row;
	out_input->col = col;

	size_t len = strlen(buffer);

	if (len > 0 && buffer[len - 1] != '\n') // line too long, rest of line still in input buffer
	{
		int ch;

		while ((ch = fgetc(stdin)) != '\n' && ch != EOF); // consume rest of line
	}	

	return INPUT_RESULT_OK;
}