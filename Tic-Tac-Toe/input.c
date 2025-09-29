#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // doing the safe pattern (fgets -> parse), so sscanf here is perfectly reasonable.
#endif

#include <stdio.h>

#include "input.h"

Input get_player_input(void)
{
	Input input = { -1, -1 };
	char buffer[100];

	if (fgets(buffer, sizeof(buffer), stdin))
	{
		if (sscanf(buffer, "%d %d", &input.row, &input.col) != 2)
		{
			input.row = -1;
			input.col = -1;
		}
	}

	return input;
}